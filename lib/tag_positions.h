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

#ifndef INCLUDED_BAD_TAG_POSITIONS_H
#define INCLUDED_BAD_TAG_POSITIONS_H

#include <cstdint>
#include <vector>
#include <gnuradio/tags.h>

namespace gr {
  namespace bad {

    class tag_positions
    {
    public:
      tag_positions(const std::vector<tag_t>& tags, uint64_t origin) :
        d_positions(tags.size()),
        d_nelements(tags.size()),
        d_index(-1),
        d_value(-1)
      {
        for (size_t i = 0; i < d_nelements; i++) {
          d_positions[i] = tags[i].offset - origin;
        }

        if (d_nelements > 0) {
          d_index = 0;
          d_value = d_positions[d_index];
        }
      }

      int value() const
      {
        return d_value;
      }

      void next()
      {
        d_index++;
        if (d_index < d_nelements)
          d_value = d_positions[d_index];
        else {
          d_index = -1;
          d_value = -1;
        }
      }

    private:
      std::vector<int> d_positions;
      size_t d_nelements;
      size_t d_index;
      int d_value;
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_TAG_POSITIONS_H */

