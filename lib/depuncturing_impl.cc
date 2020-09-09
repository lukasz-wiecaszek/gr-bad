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

    struct depuncturing_ivl
    {
      void operator () (const L_PI &l_pi)
      {
        length += l_pi.L * N_SUB_BLOCKS * (8 + l_pi.PI);
      }
      operator int () const
      {
        return length;
      }
    private:
      int length{VTAIL.size() / 2};
    };

    struct depuncturing_ovl
    {
      void operator () (const L_PI &l_pi)
      {
        length += l_pi.L * 128;
      }
      operator int () const
      {
        return length;
      }
    private:
      int length{VTAIL.size()};
    };

    depuncturing::sptr
    depuncturing::make(protection_type_e type, int index, int n)
    {
      return gnuradio::get_initial_sptr
        (new depuncturing_impl<float, float>(type, index, n));
    }

    int
    depuncturing::ivlen(protection_type_e type, int index, int n)
    {
      const protection_profile& profile = get_protection_profile(type, index, n);
      return std::for_each(profile.begin(), profile.end(), depuncturing_ivl());
    }

    int
    depuncturing::ovlen(protection_type_e type, int index, int n)
    {
      const protection_profile& profile = get_protection_profile(type, index, n);
      return std::for_each(profile.begin(), profile.end(), depuncturing_ovl());
    }

    template<typename ITYPE0, typename OTYPE0>
    depuncturing_impl<ITYPE0, OTYPE0>::depuncturing_impl(protection_type_e type, int index, int n)
      : gr::sync_block("depuncturing",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * ivlen(type, index, n)),
                       gr::io_signature::make(1, 1, sizeof(OTYPE0) * ovlen(type, index, n))),
        d_puncturing_vector()
    {
      const protection_profile& profile = get_protection_profile(type, index, n);
      std::back_insert_iterator<std::vector<int>> output_it = std::back_inserter(d_puncturing_vector);

      printf("%s (%s): type: %d, index: %d, n: %d\n",
        __func__, type == PROTECTION_TYPE_FIC ? "fic" : "msc", type, index, n);
      printf("%s (%s): (L1: %d, L2: %d, L3: %d, L4: %d) -> (PI1: %d, PI2: %d, PI3: %d, PI4: %d)\n",
        __func__, type == PROTECTION_TYPE_FIC ? "fic" : "msc",
        profile[0].L, profile[1].L, profile[2].L, profile[3].L,
        profile[0].PI, profile[1].PI, profile[2].PI, profile[3].PI);

      std::for_each(profile.begin(), profile.end(), [&](const L_PI &l_pi){
        for (int i = 0; i < N_SUB_BLOCKS * l_pi.L; ++i)
          output_it = std::copy(
            puncturing_vectors[l_pi.PI].begin(),
            puncturing_vectors[l_pi.PI].end(),
            output_it);
      });

      output_it = std::copy(VTAIL.begin(), VTAIL.end(), output_it);

      printf("%s (%s): ivlen: %d, ovlen: %d\n",
        __func__, type == PROTECTION_TYPE_FIC ? "fic" : "msc",
        ivlen(type, index, n), ovlen(type, index, n));
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
        for (int j = 0; j < d_puncturing_vector.size(); ++j)
          *optr0++ = d_puncturing_vector[j] ? *iptr0++ : 0;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace bad */
} /* namespace gr */

