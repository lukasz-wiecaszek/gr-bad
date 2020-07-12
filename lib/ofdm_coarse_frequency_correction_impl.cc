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
#include <gnuradio/expj.h>
#include "ofdm_coarse_frequency_correction_impl.h"

namespace gr {
  namespace bad {

    ofdm_coarse_frequency_correction::sptr
    ofdm_coarse_frequency_correction::make()
    {
      return gnuradio::get_initial_sptr
        (new ofdm_coarse_frequency_correction_impl<gr_complex, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_coarse_frequency_correction_impl<ITYPE0, OTYPE0>::ofdm_coarse_frequency_correction_impl()
      : gr::sync_block("ofdm_coarse_frequency_correction",
              gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
              gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      set_relative_rate(K, FFT_SIZE); // K (1536) output items per FFT_SIZE (2048) input items
      set_tag_propagation_policy(TPP_CUSTOM);
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_coarse_frequency_correction_impl<ITYPE0, OTYPE0>::~ofdm_coarse_frequency_correction_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_coarse_frequency_correction_impl<ITYPE0, OTYPE0>::calculate_frequency_offset(const gr_complex* in) const
    {
      int i, offset;
      double sum = 0;
      double max = 0;
      float norm[FFT_SIZE];

      i = 0;
      for (auto&& element : norm)
        element = std::norm(in[i++]);

      for (i = 0; i < (K + 1); ++i)
        sum += norm[i];
      sum -= norm[K / 2]; // central carrier shall be zero carrier

      max = sum;
      offset = 0;
      for (i = 1; i < (FFT_SIZE - K); ++i) {
        sum -= norm[i - 1];
        sum += norm[i + K / 2 - 1]; // central carrier shall be zero carrier
        sum -= norm[i + K / 2]; // central carrier shall be zero carrier
        sum += norm[i + K];

        if (sum > max) {
          max = sum;
          offset = i;
        }
      }

      return offset;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_coarse_frequency_correction_impl<ITYPE0, OTYPE0>::work(int noutput_items,
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
        int cfo = calculate_frequency_offset(iptr0);
        int delta_f = FFT_SIZE / 2 - K / 2 - cfo;

        gr_complex phase_offset = gr_expj(2 * M_PI * GI * delta_f * l / FFT_SIZE);

        //printf("symbol: %d, cfo: %d, delta_f: %d\n", l, cfo, delta_f);

        for (int k = 0; k < K / 2; ++k)
          optr0[k] = iptr0[k + cfo] * phase_offset;

        for (int k = K / 2; k < K; ++k)
          optr0[k] = iptr0[k + cfo + 1] * phase_offset;

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

