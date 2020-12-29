/* -*- c++ -*- */
/*
 * Copyright 2020 Lukasz Wiecaszek <lukasz.wiecaszek@gmail.com>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sstream>

#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/vector_to_stream.h>
#include <gnuradio/blocks/unpacked_to_packed.h>

#include <bad/adapter.h>
#include <bad/cus_selector.h>
#include <bad/time_deinterleaver.h>
#include <bad/convolutional_decoder.h>
#include <bad/energy_dispersal_descrambler.h>
#include <bad/protection_type.h>

#include "msc_decoder_impl.h"

namespace gr {
  namespace bad {

    msc_decoder::sptr
    msc_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new msc_decoder_impl<float, uint8_t>());
    }

    template<typename ITYPE0, typename OTYPE0>
    msc_decoder_impl<ITYPE0, OTYPE0>::msc_decoder_impl()
      : gr::hier_block2("msc_decoder",
                        gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                        gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    msc_decoder_impl<ITYPE0, OTYPE0>::~msc_decoder_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    msc_decoder_impl<ITYPE0, OTYPE0>::set(protection_type_e type, int subch_start_addr, int subch_size, int index, int n)
    {
      gr::bad::adapter_ff::sptr adapter1(
        gr::bad::adapter_ff::make(IVLEN0, OFDM_SYMBOLS_PER_MSC / CIFS_PER_TF,
          CU_SIZE, CUS_PER_CIF, TAG_CU));

      gr::bad::cus_selector::sptr cus_selector(
        gr::bad::cus_selector::make(subch_start_addr, subch_size));

      gr::bad::adapter_ff::sptr adapter2(
        gr::bad::adapter_ff::make(CU_SIZE, subch_size,
          CU_SIZE * subch_size, 1, NULL));

      gr::bad::time_deinterleaver::sptr time_deinterleaver(
        gr::bad::time_deinterleaver::make(CU_SIZE * subch_size));

      gr::bad::convolutional_decoder::sptr convolutional_decoder(
        gr::bad::convolutional_decoder::make(type, index, n));

      int I = convolutional_decoder->I();

      gr::bad::energy_dispersal_descrambler::sptr energy_dispersal_descrambler(
        gr::bad::energy_dispersal_descrambler::make(I));

      gr::blocks::vector_to_stream::sptr vector_to_stream(
        gr::blocks::vector_to_stream::make(sizeof(OTYPE0), I));

      gr::blocks::unpacked_to_packed_bb::sptr unpacked_to_packed(
        gr::blocks::unpacked_to_packed_bb::make(1, GR_MSB_FIRST));

      connect(self(),                       0, adapter1,                     0);
      connect(adapter1,                     0, cus_selector,                 0);
      connect(cus_selector,                 0, adapter2,                     0);
      connect(adapter2,                     0, time_deinterleaver,           0);
      connect(time_deinterleaver,           0, convolutional_decoder,        0);
      connect(convolutional_decoder,        0, energy_dispersal_descrambler, 0);
      connect(energy_dispersal_descrambler, 0, vector_to_stream,             0);
      connect(vector_to_stream,             0, unpacked_to_packed,           0);
      connect(unpacked_to_packed,           0, self(),                       0);
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    msc_decoder_impl<ITYPE0, OTYPE0>::set_uep_params(int subch_start_addr, int table_index)
    {
      constexpr int subch_sizes[64] = {
         16,  21,  24,  29,  35, //  32 kbit/s
         24,  29,  35,  42,  52, //  48 kbit/s
         29,  35,  42,  52,      //  56 kbit/s
         32,  42,  48,  58,  70, //  64 kbit/s
         40,  52,  58,  70,  84, //  80 kbit/s
         48,  58,  70,  84, 104, //  96 kbit/s
         58,  70,  84, 104,      // 112 kbit/s
         64,  84,  96, 116, 140, // 128 kbit/s
         80, 104, 116, 140, 168, // 160 kbit/s
         96, 116, 140, 168, 208, // 192 kbit/s
        116, 140, 168, 208, 232, // 224 kbit/s
        128, 168, 192, 232, 280, // 256 kbit/s
        160, 208,      280,      // 320 kbit/s
        192,      280,      416  // 384 kbit/s
      };

      if ((subch_start_addr < 0) || (subch_start_addr > (CUS_PER_CIF - 1)))
        throw std::invalid_argument("subch_start_addr must be in range [0 .. 863]");

      if ((table_index < 0) || (table_index > 63))
        throw std::invalid_argument("table_index must be in range [0 .. 63]");

      set(PROTECTION_TYPE_UEP, subch_start_addr, subch_sizes[table_index], table_index, 0);
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    msc_decoder_impl<ITYPE0, OTYPE0>::set_eep_a_params(int subch_start_addr, int subch_size, int protection_level)
    {
      constexpr int divider[4] = {12, 8, 6, 4};

      if ((subch_start_addr < 0) || (subch_start_addr > (CUS_PER_CIF - 1)))
        throw std::invalid_argument("subch_start_addr must be in range [0 .. 863]");

      if ((subch_size < 1) || (subch_size > CUS_PER_CIF))
        throw std::invalid_argument("subch_size must be in range [1 .. 864]");

      if ((subch_start_addr + subch_size) > (CUS_PER_CIF - 1))
        throw std::invalid_argument("subch_start_addr + subch_size must be less than 864");

      if ((protection_level < 0) || (protection_level > 3))
        throw std::invalid_argument("protection_level must be in range [0 .. 3]");

      if (subch_size % divider[protection_level]) {
        std::stringstream s;
        s << "subch_size (" << subch_size << ") must be multiple of " << divider[protection_level] << std::endl;
        throw std::invalid_argument(s.str());
      }

      set(PROTECTION_TYPE_EEP_A, subch_start_addr, subch_size, protection_level + 1, subch_size / divider[protection_level]);
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    msc_decoder_impl<ITYPE0, OTYPE0>::set_eep_b_params(int subch_start_addr, int subch_size, int protection_level)
    {
      constexpr int divider[4] = {27, 21, 18, 15};

      if ((subch_start_addr < 0) || (subch_start_addr > (CUS_PER_CIF - 1)))
        throw std::invalid_argument("subch_start_addr must be in range [0 .. 863]");

      if ((subch_size < 1) || (subch_size > CUS_PER_CIF))
        throw std::invalid_argument("subch_size must be in range [1 .. 864]");

      if ((subch_start_addr + subch_size) > (CUS_PER_CIF - 1))
        throw std::invalid_argument("subch_start_addr + subch_size must be less than 864");

      if ((protection_level < 0) || (protection_level > 3))
        throw std::invalid_argument("protection_level must be in range [0 .. 3]");

      if (subch_size % divider[protection_level]) {
        std::stringstream s;
        s << "subch_size (" << subch_size << ") must be multiple of " << divider[protection_level] << std::endl;
        throw std::invalid_argument(s.str());
      }

      set(PROTECTION_TYPE_EEP_B, subch_start_addr, subch_size, protection_level + 1, subch_size / divider[protection_level]);
    }

  } /* namespace bad */
} /* namespace gr */

