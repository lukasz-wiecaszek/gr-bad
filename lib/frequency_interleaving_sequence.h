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

#ifndef INCLUDED_BAD_FREQUENCY_INTERLEAVING_SEQUENCE_H
#define INCLUDED_BAD_FREQUENCY_INTERLEAVING_SEQUENCE_H

#include <cstdint>
#include <cassert>
#include <array>
#include <algorithm>
#include <numeric>
#include "dab_parameters.h"

namespace gr {
  namespace bad {

    class frequency_interleaving_sequence
    {
    public:
      static const frequency_interleaving_sequence& get_instance()
      {
        static frequency_interleaving_sequence instance;
        return instance;
      }

      int operator[](int x) const
      {
        return D_SHIFTED[x];
      }

    private:
      frequency_interleaving_sequence()
      {
        decltype(A) S;

        A[0] = 0;
        for (int i = 1; i < A.size(); ++i)
          A[i] = (13 * A[i - 1] + (A.size() / 4 - 1)) % A.size();

        std::iota(S.begin(), S.end(), 0);
        assert(std::is_permutation(A.begin(), A.end(), S.begin()));

        std::copy_if(A.begin(), A.end(), D.begin(), [](int a){return (a >= 256) && (a <= 1792) && (a != 1024);});
        std::transform(D.begin(), D.end(), D_SHIFTED.begin(), [](int d){d -= 1024; return d + K / 2 - ((d > 0) ? 1 : 0);});

        //for (int i = 0; i < D_SHIFTED.size(); i++)
        //  printf("i: %d, k: %d, d: %d\n", i, D_SHIFTED[i], D_SHIFTED[i] - K/2);
      }

      frequency_interleaving_sequence(const frequency_interleaving_sequence&) = delete;
      frequency_interleaving_sequence& operator=(const frequency_interleaving_sequence&) = delete;

      std::array<int, FFT_SIZE> A;
      std::array<int, K> D;
      std::array<int, K> D_SHIFTED;
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_FREQUENCY_INTERLEAVING_SEQUENCE_H */

