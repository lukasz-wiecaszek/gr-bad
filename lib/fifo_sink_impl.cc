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

#include <sstream>

#include <gnuradio/io_signature.h>
#include "fifo_sink_impl.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

namespace gr {
  namespace bad {

    fifo_sink::sptr
    fifo_sink::make(const char *filename, bool non_blocking)
    {
      return gnuradio::get_initial_sptr
        (new fifo_sink_impl<uint8_t>(filename, non_blocking));
    }

    template<typename ITYPE0>
    fifo_sink_impl<ITYPE0>::fifo_sink_impl(const char *filename, bool non_blocking)
      : gr::sync_block("fifo_sink",
                       gr::io_signature::make(1, 1, sizeof(ITYPE0) * IVLEN0),
                       gr::io_signature::make(0, 0, 0)),
        d_fd(-1)
    {
      int flags = O_WRONLY;

      if (non_blocking)
        flags |= O_NONBLOCK;

      d_fd = open(filename, flags);
      assert(d_fd >= -1);
      if (d_fd == -1) {
        std::stringstream s;
        s << "cannot open fifo file '" << filename << "': '" << strerror(errno) << "'" << std::endl;
        throw std::runtime_error(s.str());
      }
    }

    template<typename ITYPE0>
    fifo_sink_impl<ITYPE0>::~fifo_sink_impl()
    {
      if (d_fd >= 0)
        close(d_fd);
    }

    template<typename ITYPE0>
    int
    fifo_sink_impl<ITYPE0>::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const uint8_t* iptr0 = (const uint8_t*) input_items[0];
      int nwritten = 0;

      while (nwritten < noutput_items) {
        ssize_t count = write(d_fd, iptr0 + nwritten, noutput_items - nwritten);
        if (count < 0) {
          //printf("attempt to write() %d bytes returned error: '%s'\n",
            //noutput_items - nwritten, strerror(errno));
          nwritten = noutput_items;
        }
        else
        if (count == 0) {
          //printf("attempt to write() %d bytes returned 0 bytes written\n",
            //noutput_items - nwritten);
          nwritten = noutput_items;
        }
        else {
          nwritten += count;
        }
      }

      // Tell runtime system how many output items we produced.
      return nwritten;
    }

  } /* namespace bad */
} /* namespace gr */

