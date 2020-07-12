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
#include "select_symbols_impl.h"
#include "dab_parameters.h"

namespace gr {
  namespace bad {

    select_symbols::sptr
    select_symbols::make()
    {
      return gnuradio::get_initial_sptr
        (new select_symbols_impl<float, float>());
    }

    template<typename ITYPE0, typename OTYPE0>
    select_symbols_impl<ITYPE0, OTYPE0>::select_symbols_impl()
      : gr::block("select_symbols",
                  gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                  gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      set_tag_propagation_policy(TPP_CUSTOM);
    }

    template<typename ITYPE0, typename OTYPE0>
    select_symbols_impl<ITYPE0, OTYPE0>::~select_symbols_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    select_symbols_impl<ITYPE0, OTYPE0>::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      for (auto&& element : ninput_items_required)
        element = noutput_items;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    select_symbols_impl<ITYPE0, OTYPE0>::general_work(int noutput_items,
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

        int l = pmt::to_long(element.value);

        if (l == 1 || l == 2 || l == 3) {
          add_item_tag(0, nitems_written(0) + nproduced, pmt::mp(TAG_SYMBOL), pmt::mp(l), alias_pmt());
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

