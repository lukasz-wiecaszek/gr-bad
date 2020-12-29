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

#ifndef INCLUDED_BAD_CONVOLUTIONAL_DECODER_IMPL_H
#define INCLUDED_BAD_CONVOLUTIONAL_DECODER_IMPL_H

#include <bad/convolutional_decoder.h>
#include "dab_parameters.h"

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    class convolutional_decoder_impl : public convolutional_decoder
    {
    private:
      int d_I;

    public:
      convolutional_decoder_impl(protection_type_e type, int index, int n);
      ~convolutional_decoder_impl();

      int I() const override
      {
        return d_I;
      }

    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_CONVOLUTIONAL_DECODER_IMPL_H */

