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

#ifndef INCLUDED_BAD_DAB_PARAMETERS_H
#define INCLUDED_BAD_DAB_PARAMETERS_H

namespace gr {
  namespace bad {

  // number of ofdm symbols per synchronization channel
  constexpr int  OFDM_SYMBOLS_PER_SC = 1;

  // number of ofdm symbols per fast information channel
  constexpr int  OFDM_SYMBOLS_PER_FIC = 3;

  // number of ofdm symbols per main service channel
  constexpr int  OFDM_SYMBOLS_PER_MSC = 72;

  // number of ofdm symbols per transmission frame (the Null symbol being excluded)
  constexpr int L = OFDM_SYMBOLS_PER_SC + OFDM_SYMBOLS_PER_FIC + OFDM_SYMBOLS_PER_MSC;

  // number of transmitted carriers per ofdm symbol
  constexpr int K = 1536;

  // number of coded bits per ofdm symbol
  constexpr int OFDM_SYMBOL_BITS = 2 * K;

  // DAB elementary sampling frequency
  constexpr int FS = 2048000;

  // Tnull is the Null symbol duration [#samples @ FS]
  constexpr int TNULL = 2656;

  // Ts is the duration of OFDM symbols of indices l = 1, 2, 3,..., L [#samples @ FS]
  constexpr int TS = 2552;

  // Tf is the transmission frame duration [#samples @ FS]
  constexpr int TF = TNULL + L * TS;

  // GI is the duration of the time interval called guard interval [#samples @ FS]
  constexpr int GI = 504;

  // OFDM fft size
  constexpr int FFT_SIZE = 2048;

  // number of FIBs per transmission frame
  constexpr int FIBS_PER_TF = 12;

  // number of CIFs per transmission frame
  constexpr int CIFS_PER_TF = 4;

  // FIC convolutional codeword length
  constexpr int  FIC_CONVOLUTIONAL_CODEWORD_LENGTH = 3096;

  // FIC punctured convolutional codeword length
  constexpr int  FIC_PUNCTURED_CONVOLUTIONAL_CODEWORD_LENGTH = 2304;

  // number of FIC convolutional codewords
  constexpr int  FIC_CONVOLUTIONAL_CODEWORDS = 4;

  // size of capacity unit
  constexpr int  CU_SIZE = 64;

  // number of capacity units in one CIF
  constexpr int CUS_PER_CIF = 864;

  constexpr const char* TAG_NS = "dab_sync";

  constexpr const char* TAG_SYMBOL = "symbol";

  constexpr const char* TAG_CU = "cu";

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_DAB_PARAMETERS_H */

