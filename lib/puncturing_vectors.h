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

#ifndef INCLUDED_BAD_PUNCTURING_VECTORS_H
#define INCLUDED_BAD_PUNCTURING_VECTORS_H

#include <bad/protection_type.h>
#include <array>

#define N_SUB_BLOCKS 4

#define EEP_A(n)                                \
  {{{4*n-3,  3}, {2*n+3,  2}, {0, 0}, {0, 0}}}, \
  {{{6*n-3,  8}, {    3,  7}, {0, 0}, {0, 0}}}, \
  {{{2*n-3, 14}, {4*n+3, 13}, {0, 0}, {0, 0}}}, \
  {{{6*n-3, 24}, {    3, 23}, {0, 0}, {0, 0}}}  \

#define EEP_B(n)                            \
  {{{24*n-3,  2}, {3, 1}, {0, 0}, {0, 0}}}, \
  {{{24*n-3,  4}, {3, 3}, {0, 0}, {0, 0}}}, \
  {{{24*n-3,  6}, {3, 5}, {0, 0}, {0, 0}}}, \
  {{{24*n-3, 10}, {3, 9}, {0, 0}, {0, 0}}}  \

namespace gr {
  namespace bad {

    using V  = std::array<int, 32>; // regular puncturing vector
    using VT = std::array<int, 24>; // tail puncturing vector

    constexpr V VPI0  = {};
    constexpr V VPI1  = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; // PI=1: code rate: 8/9
    constexpr V VPI2  = {1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; // PI=2: code rate: 8/10
    constexpr V VPI3  = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; // PI=3: code rate: 8/11
    constexpr V VPI4  = {1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0}; // PI=4: code rate: 8/12
    constexpr V VPI5  = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0}; // PI=5: code rate: 8/13
    constexpr V VPI6  = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0}; // PI=6: code rate: 8/14
    constexpr V VPI7  = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0}; // PI=7: code rate: 8/15
    constexpr V VPI8  = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}; // PI=8: code rate: 8/16
    constexpr V VPI9  = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}; // PI=9: code rate: 8/17
    constexpr V VPI10 = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}; // PI=10 code rate: 8/18
    constexpr V VPI11 = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0}; // PI=11 code rate: 8/19
    constexpr V VPI12 = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0}; // PI=12 code rate: 8/20
    constexpr V VPI13 = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0}; // PI=13 code rate: 8/21
    constexpr V VPI14 = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0}; // PI=14 code rate: 8/22
    constexpr V VPI15 = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0}; // PI=15 code rate: 8/23
    constexpr V VPI16 = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; // PI=16 code rate: 8/24
    constexpr V VPI17 = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; // PI=17 code rate: 8/25
    constexpr V VPI18 = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; // PI=18 code rate: 8/26
    constexpr V VPI19 = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; // PI=19 code rate: 8/27
    constexpr V VPI20 = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}; // PI=20 code rate: 8/28
    constexpr V VPI21 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}; // PI=21 code rate: 8/29
    constexpr V VPI22 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; // PI=22 code rate: 8/30
    constexpr V VPI23 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; // PI=23 code rate: 8/31
    constexpr V VPI24 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // PI=24 code rate: 8/32

    constexpr std::array<V, 1 + 24> puncturing_vectors = {
      VPI0,   VPI1,  VPI2,  VPI3,  VPI4,  VPI5,  VPI6,  VPI7,  VPI8,  VPI9,
      VPI10, VPI11, VPI12, VPI13, VPI14, VPI15, VPI16, VPI17, VPI18, VPI19,
      VPI20, VPI21, VPI22, VPI23, VPI24
    };

    constexpr VT VTAIL = {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0};

    struct L_PI {
      int L;
      int PI;
    };

    using protection_profile = std::array<L_PI, 4>;

    constexpr protection_profile null_protection_profile = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};

    constexpr protection_profile fic_protection_profile = {{{21, 16}, {3, 15}, {0, 0}, {0, 0}}};

    constexpr protection_profile uep_profiles[] = {
      {{{ 3,  5}, { 4,  3}, {17,  2}, { 0,  0}}}, //  32 kbit/s (5)
      {{{ 3, 11}, { 3,  6}, {18,  5}, { 0,  0}}}, //  32 kbit/s (4)
      {{{ 3, 15}, { 4,  9}, {14,  6}, { 3,  8}}}, //  32 kbit/s (3)
      {{{ 3, 22}, { 4, 13}, {14,  8}, { 3, 13}}}, //  32 kbit/s (2)
      {{{ 3, 24}, { 5, 17}, {13, 12}, { 3, 17}}}, //  32 kbit/s (1)

      {{{ 4,  5}, { 3,  4}, {26,  2}, { 3,  3}}}, //  48 kbit/s (5)
      {{{ 3,  9}, { 4,  6}, {26,  4}, { 3,  6}}}, //  48 kbit/s (4)
      {{{ 3, 15}, { 4, 10}, {26,  6}, { 3,  9}}}, //  48 kbit/s (3)
      {{{ 3, 24}, { 4, 14}, {26,  8}, { 3, 15}}}, //  48 kbit/s (2)
      {{{ 3, 24}, { 5, 18}, {25, 13}, { 3, 18}}}, //  48 kbit/s (1)

      {{{ 6,  5}, {10,  4}, {23,  2}, { 3,  3}}}, //  56 kbit/s (5)
      {{{ 6,  9}, {10,  6}, {23,  4}, { 3,  5}}}, //  56 kbit/s (4)
      {{{ 6, 16}, {12,  7}, {21,  6}, { 3,  9}}}, //  56 kbit/s (3)
      {{{ 6, 23}, {10, 13}, {23,  8}, { 3, 13}}}, //  56 kbit/s (2)

      {{{ 6,  5}, { 9,  3}, {31,  2}, { 2,  3}}}, //  64 kbit/s (5)
      {{{ 6, 11}, { 9,  6}, {33,  5}, { 0,  0}}}, //  64 kbit/s (4)
      {{{ 6, 16}, {12,  8}, {27,  6}, { 3,  9}}}, //  64 kbit/s (3)
      {{{ 6, 23}, {10, 13}, {29,  8}, { 3, 13}}}, //  64 kbit/s (2)
      {{{ 6, 24}, {11, 18}, {28, 12}, { 3, 18}}}, //  64 kbit/s (1)

      {{{ 6,  6}, {10,  3}, {41,  2}, { 3,  3}}}, //  80 kbit/s (5)
      {{{ 6, 11}, {10,  6}, {41,  5}, { 3,  6}}}, //  80 kbit/s (4)
      {{{ 6, 16}, {11,  8}, {40,  6}, { 3,  7}}}, //  80 kbit/s (3)
      {{{ 6, 23}, {10, 13}, {41,  8}, { 3, 13}}}, //  80 kbit/s (2)
      {{{ 6, 24}, {10, 17}, {41, 12}, { 3, 18}}}, //  80 kbit/s (1)

      {{{ 7,  5}, { 9,  4}, {53,  2}, { 3,  4}}}, //  96 kbit/s (5)
      {{{ 7,  9}, {10,  6}, {52,  4}, { 3,  6}}}, //  96 kbit/s (4)
      {{{ 6, 16}, {12,  9}, {51,  6}, { 3, 10}}}, //  96 kbit/s (3)
      {{{ 6, 22}, {10, 12}, {53,  9}, { 3, 12}}}, //  96 kbit/s (2)
      {{{ 6, 24}, {13, 18}, {50, 13}, { 3, 19}}}, //  96 kbit/s (1)

      {{{14,  5}, {17,  4}, {50,  2}, { 3,  5}}}, // 112 kbit/s (5)
      {{{11,  9}, {21,  6}, {49,  4}, { 3,  8}}}, // 112 kbit/s (4)
      {{{11, 16}, {23,  8}, {47,  6}, { 3,  9}}}, // 112 kbit/s (3)
      {{{11, 23}, {21, 12}, {49,  9}, { 3, 14}}}, // 112 kbit/s (2)

      {{{12,  5}, {19,  3}, {62,  2}, { 3,  4}}}, // 128 kbit/s (5)
      {{{11, 11}, {21,  6}, {61,  5}, { 3,  7}}}, // 128 kbit/s (4)
      {{{11, 16}, {22,  9}, {60,  6}, { 3, 10}}}, // 128 kbit/s (3)
      {{{11, 22}, {21, 12}, {61,  9}, { 3, 14}}}, // 128 kbit/s (2)
      {{{11, 24}, {20, 17}, {62, 13}, { 3, 19}}}, // 128 kbit/s (1)
    };

    constexpr protection_profile eep_a_profiles[] = {
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 1,  3}, { 5,  2}, {0, 0}, {0, 0}}}, // n == 1
      {{{ 3,  8}, { 3,  7}, {0, 0}, {0, 0}}}, // n == 1
      {{{ 5, 13}, { 1, 12}, {0, 0}, {0, 0}}}, // n == 1
      {{{ 3, 24}, { 3, 23}, {0, 0}, {0, 0}}}, // n == 1
                              EEP_A(  2), EEP_A(  3), EEP_A(  4), EEP_A(  5), EEP_A(  6), EEP_A(  7), EEP_A(  8), EEP_A(  9),
      EEP_A( 10), EEP_A( 11), EEP_A( 12), EEP_A( 13), EEP_A( 14), EEP_A( 15), EEP_A( 16), EEP_A( 17), EEP_A( 18), EEP_A( 19),
      EEP_A( 20), EEP_A( 21), EEP_A( 22), EEP_A( 23), EEP_A( 24), EEP_A( 25), EEP_A( 26), EEP_A( 27), EEP_A( 28), EEP_A( 29),
      EEP_A( 30), EEP_A( 31), EEP_A( 32), EEP_A( 33), EEP_A( 34), EEP_A( 35), EEP_A( 36), EEP_A( 37), EEP_A( 38), EEP_A( 39),
      EEP_A( 40), EEP_A( 41), EEP_A( 42), EEP_A( 43), EEP_A( 44), EEP_A( 45), EEP_A( 46), EEP_A( 47), EEP_A( 48), EEP_A( 49),
      EEP_A( 50), EEP_A( 51), EEP_A( 52), EEP_A( 53), EEP_A( 54), EEP_A( 55), EEP_A( 56), EEP_A( 57), EEP_A( 58), EEP_A( 59),
      EEP_A( 60), EEP_A( 61), EEP_A( 62), EEP_A( 63), EEP_A( 64), EEP_A( 65), EEP_A( 66), EEP_A( 67), EEP_A( 68), EEP_A( 69),
      EEP_A( 70), EEP_A( 71), EEP_A( 72), EEP_A( 73), EEP_A( 74), EEP_A( 75), EEP_A( 76), EEP_A( 77), EEP_A( 78), EEP_A( 79),
      EEP_A( 80), EEP_A( 81), EEP_A( 82), EEP_A( 83), EEP_A( 84), EEP_A( 85), EEP_A( 86), EEP_A( 87), EEP_A( 88), EEP_A( 89),
      EEP_A( 90), EEP_A( 91), EEP_A( 92), EEP_A( 93), EEP_A( 94), EEP_A( 95), EEP_A( 96), EEP_A( 97), EEP_A( 98), EEP_A( 99),
      EEP_A(100), EEP_A(101), EEP_A(102), EEP_A(103), EEP_A(104), EEP_A(105), EEP_A(106), EEP_A(107), EEP_A(108), EEP_A(109),
      EEP_A(110), EEP_A(111), EEP_A(112), EEP_A(113), EEP_A(114), EEP_A(115), EEP_A(116), EEP_A(117), EEP_A(118), EEP_A(119),
      EEP_A(120), EEP_A(121), EEP_A(122), EEP_A(123), EEP_A(124), EEP_A(125), EEP_A(126), EEP_A(127), EEP_A(128), EEP_A(129),
      EEP_A(130), EEP_A(131), EEP_A(132), EEP_A(133), EEP_A(134), EEP_A(135), EEP_A(136), EEP_A(137), EEP_A(138), EEP_A(139),
      EEP_A(140), EEP_A(141), EEP_A(142), EEP_A(143), EEP_A(144), EEP_A(145), EEP_A(146), EEP_A(147), EEP_A(148), EEP_A(149),
      EEP_A(150), EEP_A(151), EEP_A(152), EEP_A(153), EEP_A(154), EEP_A(155), EEP_A(156), EEP_A(157), EEP_A(158), EEP_A(159),
      EEP_A(160), EEP_A(161), EEP_A(162), EEP_A(163), EEP_A(164), EEP_A(165), EEP_A(166), EEP_A(167), EEP_A(168), EEP_A(169),
      EEP_A(170), EEP_A(171), EEP_A(172), EEP_A(173), EEP_A(174), EEP_A(175), EEP_A(176), EEP_A(177), EEP_A(178), EEP_A(179),
      EEP_A(180), EEP_A(181), EEP_A(182), EEP_A(183), EEP_A(184), EEP_A(185), EEP_A(186), EEP_A(187), EEP_A(188), EEP_A(189),
      EEP_A(190), EEP_A(191), EEP_A(192), EEP_A(193), EEP_A(194), EEP_A(195), EEP_A(196), EEP_A(197), EEP_A(198), EEP_A(199),
      EEP_A(200), EEP_A(201), EEP_A(202), EEP_A(203), EEP_A(204), EEP_A(205), EEP_A(206), EEP_A(207), EEP_A(208), EEP_A(209),
      EEP_A(210), EEP_A(211), EEP_A(212), EEP_A(213), EEP_A(214), EEP_A(215), EEP_A(216)
    };

    constexpr protection_profile eep_b_profiles[] = {
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
      {{{ 0,  0}, { 0,  0}, {0, 0}, {0, 0}}}, // n == 0
                  EEP_B(  1), EEP_B(  2), EEP_B(  3), EEP_B(  4), EEP_B(  5), EEP_B(  6), EEP_B(  7), EEP_B(  8), EEP_B(  9),
      EEP_B( 10), EEP_B( 11), EEP_B( 12), EEP_B( 13), EEP_B( 14), EEP_B( 15), EEP_B( 16), EEP_B( 17), EEP_B( 18), EEP_B( 19),
      EEP_B( 20), EEP_B( 21), EEP_B( 22), EEP_B( 23), EEP_B( 24), EEP_B( 25), EEP_B( 26), EEP_B( 27), EEP_B( 28), EEP_B( 29),
      EEP_B( 30), EEP_B( 31), EEP_B( 32), EEP_B( 33), EEP_B( 34), EEP_B( 35), EEP_B( 36), EEP_B( 37), EEP_B( 38), EEP_B( 39),
      EEP_B( 40), EEP_B( 41), EEP_B( 42), EEP_B( 43), EEP_B( 44), EEP_B( 45), EEP_B( 46), EEP_B( 47), EEP_B( 48), EEP_B( 49),
      EEP_B( 50), EEP_B( 51), EEP_B( 52), EEP_B( 53), EEP_B( 54), EEP_B( 55), EEP_B( 56), EEP_B( 57)
    };

    constexpr const protection_profile& get_protection_profile(protection_type_e type, int index, int n)
    {
      return
        (type == PROTECTION_TYPE_FIC)   ? fic_protection_profile :
        (type == PROTECTION_TYPE_UEP)   ? uep_profiles[index] :
        (type == PROTECTION_TYPE_EEP_A) ? eep_a_profiles[n * 4 + 4 - index] :
        (type == PROTECTION_TYPE_EEP_B) ? eep_b_profiles[n * 4 + 4 - index] :
        null_protection_profile;
    }

  } // namespace bad
} // namespace gr

#endif /* INCLUDED_BAD_PUNCTURING_VECTORS_H */

