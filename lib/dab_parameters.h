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

  struct kin_t {
    int k;
    int i;
    int n;
  };

  constexpr kin_t kin[] = {
    {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1},
    {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1},
    {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1},
    {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1}, {-768, 0, 1},

    {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2},
    {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2},
    {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2},
    {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2}, {-736, 1, 2},

    {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0},
    {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0},
    {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0},
    {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0}, {-704, 2, 0},

    {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1},
    {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1},
    {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1},
    {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1}, {-672, 3, 1},

    {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3},
    {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3},
    {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3},
    {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3}, {-640, 0, 3},

    {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2},
    {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2},
    {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2},
    {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2}, {-608, 1, 2},

    {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2},
    {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2},
    {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2},
    {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2}, {-576, 2, 2},

    {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3},
    {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3},
    {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3},
    {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3}, {-544, 3, 3},

    {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2},
    {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2},
    {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2},
    {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2}, {-512, 0, 2},

    {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1},
    {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1},
    {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1},
    {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1}, {-480, 1, 1},

    {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2},
    {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2},
    {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2},
    {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2}, {-448, 2, 2},

    {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3},
    {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3},
    {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3},
    {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3}, {-416, 3, 3},

    {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1},
    {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1},
    {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1},
    {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1}, {-384, 0, 1},

    {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2},
    {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2},
    {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2},
    {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2}, {-352, 1, 2},

    {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3},
    {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3},
    {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3},
    {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3}, {-320, 2, 3},

    {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3},
    {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3},
    {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3},
    {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3}, {-288, 3, 3},

    {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2},
    {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2},
    {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2},
    {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2}, {-256, 0, 2},

    {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2},
    {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2},
    {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2},
    {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2}, {-224, 1, 2},

    {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2},
    {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2},
    {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2},
    {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2}, {-192, 2, 2},

    {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1},
    {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1},
    {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1},
    {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1}, {-160, 3, 1},

    {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1},
    {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1},
    {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1},
    {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1}, {-128, 0, 1},

    { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3},
    { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3},
    { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3},
    { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3}, { -96, 1, 3},

    { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1},
    { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1},
    { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1},
    { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1}, { -64, 2, 1},

    { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2},
    { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2},
    { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2},
    { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2}, { -32, 3, 2},

    {   0, 0, 0},

    {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3},
    {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3},
    {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3},
    {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3}, {   1, 0, 3},

    {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1},
    {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1},
    {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1},
    {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1}, {  33, 3, 1},

    {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1},
    {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1},
    {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1},
    {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1}, {  65, 2, 1},

    {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1},
    {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1},
    {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1},
    {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1}, {  97, 1, 1},

    { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2},
    { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2},
    { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2},
    { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2}, { 129, 0, 2},

    { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2},
    { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2},
    { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2},
    { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2}, { 161, 3, 2},

    { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1},
    { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1},
    { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1},
    { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1}, { 193, 2, 1},

    { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0},
    { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0},
    { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0},
    { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0}, { 225, 1, 0},

    { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2},
    { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2},
    { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2},
    { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2}, { 257, 0, 2},

    { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2},
    { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2},
    { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2},
    { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2}, { 289, 3, 2},

    { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3},
    { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3},
    { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3},
    { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3}, { 321, 2, 3},

    { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3},
    { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3},
    { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3},
    { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3}, { 353, 1, 3},

    { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0},
    { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0},
    { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0},
    { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0}, { 385, 0, 0},

    { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2},
    { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2},
    { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2},
    { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2}, { 417, 3, 2},

    { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1},
    { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1},
    { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1},
    { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1}, { 449, 2, 1},

    { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3},
    { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3},
    { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3},
    { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3}, { 481, 1, 3},

    { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3},
    { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3},
    { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3},
    { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3}, { 513, 0, 3},

    { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3},
    { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3},
    { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3},
    { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3}, { 545, 3, 3},

    { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3},
    { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3},
    { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3},
    { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3}, { 577, 2, 3},

    { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0},
    { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0},
    { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0},
    { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0}, { 609, 1, 0},

    { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3},
    { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3},
    { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3},
    { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3}, { 641, 0, 3},

    { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0},
    { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0},
    { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0},
    { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0}, { 673, 3, 0},

    { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1},
    { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1},
    { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1},
    { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1}, { 705, 2, 1},

    { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1},
    { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1},
    { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1},
    { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1}, { 737, 1, 1},
  };

  constexpr int h[4][32] = {
    {0, 2, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 2, 1, 1, 0, 2, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 2, 2, 1, 1},
    {0, 3, 2, 3, 0, 1, 3, 0, 2, 1, 2, 3, 2, 3, 3, 0, 0, 3, 2, 3, 0, 1, 3, 0, 2, 1, 2, 3, 2, 3, 3, 0},
    {0, 0, 0, 2, 0, 2, 1, 3, 2, 2, 0, 2, 2, 0, 1, 3, 0, 0, 0, 2, 0, 2, 1, 3, 2, 2, 0, 2, 2, 0, 1, 3},
    {0, 1, 2, 1, 0, 3, 3, 2, 2, 3, 2, 1, 2, 1, 3, 2, 0, 1, 2, 1, 0, 3, 3, 2, 2, 3, 2, 1, 2, 1, 3, 2}
  };

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_DAB_PARAMETERS_H */

