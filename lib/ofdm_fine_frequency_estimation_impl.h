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

#ifndef INCLUDED_BAD_OFDM_FINE_FREQUENCY_ESTIMATION_IMPL_H
#define INCLUDED_BAD_OFDM_FINE_FREQUENCY_ESTIMATION_IMPL_H

#include <bad/ofdm_fine_frequency_estimation.h>
#include "dab_parameters.h"
#include "tag_positions.h"

#define IVLEN0 1
#define OVLEN0 1

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    class ofdm_fine_frequency_estimation_impl : public ofdm_fine_frequency_estimation
    {
    private:
      enum class state {
        NULL_SYMBOL,
        REGULAR_SYMBOL,
      };

      state d_state;
      int d_pos;
      int d_symbol;
      float d_alpha;
      float d_ffo;

      float estimate_atan(const ITYPE0* iptr);

      bool state_handler_null_symbol(tag_positions& positions, int nout, OTYPE0* optr);
      bool state_handler_regular_symbol(int nout, const ITYPE0* iptr, OTYPE0* optr);

    public:
      ofdm_fine_frequency_estimation_impl(float alpha);
      ~ofdm_fine_frequency_estimation_impl();

      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_OFDM_FINE_FREQUENCY_ESTIMATION_IMPL_H */

