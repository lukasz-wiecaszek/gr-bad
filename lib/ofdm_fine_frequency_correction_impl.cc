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
#include <gnuradio/analog/frequency_modulator_fc.h>
#include <gnuradio/blocks/multiply.h>

#include <bad/ofdm_fine_frequency_estimation.h>

#include "ofdm_fine_frequency_correction_impl.h"

namespace gr {
  namespace bad {

    ofdm_fine_frequency_correction::sptr
    ofdm_fine_frequency_correction::make(float alpha)
    {
      return gnuradio::get_initial_sptr
        (new ofdm_fine_frequency_correction_impl<gr_complex, gr_complex, float>(alpha));
    }


    template<typename ITYPE0, typename OTYPE0, typename OTYPE1>
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0, OTYPE1>::ofdm_fine_frequency_correction_impl(float alpha)
      : gr::hier_block2("ofdm_fine_frequency_correction",
                        gr::io_signature::make (1, 1, sizeof(ITYPE0) * IVLEN0),
                        gr::io_signature::make2(2, 2, sizeof(OTYPE0) * OVLEN0, sizeof(OTYPE1) * OVLEN1))
    {
      gr::bad::ofdm_fine_frequency_estimation::sptr ffe(
        gr::bad::ofdm_fine_frequency_estimation::make(alpha));

      gr::analog::frequency_modulator_fc::sptr fm(
        gr::analog::frequency_modulator_fc::make(1.0f));

      gr::blocks::multiply_cc::sptr multiplier(
        gr::blocks::multiply_cc::make(1));

      connect(self(),      0, ffe,         0);
      connect(ffe,         0, fm,          0);
      connect(fm,          0, multiplier,  0);
      connect(self(),      0, multiplier,  1);
      connect(multiplier,  0, self(),      0);
      connect(ffe,         0, self(),      1);
    }

    template<typename ITYPE0, typename OTYPE0, typename OTYPE1>
    ofdm_fine_frequency_correction_impl<ITYPE0, OTYPE0, OTYPE1>::~ofdm_fine_frequency_correction_impl()
    {
    }

  } /* namespace bad */
} /* namespace gr */

