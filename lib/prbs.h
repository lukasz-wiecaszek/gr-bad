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

#ifndef INCLUDED_BAD_PRBS_H
#define INCLUDED_BAD_PRBS_H

#include <array>
#include <memory>

namespace gr {
  namespace bad {

    template<typename T>
    class prbs
    {
    private:
      int d_length;
      std::array<T, 9> d_FSR; // feedback shift register
      std::unique_ptr<T[]> d_PRBS;

    public:
      prbs(int length) :
         d_length{length},
         d_FSR{},
         d_PRBS{new T[length]}
      {
        // Initial state: 111111111
        d_FSR.fill(1);

        // Polynomial: X^9 + X^5 + 1
        for (int i = 0; i < length; ++i) {
          T x = d_FSR[8] ^ d_FSR[4];
          std::rotate(d_FSR.rbegin(), d_FSR.rbegin() + 1, d_FSR.rend());
          d_PRBS[i] = d_FSR[0] = x;
        }
      }

      T operator[](int x) const
      {
        return d_PRBS[x];
      }

      int length() const
      {
        return d_length;
      }
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_PRBS_H */

