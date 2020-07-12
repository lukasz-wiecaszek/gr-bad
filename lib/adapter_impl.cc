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
#include "adapter_impl.h"

namespace gr {
  namespace bad {

    template<typename ITYPE0, typename OTYPE0>
    typename adapter<ITYPE0, OTYPE0>::sptr
             adapter<ITYPE0, OTYPE0>::make(int ivlen, int iitems, int ovlen, int oitems)
    {
      return gnuradio::get_initial_sptr
        (new adapter_impl<ITYPE0, OTYPE0>(ivlen, iitems, ovlen, oitems));
    }

    template<typename ITYPE0, typename OTYPE0>
    adapter_impl<ITYPE0, OTYPE0>::adapter_impl(int ivlen, int iitems, int ovlen, int oitems)
      : gr::block("adapter",
                  gr::io_signature::make(1, 1, sizeof(ITYPE0) * ivlen),
                  gr::io_signature::make(1, 1, sizeof(OTYPE0) * ovlen)),
        d_ivlen(ivlen),
        d_iitems(iitems),
        d_ovlen(ovlen),
        d_oitems(oitems)
    {
      assert(ivlen * iitems >= ovlen * oitems);
      this->set_relative_rate(ovlen * oitems, ivlen * iitems);
      this->set_output_multiple(oitems);
      this->set_tag_propagation_policy(gr::block::TPP_DONT);
    }

    template<typename ITYPE0, typename OTYPE0>
    adapter_impl<ITYPE0, OTYPE0>::~adapter_impl()
    {
    }

    template<typename ITYPE0, typename OTYPE0>
    void
    adapter_impl<ITYPE0, OTYPE0>::forecast(int noutput_items, gr_vector_int &ninput_items_required)
    {
      // Every d_oitems at output require d_iitems at input
      int nrequired = noutput_items * d_iitems / d_oitems;

      for (auto&& element : ninput_items_required)
        element = nrequired;
    }

    template<typename ITYPE0, typename OTYPE0>
    int
    adapter_impl<ITYPE0, OTYPE0>::general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const ITYPE0* iptr0 = (const ITYPE0*) input_items[0];
      OTYPE0* optr0 = (OTYPE0*) output_items[0];
      int nproduced = 0;
      int nconsumed = 0;

      while (nproduced < noutput_items) {
        if (noutput_items < nproduced + d_oitems)
          break;
        if (ninput_items[0] < nconsumed + d_iitems)
          break;

        memcpy(optr0, iptr0, sizeof(OTYPE0) * d_ovlen * d_oitems);

        iptr0 += d_ivlen * d_iitems;
        optr0 += d_ovlen * d_oitems;

        nconsumed += d_iitems;
        nproduced += d_oitems;
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      this->consume_each(nconsumed);

      // Tell runtime system how many output items we produced.
      return nproduced;
    }

    template class adapter<std::uint8_t, std::uint8_t>;
    template class adapter<std::uint16_t, std::uint16_t>;
    template class adapter<std::uint32_t, std::uint32_t>;
    template class adapter<float, float>;
    template class adapter<gr_complex, gr_complex>;

  } /* namespace bad */
} /* namespace gr */

