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
#include <math.h>
#include <algorithm>
#include "ns_peak_detector_impl.h"

#define THRESHOLD_FALL 0.4
#define THRESHOLD_RISE 0.6
#define APLHA          0.1

namespace gr {
  namespace bad {

    ns_peak_detector::sptr
    ns_peak_detector::make()
    {
      return gnuradio::get_initial_sptr
        (new ns_peak_detector_impl<float, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ns_peak_detector_impl<ITYPE0, OTYPE0>::ns_peak_detector_impl()
      : gr::sync_block("ns_peak_detector",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0)),
        d_state(state::ABOVE_THRESHOLD),
        d_sum_max(-INFINITY),
        d_peak_value(INFINITY),
        d_peak_index(-1)
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    ns_peak_detector_impl<ITYPE0, OTYPE0>::~ns_peak_detector_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ns_peak_detector_impl<ITYPE0, OTYPE0>::work(int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const ITYPE0 *iptr0 = (const ITYPE0 *) input_items[0];
      OTYPE0 *optr0 = (OTYPE0 *) output_items[0];

      tag_t tag;
      tag.offset = 0; // offset will be updated just before adding this tag to a stream
      tag.key = pmt::mp(TAG_NS);
      tag.value = pmt::PMT_NIL;
      tag.srcid = alias_pmt();

      if (d_sum_max == -INFINITY) {
        for (int i = 0; i < noutput_items; i++) {
          d_sum_max = std::max(d_sum_max, iptr0[i]);
        }
      }
      else {
        int i = 0;
        float max = -INFINITY;

        while (i < noutput_items) {
          if (d_state == state::ABOVE_THRESHOLD) {
            if (iptr0[i] < d_sum_max * THRESHOLD_FALL) {
              //printf("fall noutput_items: %d, d_sum_max: %6.2f, threshold: %6.2f, sum: %6.2f\n",
              //  noutput_items, d_sum_max, d_sum_max * THRESHOLD_FALL, in0[i]);
              d_state = state::BELOW_THRESHOLD;
              continue;
            }
            else
              i++;
          }
          else
          if (d_state == state::BELOW_THRESHOLD) {
            if (iptr0[i] <= d_peak_value) {
               d_peak_value = iptr0[i];
               d_peak_index = i;
               i++;
            }
            else
            if (iptr0[i] < d_sum_max * THRESHOLD_RISE) { // if it's still lower than rise threshold
               i++;
            }
            else {
              //printf("rise noutput_items: %d, d_sum_max: %6.2f, threshold: %6.2f, sum: %6.2f (%6.2f @ %lu), index: %d\n",
              //  noutput_items, d_sum_max, d_sum_max * THRESHOLD_RISE, in0[i], d_peak_value, nitems_written(0) + d_peak_index, d_peak_index);
              tag.offset = nitems_written(0) + d_peak_index;
              add_item_tag(0, tag);

              d_peak_value = INFINITY;
              d_peak_index = -1;
              d_state = state::ABOVE_THRESHOLD;
              continue;
            }
          }
          else
            assert(!"invalid state detected");

          max = std::max(max, iptr0[i]);
        }

        if (d_state == state::ABOVE_THRESHOLD)
          d_sum_max += APLHA * (max - d_sum_max);
      }

      int nproduced = (d_state == state::BELOW_THRESHOLD) ? d_peak_index : noutput_items;

      // This is tricky, but when all bits (sign, exponent, mantissa) are zero
      // the floating point value represents also zero, as defined by IEEE 754.
      memset(optr0, 0, nproduced * sizeof(OTYPE0));

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

  } /* namespace bad */
} /* namespace gr */

