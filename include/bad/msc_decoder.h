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

#ifndef INCLUDED_BAD_MSC_DECODER_H
#define INCLUDED_BAD_MSC_DECODER_H

#include <bad/api.h>
#include <gnuradio/hier_block2.h>

namespace gr {
  namespace bad {

    /*!
     * \brief <+description of block+>
     * \ingroup bad
     *
     */
    class BAD_API msc_decoder : virtual public gr::hier_block2
    {
     public:
      typedef boost::shared_ptr<msc_decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of bad::msc_decoder.
       *
       * To avoid accidental use of raw pointers, bad::msc_decoder's
       * constructor is in a private implementation
       * class. bad::msc_decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make();

      /*! \brief Set the parameters required to decode unequal error protected main service channel.
       *
       *  \param subch_start_addr Subchannel start address as defined in FIG0/1.
       *                          It address the first CU (Capacity Unit) of the subchannel.
       *                          Valid values are in the range 0 to 863.
       * \param table_index Table index as defined in FIG0/1.
       */
      virtual void set_uep_params(int subch_start_addr, int table_index) = 0;

      /*! \brief Set the parameters required to decode equal error protected (type A) main service channel.
       *
       *  \param subch_start_addr Subchannel start address as defined in FIG0/1.
       *                          It address the first Capacity Unit of the subchannel.
       *                          Valid values are in the range 0 to 863.
       * \param subch_size Subchannel size as defined in FIG0/1.
       *                   It defines the number of Capacity Units occupied by the sub-channel.
       *                   Valid values are in the range 1 to 864.
       * \param protection_level Protection level as defined in FIG0/1.
       *                         Valid values are:
       *                         0 - protection level 1-A
       *                         1 - protection level 2-A
       *                         2 - protection level 3-A
       *                         3 - protection level 4-A
       */
      virtual void set_eep_a_params(int subch_start_addr, int subch_size, int protection_level) = 0;

      /*! \brief Set the parameters required to decode equal error protected (type B) main service channel.
       *
       *  \param subch_start_addr Subchannel start address as defined in FIG0/1.
       *                          It address the first Capacity Unit of the subchannel.
       *                          Valid values are in the range 0 to 863.
       * \param subch_size Subchannel size as defined in FIG0/1.
       *                   It defines the number of Capacity Units occupied by the sub-channel.
       *                   Valid values are in the range 1 to 864.
       * \param protection_level Protection level as defined in FIG0/1.
       *                         Valid values are:
       *                         0 - protection level 1-B
       *                         1 - protection level 2-B
       *                         2 - protection level 3-B
       *                         3 - protection level 4-B
       */
      virtual void set_eep_b_params(int subch_start_addr, int subch_size, int protection_level) = 0;

    };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_MSC_DECODER_H */

