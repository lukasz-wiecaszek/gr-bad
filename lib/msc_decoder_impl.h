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

#ifndef INCLUDED_BAD_MSC_DECODER_IMPL_H
#define INCLUDED_BAD_MSC_DECODER_IMPL_H

#include <bad/msc_decoder.h>
#include "dab_parameters.h"

#define IVLEN0 OFDM_SYMBOL_BITS
#define OVLEN0 1

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    class msc_decoder_impl : public msc_decoder
    {
    private:
      void set(protection_type_e type, int subch_start_addr, int subch_size, int index, int n);

    public:
      msc_decoder_impl();
      ~msc_decoder_impl();

      void set_uep_params(int subch_start_addr, int table_index) override;
      void set_eep_a_params(int subch_start_addr, int subch_size, int protection_level) override;
      void set_eep_b_params(int subch_start_addr, int subch_size, int protection_level) override;

    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_MSC_DECODER_IMPL_H */

