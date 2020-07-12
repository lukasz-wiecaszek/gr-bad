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
#include "energy_dispersal_descrambler_impl.h"

namespace gr {
  namespace bad {

    energy_dispersal_descrambler::sptr
    energy_dispersal_descrambler::make(int vlen)
    {
      return gnuradio::get_initial_sptr
        (new energy_dispersal_descrambler_impl<uint8_t, uint8_t>(vlen));
    }

    template<typename ITYPE0, typename OTYPE0>
    energy_dispersal_descrambler_impl<ITYPE0, OTYPE0>::energy_dispersal_descrambler_impl(int vlen)
      : gr::sync_block("energy_dispersal_descrambler",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * vlen),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * vlen)),
        d_prbs(vlen)
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    energy_dispersal_descrambler_impl<ITYPE0, OTYPE0>::~energy_dispersal_descrambler_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    energy_dispersal_descrambler_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      for (int i = 0; i < noutput_items; ++i) {
        for (int j = 0; j < d_prbs.length(); ++j)
          optr0[j] = iptr0[j] ^ d_prbs[j];
        
        iptr0 += d_prbs.length();
        optr0 += d_prbs.length();
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

