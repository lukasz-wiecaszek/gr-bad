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

#ifndef INCLUDED_BAD_BLOCK_DEPARTITIONER_IMPL_H
#define INCLUDED_BAD_BLOCK_DEPARTITIONER_IMPL_H

#include <bad/block_departitioner.h>
#include "dab_parameters.h"

#define IVLEN0 OFDM_SYMBOL_BITS
#define OVLEN0 FIC_PUNCTURED_CONVOLUTIONAL_CODEWORD_LENGTH

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    class block_departitioner_impl : public block_departitioner
    {
    private:

    public:
      block_departitioner_impl();
      ~block_departitioner_impl();

      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);

    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_BLOCK_DEPARTITIONER_IMPL_H */

