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
#include "time_deinterleaver_impl.h"

namespace gr {
  namespace bad {

    // This table corresponds to table 37 "Relationship between the indicies r', r and ir"
    // (Chapter 12 "Time Interleaving")
    constexpr int r_prime_to_r[] = {
      0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
    };

    constexpr int r_prime_to_r_length = sizeof(r_prime_to_r) / sizeof(r_prime_to_r[0]);

    time_deinterleaver::sptr
    time_deinterleaver::make(int vlen)
    {
      return gnuradio::get_initial_sptr
        (new time_deinterleaver_impl<float, float>(vlen));
    }

    template<typename ITYPE0, typename OTYPE0>
    time_deinterleaver_impl<ITYPE0, OTYPE0>::time_deinterleaver_impl(int vlen)
      : gr::sync_block("time_deinterleaver",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * vlen),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * vlen)),
        d_vlen(vlen)
    {
      set_history(r_prime_to_r_length);
    }

    template<typename ITYPE0, typename OTYPE0>
    time_deinterleaver_impl<ITYPE0, OTYPE0>::~time_deinterleaver_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    time_deinterleaver_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      for (int i = 0; i < noutput_items; ++i)
        for (int ir = 0; ir < d_vlen; ++ir) {
          int r = r_prime_to_r[ir % r_prime_to_r_length];
          optr0[ir] = iptr0[d_vlen * (i + r) + ir];
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

