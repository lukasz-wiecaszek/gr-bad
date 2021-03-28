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
#include "ofdm_symbols_selector_impl.h"
#include "dab_parameters.h"

namespace gr {
  namespace bad {

    ofdm_symbols_selector::sptr
    ofdm_symbols_selector::make()
    {
      return gnuradio::get_initial_sptr
        (new ofdm_symbols_selector_impl<float, float>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::ofdm_symbols_selector_impl()
      : gr::block("ofdm_symbols_selector",
                  gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                  gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0)),
        d_first(0),
        d_count(0)
    {
      set_tag_propagation_policy(TPP_DONT);
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::~ofdm_symbols_selector_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    void ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::select_symbols(int first, int count)
    {
        d_first = first;
        d_count = count;
    }

    template<typename ITYPE0, typename OTYPE0>
    void ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::select_fic_symbols()
    {
        d_first = 1;
        d_count = 3;
    }

    template<typename ITYPE0, typename OTYPE0>
    void ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::select_msc_symbols()
    {
        d_first = 4;
        d_count = 72;
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      for (auto&& element : ninput_items_required)
        element = noutput_items;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_symbols_selector_impl<ITYPE0, OTYPE0>::general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];
      int nproduced = 0;
      int nconsumed = 0;

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + ninput_items[0], pmt::mp(TAG_SYMBOL));

      for (auto&& element : tags) {
        if (nproduced >= noutput_items)
          break;
        if (nconsumed >= ninput_items[0])
          break;

        int l = pmt::to_long(element.value);

        if ((l >= d_first) && (l < (d_first + d_count))) {
          memcpy(optr0, iptr0, sizeof(OTYPE0) * OVLEN0);
          optr0 += OVLEN0;
          nproduced++;
        }

        iptr0 += IVLEN0;
        nconsumed++;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each(nconsumed);

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

  } /* namespace bad */
} /* namespace gr */

