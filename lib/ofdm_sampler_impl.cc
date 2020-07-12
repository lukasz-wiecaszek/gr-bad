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
#include "ofdm_sampler_impl.h"
#include "tag_positions.h"

#define GI_HEAD (252)
#define GI_TAIL (GI - GI_HEAD)

namespace gr {
  namespace bad {

    static_assert(GI_HEAD <= GI, "guard interval header cannot be bigger then the guard interval alone");

    ofdm_sampler::sptr
    ofdm_sampler::make()
    {
      return gnuradio::get_initial_sptr
        (new ofdm_sampler_impl<gr_complex, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_sampler_impl<ITYPE0, OTYPE0>::ofdm_sampler_impl()
      : gr::block("ofdm_sampler",
                  gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                  gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0)),
        d_state(state::NULL_SYMBOL),
        d_pos(0),
        d_symbol(0)
    {
      set_relative_rate(1, TS); // 1 output item per TS input items
      set_tag_propagation_policy(TPP_DONT);
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_sampler_impl<ITYPE0, OTYPE0>::~ofdm_sampler_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_sampler_impl<ITYPE0, OTYPE0>::state_handler_null_symbol(tag_positions& positions, int nin)
    {
      d_symbol = 0;

      if (positions.value() < 0) {
        if (d_pos == 0)
          d_pos = nin;
        return false;
      }

      d_pos = positions.value();
      positions.next();

      d_state = state::GUARD_INTERVAL_HEAD;
      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_sampler_impl<ITYPE0, OTYPE0>::state_handler_guard_interval_head(int nin)
    {
      if (d_pos + GI_HEAD > nin)
        return false;

      d_pos += GI_HEAD;

      d_state = state::REGULAR_SYMBOL;
      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_sampler_impl<ITYPE0, OTYPE0>::state_handler_regular_symbol(int nin, const ITYPE0* iptr, int& nout, OTYPE0* optr)
    {
      if (d_pos + FFT_SIZE > nin)
        return false;

      memcpy(optr + (nout * FFT_SIZE), iptr + d_pos, FFT_SIZE * sizeof(gr_complex));
      add_item_tag(0, nitems_written(0) + nout, pmt::mp(TAG_SYMBOL), pmt::mp(d_symbol), alias_pmt());

      d_pos += FFT_SIZE;
      nout++;
      d_symbol++;

      d_state = state::GUARD_INTERVAL_TAIL;
      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_sampler_impl<ITYPE0, OTYPE0>::state_handler_guard_interval_tail(int nin)
    {
      if (d_pos + GI_TAIL > nin)
        return false;

      d_pos += GI_TAIL;
      if (d_symbol < L)
        d_state = state::GUARD_INTERVAL_HEAD;
      else
        d_state = state::NULL_SYMBOL;

      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    ofdm_sampler_impl<ITYPE0, OTYPE0>::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      int nrequired = noutput_items * TS;

      for (auto&& element : ninput_items_required)
        element = nrequired;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_sampler_impl<ITYPE0, OTYPE0>::general_work(int noutput_items,
                       gr_vector_int& ninput_items,
                       gr_vector_const_void_star& input_items,
                       gr_vector_void_star& output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];
      int nproduced = 0;

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + ninput_items[0], pmt::mp(TAG_NS));
      tag_positions positions(tags, nitems_read(0));

      d_pos = 0;

      bool status = true;
      while ((nproduced < noutput_items) && (status == true)) {
        switch (d_state) {
          case state::NULL_SYMBOL:
            status = state_handler_null_symbol(positions, ninput_items[0]);
            break;

          case state::GUARD_INTERVAL_HEAD:
            status = state_handler_guard_interval_head(ninput_items[0]);
            break;

          case state::REGULAR_SYMBOL:
            status = state_handler_regular_symbol(ninput_items[0], iptr0, nproduced, optr0);
            break;

          case state::GUARD_INTERVAL_TAIL:
            status = state_handler_guard_interval_tail(ninput_items[0]);
            break;

          default:
            status = false;
            break;
        }
      };

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each(d_pos);

      //printf("general_work: noutput_items = %d, ninput_items = %d, d_state = %d, d_symbol = %d, d_pos = %d, nout0 = %d\n",
      //  noutput_items, ninput_items[0], (int)d_state, d_symbol, d_pos, nout0);

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

  } /* namespace bad */
} /* namespace gr */

