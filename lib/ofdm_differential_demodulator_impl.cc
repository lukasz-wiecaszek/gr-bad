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
#include "ofdm_differential_demodulator_impl.h"

namespace gr {
  namespace bad {

    ofdm_differential_demodulator::sptr
    ofdm_differential_demodulator::make()
    {
      return gnuradio::get_initial_sptr
        (new ofdm_differential_demodulator_impl<gr_complex, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_differential_demodulator_impl<ITYPE0, OTYPE0>::ofdm_differential_demodulator_impl()
      : gr::sync_block("ofdm_differential_demodulator",
              gr::io_signature::make(1, 1, sizeof(gr_complex) * IVLEN0),
              gr::io_signature::make(1, 1, sizeof(gr_complex) * OVLEN0))
    {
      set_history(2);
    }

    template<typename ITYPE0, typename OTYPE0>
    ofdm_differential_demodulator_impl<ITYPE0, OTYPE0>::~ofdm_differential_demodulator_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    ofdm_differential_demodulator_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      for(int k = 0; k < noutput_items * K; ++k)
        optr0[k] = iptr0[k + K] * std::conj(iptr0[k]);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

