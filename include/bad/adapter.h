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

#ifndef INCLUDED_BAD_ADAPTER_H
#define INCLUDED_BAD_ADAPTER_H

#include <bad/api.h>
#include <gnuradio/block.h>
#include <cstdint>

namespace gr {
  namespace bad {

    /*!
     * \brief <+description of block+>
     * \ingroup bad
     *
     */
    template<typename ITYPE0, typename OTYPE0>
    class BAD_API adapter : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<adapter<ITYPE0, OTYPE0>> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of bad::adapter.
       *
       * To avoid accidental use of raw pointers, bad::adapter's
       * constructor is in a private implementation
       * class. bad::adapter::make is the public interface for
       * creating new instances.
       */
      static sptr make(int ivlen, int iitems, int ovlen, int oitems, const char *tag_name);
    };

    using adapter_bb = adapter<std::uint8_t, std::uint8_t>;
    using adapter_ss = adapter<std::uint16_t, std::uint16_t>;
    using adapter_ii = adapter<std::uint32_t, std::int32_t>;
    using adapter_ff = adapter<float, float>;
    using adapter_cc = adapter<gr_complex, gr_complex>;

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_ADAPTER_H */

