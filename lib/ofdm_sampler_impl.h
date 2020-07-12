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

#ifndef INCLUDED_BAD_OFDM_SAMPLER_IMPL_H
#define INCLUDED_BAD_OFDM_SAMPLER_IMPL_H

#include <bad/ofdm_sampler.h>
#include "dab_parameters.h"
#include "tag_positions.h"

#define IVLEN0 1
#define OVLEN0 FFT_SIZE

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    class ofdm_sampler_impl : public ofdm_sampler
    {
    private:
      enum class state {
        NULL_SYMBOL,
        GUARD_INTERVAL_HEAD,
        REGULAR_SYMBOL,
        GUARD_INTERVAL_TAIL,
      };

      state d_state;
      int d_pos;
      int d_symbol;

      bool state_handler_null_symbol(tag_positions& positions, int nin);
      bool state_handler_guard_interval_head(int nin);
      bool state_handler_regular_symbol(int nin, const ITYPE0* iptr, int& nout, OTYPE0* optr);
      bool state_handler_guard_interval_tail(int nin);

    public:
      ofdm_sampler_impl();
      ~ofdm_sampler_impl();

      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_OFDM_SAMPLER_IMPL_H */

