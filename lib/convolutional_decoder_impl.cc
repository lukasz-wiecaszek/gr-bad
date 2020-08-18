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

#include "convolutional_decoder_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/blocks/vector_to_stream.h>
#include <gnuradio/trellis/fsm.h>
#include <gnuradio/trellis/viterbi_combined.h>

#include <bad/depuncturing.h>
#include <bad/adapter.h>

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

    convolutional_decoder::sptr
    convolutional_decoder::make()
    {
      return gnuradio::get_initial_sptr
        (new convolutional_decoder_impl<float, uint8_t>());
    }

    template<typename ITYPE0, typename OTYPE0>
    convolutional_decoder_impl<ITYPE0, OTYPE0>::convolutional_decoder_impl()
      : gr::hier_block2("convolutional_decoder",
              gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
              gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      gr::trellis::fsm fsm{1, 4, polynomials};

      printf("fsm: input symbols: %u, output symbols: %u, states: %u\n", fsm.I(), fsm.O(), fsm.S());

      std::vector<float> table(observations.size());
      std::transform(observations.begin(), observations.end(), table.begin(),
         [](int x){return (1 - 2 * x) / std::sqrt(2);});

      gr::bad::depuncturing::sptr depuncturing(
        gr::bad::depuncturing::make());

      gr::blocks::vector_to_stream::sptr vector_to_stream(
        gr::blocks::vector_to_stream::make(sizeof(ITYPE0), FIC_CONVOLUTIONAL_CODEWORD_LENGTH));

      gr::trellis::viterbi_combined_fb::sptr viterbi_combined(
        gr::trellis::viterbi_combined_fb::make(fsm, 768 + 6, 0, 0, 4, table, gr::digital::TRELLIS_EUCLIDEAN));

      gr::bad::adapter_bb::sptr adapter(
        gr::bad::adapter_bb::make(1, (768 + 6) * 4, 768, 4, NULL));


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
