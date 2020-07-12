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
#include "qpsk_symbol_demapper_impl.h"

namespace gr {
  namespace bad {

    qpsk_symbol_demapper::sptr
    qpsk_symbol_demapper::make()
    {
      return gnuradio::get_initial_sptr
        (new qpsk_symbol_demapper_impl<gr_complex, float>());
    }

    template<typename ITYPE0, typename OTYPE0>
    qpsk_symbol_demapper_impl<ITYPE0, OTYPE0>::qpsk_symbol_demapper_impl()
      : gr::sync_block("qpsk_symbol_demapper",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      set_tag_propagation_policy(TPP_CUSTOM);
    }

    template<typename ITYPE0, typename OTYPE0>
    qpsk_symbol_demapper_impl<ITYPE0, OTYPE0>::~qpsk_symbol_demapper_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    qpsk_symbol_demapper_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];
      int nproduced = 0;

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items, pmt::mp(TAG_SYMBOL));

      for (auto&& element : tags) {
        int l = pmt::to_long(element.value);

        for (int k = 0; k < K; ++k) {
          optr0[k + 0] = iptr0[k].real();
          optr0[k + K] = iptr0[k].imag();
        }

        add_item_tag(0, nitems_written(0) + nproduced, pmt::mp(TAG_SYMBOL), pmt::mp(l), alias_pmt());

        nproduced++;
        iptr0 += IVLEN0;
        optr0 += OVLEN0;
      }

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

  } /* namespace bad */
} /* namespace gr */

