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

#include "ns_detector_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/complex_to_mag_squared.h>
#include <gnuradio/blocks/add_blk.h>

#include <bad/ns_moving_sum.h>
#include <bad/ns_peak_detector.h>

namespace gr {
  namespace bad {

    ns_detector::sptr
    ns_detector::make()
    {
      return gnuradio::get_initial_sptr
        (new ns_detector_impl<gr_complex, gr_complex>());
    }

    template<typename ITYPE0, typename OTYPE0>
    ns_detector_impl<ITYPE0, OTYPE0>::ns_detector_impl()
      : gr::hier_block2("ns_detector",
                         gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                         gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      gr::blocks::complex_to_mag_squared::sptr c2mag2(gr::blocks::complex_to_mag_squared::make());
      gr::bad::ns_moving_sum::sptr             ns_moving_sum(gr::bad::ns_moving_sum::make());
      gr::bad::ns_peak_detector::sptr          ns_peak_detector(gr::bad::ns_peak_detector::make());
      gr::blocks::add_cc::sptr                 adder(gr::blocks::add_cc::make());

      connect(self(),               0, c2mag2,               0);
      connect(c2mag2,               0, ns_moving_sum,        0);
      connect(ns_moving_sum,        0, ns_peak_detector,     0);
      connect(self(),               0, adder,                0);
      connect(ns_peak_detector,     0, adder,                1);
      connect(adder,                0, self(),               0);
    }

    template<typename ITYPE0, typename OTYPE0>
    ns_detector_impl<ITYPE0, OTYPE0>::~ns_detector_impl()
    {
    }

  } /* namespace bad */
} /* namespace gr */

