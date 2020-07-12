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
#include <gnuradio/math.h>
#include "ofdm_fine_frequency_correction_impl.h"
#include "tag_positions.h"

namespace gr {
  namespace bad {

    ofdm_fine_frequency_correction::sptr
    ofdm_fine_frequency_correction::make(float alpha)
    {
      return gnuradio::get_initial_sptr
        (new ofdm_fine_frequency_correction_impl<gr_complex, float>(alpha));
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::ofdm_fine_frequency_correction_impl(float alpha)
      : gr::sync_block("ofdm_fine_frequency_correction",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0)),
        d_state(state::NULL_SYMBOL),
        d_pos(0),
        d_symbol(0),
        d_alpha(alpha),
        d_ffo(0)
    {
      set_output_multiple((2 * TNULL) + 1);
      set_tag_propagation_policy(TPP_DONT);
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::~ofdm_fine_frequency_correction_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    float
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::estimate_atan(const ITYPE0* iptr)
    {
      gr_complex sum = 0;

      for (int i = 0; i < GI; i++)
        sum += iptr[i] * std::conj(iptr[i + FFT_SIZE]);

      float atan2 = gr::fast_atan2f(sum);

      return atan2 /* < 0 ? 2 * M_PI + atan2 : atan2 */;
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::state_handler_null_symbol(tag_positions& positions, int nout, OTYPE0* optr)
    {
      d_symbol = 0;

      if (positions.value() < 0) {
        if (d_pos == 0) {
          for (int i = 0; i < nout; i++)
            optr[i] = 0.0;
          d_pos = nout;
        }
        return false;
      }

      for (int i = d_pos; i < positions.value(); i++)
        optr[i] = 0.0;

      d_pos = positions.value();
      positions.next();

      d_state = state::REGULAR_SYMBOL;
      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    bool
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::state_handler_regular_symbol(int nout, const ITYPE0* iptr, OTYPE0* optr)
    {
      if (d_pos + TS > nout)
        return false;

      float ffo = estimate_atan(iptr + d_pos) / FFT_SIZE;

      d_ffo += d_alpha * (ffo - d_ffo);

      for (int i = d_pos; i < d_pos + TS; i++)
        optr[i] = d_ffo;

      d_pos += TS;
      d_symbol++;

      if (d_symbol < L)
        d_state = state::REGULAR_SYMBOL;
      else
        d_state = state::NULL_SYMBOL;

      return true;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      std::vector<tag_t> tags;
      get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items, pmt::mp(TAG_NS));
      tag_positions positions(tags, nitems_read(0));

      d_pos = 0;

      bool status = false;
      do {
        switch (d_state)
        {
          case state::NULL_SYMBOL:
            status = state_handler_null_symbol(positions, noutput_items, optr0);
            break;

          case state::REGULAR_SYMBOL:
            status = state_handler_regular_symbol(noutput_items, iptr0, optr0);
            break;

          default:
            status = false;
            break;
        }
      } while (status == true);

      //printf("noutput_items = %d, d_state = %d, d_symbol = %d, d_pos = %d\n",
      //  noutput_items, (int)d_state, d_symbol, d_pos);

      // Tell runtime system how many output items we produced.
      return d_pos;
    }

  } /* namespace bad */
} /* namespace gr */

