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

#ifndef INCLUDED_BAD_QPSK_SYMBOL_DEMAPPER_H
#define INCLUDED_BAD_QPSK_SYMBOL_DEMAPPER_H

#include <bad/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace bad {

    /*!
     * \brief <+description of block+>
     * \ingroup bad
     *
     */
    class BAD_API qpsk_symbol_demapper : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<qpsk_symbol_demapper> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of bad::qpsk_symbol_demapper.
       *
       * To avoid accidental use of raw pointers, bad::qpsk_symbol_demapper's
       * constructor is in a private implementation
       * class. bad::qpsk_symbol_demapper::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_QPSK_SYMBOL_DEMAPPER_H */

