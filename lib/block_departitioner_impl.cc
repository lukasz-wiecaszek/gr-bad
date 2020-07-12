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

#include <gnuradio/io_signature.h>
#include "block_departitioner_impl.h"

namespace gr {
  namespace bad {

    static_assert(OFDM_SYMBOL_BITS * OFDM_SYMBOLS_PER_FIC == FIC_PUNCTURED_CONVOLUTIONAL_CODEWORD_LENGTH * FIC_CONVOLUTIONAL_CODEWORDS, 
      "Number of bytes at input must be equal to the number of bytes at output");

    block_departitioner::sptr
    block_departitioner::make()
    {
      return gnuradio::get_initial_sptr
        (new block_departitioner_impl<float, float>());
    }

    template<typename ITYPE0, typename OTYPE0>
    block_departitioner_impl<ITYPE0, OTYPE0>::block_departitioner_impl()
      : gr::block("block_departitioner",
                  gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                  gr::io_signature::make(1, 1, sizeof(OTYPE0) * OVLEN0))
    {
      set_output_multiple(FIC_CONVOLUTIONAL_CODEWORDS);
      set_tag_propagation_policy(TPP_DONT);
    }

    template<typename ITYPE0, typename OTYPE0>
    block_departitioner_impl<ITYPE0, OTYPE0>::~block_departitioner_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    block_departitioner_impl<ITYPE0, OTYPE0>::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      // Every FIC_CONVOLUTIONAL_CODEWORDS blocks at output require OFDM_SYMBOLS_PER_FIC symbols at input
      int nrequired = noutput_items * OFDM_SYMBOLS_PER_FIC / FIC_CONVOLUTIONAL_CODEWORDS;

      for (auto&& element : ninput_items_required)
        element = nrequired;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    block_departitioner_impl<ITYPE0, OTYPE0>::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];
      int nproduced = 0;
      int nconsumed = 0;
      
      while (nproduced < noutput_items) {
        if (noutput_items < nproduced + FIC_CONVOLUTIONAL_CODEWORDS)
          break;
        if (ninput_items[0] < nconsumed + OFDM_SYMBOLS_PER_FIC)
          break;

        memcpy(optr0, iptr0, sizeof(OTYPE0) * OVLEN0 * FIC_CONVOLUTIONAL_CODEWORDS);

        iptr0 += IVLEN0 * OFDM_SYMBOLS_PER_FIC;
        optr0 += OVLEN0 * FIC_CONVOLUTIONAL_CODEWORDS;

        nconsumed += OFDM_SYMBOLS_PER_FIC;
        nproduced += FIC_CONVOLUTIONAL_CODEWORDS;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each(nconsumed);

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

  } /* namespace bad */
} /* namespace gr */

