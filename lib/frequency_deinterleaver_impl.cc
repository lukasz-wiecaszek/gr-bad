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
#include "frequency_deinterleaver_impl.h"

namespace gr {
  namespace bad {

    frequency_deinterleaver::sptr
    frequency_deinterleaver::make()
    {
      return gnuradio::get_initial_sptr
        (new frequency_deinterleaver_impl<gr_complex, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    frequency_deinterleaver_impl<ITYPE0, OTYPE0>::frequency_deinterleaver_impl()
      : gr::sync_block("frequency_deinterleaver",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0)),
        d_fis(frequency_interleaving_sequence::get_instance())
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    frequency_deinterleaver_impl<ITYPE0, OTYPE0>::~frequency_deinterleaver_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    frequency_deinterleaver_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      for (int i = 0; i < noutput_items; ++i) {
        for (int k = 0; k < K; ++k)
          optr0[k] = iptr0[d_fis[k]];
        
        iptr0 += IVLEN0;
        optr0 += OVLEN0;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

