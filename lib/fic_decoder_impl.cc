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

#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/vector_to_stream.h>
#include <gnuradio/blocks/unpacked_to_packed.h>

#include <bad/adapter.h>
#include <bad/convolutional_decoder.h>
#include <bad/energy_dispersal_descrambler.h>
#include <bad/protection_type.h>

#include "fic_decoder_impl.h"

namespace gr {
  namespace bad {

    fic_decoder::sptr
    fic_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new fic_decoder_impl<float, uint8_t>());
    }

    template<typename ITYPE0, typename OTYPE0>
    fic_decoder_impl<ITYPE0, OTYPE0>::fic_decoder_impl()
      : gr::hier_block2("fic_decoder",
                        gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                        gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      protection_type_e type = PROTECTION_TYPE_FIC;
      int index = 0;
      int n = 0;
      int ivlen = gr::bad::convolutional_decoder::ivlen(type, index, n);
      int ovlen = gr::bad::convolutional_decoder::ovlen(type, index, n);

printf("%s ivlen: %d, ovlen: %d\n", __func__, ivlen, ovlen);

      gr::bad::adapter_ff::sptr adapter(
        gr::bad::adapter_ff::make(IVLEN0, OFDM_SYMBOLS_PER_FIC,
          FIC_PUNCTURED_CONVOLUTIONAL_CODEWORD_LENGTH, FIC_CONVOLUTIONAL_CODEWORDS, NULL));

      gr::bad::convolutional_decoder::sptr fic_convolutional_decoder(
        gr::bad::convolutional_decoder::make(type, index, n));

      gr::bad::energy_dispersal_descrambler::sptr energy_dispersal_descrambler(
        gr::bad::energy_dispersal_descrambler::make(ovlen));

      gr::blocks::vector_to_stream::sptr vector_to_stream(
        gr::blocks::vector_to_stream::make(sizeof(OTYPE0), ovlen));

      gr::blocks::unpacked_to_packed_bb::sptr unpacked_to_packed(
        gr::blocks::unpacked_to_packed_bb::make(1, GR_MSB_FIRST));

      connect(self(),                       0, adapter,                      0);
      connect(adapter,                      0, fic_convolutional_decoder,    0);
      connect(fic_convolutional_decoder,    0, energy_dispersal_descrambler, 0);
      connect(energy_dispersal_descrambler, 0, vector_to_stream,             0);
      connect(vector_to_stream,             0, unpacked_to_packed,           0);
      connect(unpacked_to_packed,           0, self(),                       0);
    }

    template<typename ITYPE0, typename OTYPE0>
    fic_decoder_impl<ITYPE0, OTYPE0>::~fic_decoder_impl()
    {
    }

  } /* namespace bad */
} /* namespace gr */

