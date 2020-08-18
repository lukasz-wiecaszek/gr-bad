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

#ifndef INCLUDED_BAD_OFDM_SYMBOLS_SELECTOR_H
#define INCLUDED_BAD_OFDM_SYMBOLS_SELECTOR_H

#include <bad/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace bad {

    /*!
     * \brief <+description of block+>
     * \ingroup bad
     *
     */
    class BAD_API ofdm_symbols_selector : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<ofdm_symbols_selector> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of bad::ofdm_symbols_selector.
       *
       * To avoid accidental use of raw pointers, bad::ofdm_symbols_selector's
       * constructor is in a private implementation
       * class. bad::ofdm_symbols_selector::make is the public interface for
       * creating new instances.
       */
      static sptr make(int first, int count);
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_OFDM_SYMBOLS_SELECTOR_H */

