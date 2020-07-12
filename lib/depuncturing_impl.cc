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

#include <cassert>
#include <algorithm>

#include <gnuradio/io_signature.h>
#include "depuncturing_impl.h"
#include "puncturing_vectors.h"

namespace gr {
  namespace bad {

    depuncturing::sptr
    depuncturing::make()
    {
      return gnuradio::get_initial_sptr
        (new depuncturing_impl<float, float>());
    }

    template<typename ITYPE0, typename OTYPE0>
    depuncturing_impl<ITYPE0, OTYPE0>::depuncturing_impl()
      : gr::sync_block("depuncturing",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      typename decltype(d_fic_puncturing_vector)::iterator output_it = d_fic_puncturing_vector.begin();

      for (int i = 0; i < 21 * 4; ++i)
        output_it = std::copy(puncturing_vectors[16].begin(), puncturing_vectors[16].end(), output_it);

      for (int i = 0; i < 3 * 4; ++i)
        output_it = std::copy(puncturing_vectors[15].begin(), puncturing_vectors[15].end(), output_it);

      output_it = std::copy(VTAIL.begin(), VTAIL.end(), output_it);

      assert(output_it == d_fic_puncturing_vector.end());
    }

    template<typename ITYPE0, typename OTYPE0>
    depuncturing_impl<ITYPE0, OTYPE0>::~depuncturing_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    depuncturing_impl<ITYPE0, OTYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];

      for (int i = 0; i < noutput_items; ++i)
        for (int j = 0; j < d_fic_puncturing_vector.size(); ++j)
          *optr0++ = d_fic_puncturing_vector[j] ? *iptr0++ : 0;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

