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

#include <cmath>
#include <array>
#include <algorithm>

#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/vector_to_stream.h>
#include <gnuradio/trellis/fsm.h>
#include <gnuradio/trellis/viterbi_combined.h>

#include <bad/depuncturing.h>
#include <bad/adapter.h>

#include "convolutional_decoder_impl.h"
#include "puncturing_vectors.h"

namespace gr {
  namespace bad {

    constexpr std::array<int, 64> observations = {
      0, 0, 0, 0,
      0, 0, 0, 1,
      0, 0, 1, 0,
      0, 0, 1, 1,
      0, 1, 0, 0,
      0, 1, 0, 1,
      0, 1, 1, 0,
      0, 1, 1, 1,
      1, 0, 0, 0,
      1, 0, 0, 1,
      1, 0, 1, 0,
      1, 0, 1, 1,
      1, 1, 0, 0,
      1, 1, 0, 1,
      1, 1, 1, 0,
      1, 1, 1, 1
    };

    const std::vector<int> polynomials = {
      0133, 0171, 0145, 0133
    };

    struct convolutional_decoder_ivl
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

    struct convolutional_decoder_ovl
    {
      void operator () (const L_PI &l_pi)
      {
        length += l_pi.L * 32;
      }
      operator int () const
      {
        return length;
      }
    private:
      int length{0};
    };

    convolutional_decoder::sptr
    convolutional_decoder::make(protection_type_e type, int index, int n)
    {
      return gnuradio::get_initial_sptr
        (new convolutional_decoder_impl<float, uint8_t>(type, index, n));
    }

    int
    convolutional_decoder::ivlen(protection_type_e type, int index, int n)
    {
      const protection_profile& profile = get_protection_profile(type, index, n);
      return std::for_each(profile.begin(), profile.end(), convolutional_decoder_ivl());
    }

    int
    convolutional_decoder::ovlen(protection_type_e type, int index, int n)
    {
      const protection_profile& profile = get_protection_profile(type, index, n);
      return std::for_each(profile.begin(), profile.end(), convolutional_decoder_ovl());
    }

    template<typename ITYPE0, typename OTYPE0>
    convolutional_decoder_impl<ITYPE0, OTYPE0>::convolutional_decoder_impl(protection_type_e type, int index, int n)
      : gr::hier_block2("convolutional_decoder",
                        gr::io_signature::make(1, 1, sizeof(ITYPE0) * ivlen(type, index, n)),
                        gr::io_signature::make(1, 1, sizeof(OTYPE0) * ovlen(type, index, n))),
        d_I{ovlen(type, index, n)}
    {
      gr::trellis::fsm fsm{1, 4, polynomials};

      printf("%s (%s): fsm: input symbols: %u, output symbols: %u, states: %u\n",
        __func__, type == PROTECTION_TYPE_FIC ? "fic" : "msc", fsm.I(), fsm.O(), fsm.S());
      printf("%s (%s): I: %d\n", __func__, type == PROTECTION_TYPE_FIC ? "fic" : "msc", d_I);

      std::vector<float> table(observations.size());
      std::transform(observations.begin(), observations.end(), table.begin(),
         [](int x){return (1 - 2 * x) / std::sqrt(2);});

      gr::bad::depuncturing::sptr depuncturing(
        gr::bad::depuncturing::make(type, index, n));

      gr::blocks::vector_to_stream::sptr vector_to_stream(
        gr::blocks::vector_to_stream::make(sizeof(ITYPE0), (d_I + 6) * 4));

      gr::trellis::viterbi_combined_fb::sptr viterbi_combined(
        gr::trellis::viterbi_combined_fb::make(fsm, d_I + 6, 0, 0, 4, table, gr::digital::TRELLIS_EUCLIDEAN));

      gr::bad::adapter_bb::sptr adapter(
        gr::bad::adapter_bb::make(sizeof(OTYPE0), d_I + 6, d_I, sizeof(OTYPE0), NULL));

      connect(self(),               0, depuncturing,         0);
      connect(depuncturing,         0, vector_to_stream,     0);
      connect(vector_to_stream,     0, viterbi_combined,     0);
      connect(viterbi_combined,     0, adapter,              0);
      connect(adapter,              0, self(),               0);
    }

    template<typename ITYPE0, typename OTYPE0>
    convolutional_decoder_impl<ITYPE0, OTYPE0>::~convolutional_decoder_impl()
    {
    }

  } /* namespace bad */
} /* namespace gr */
