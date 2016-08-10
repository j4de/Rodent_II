/**
Rodent, a UCI chess playing engine derived from Sungorus 1.4
Copyright (C) 2009-2011 Pablo Vazquez (Sungorus author)
Copyright (C) 2011-2016 Pawel Koziol

Rodent is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

Rodent is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Piece/square tables come in three sets. The first is based on those 
// of Hakkapeliitta chess engine (https://github.com/mAarnos/Hakkapeliitta),
// made symmetric and tweaked afterwards. The second set has been used
// by Rodent 0.9.33, and amounts to modified Fruit 2.1. tables.
// The third set is similar to Ippolit piece/square tables.

// 0 (symmetric Hakkapeliitta 80%)
// 1 (Fruity 80%) : 47,3%  vs 0
// 2 (Ippo 100%)  : 48,9%  vs 0

#pragma once

static const int pst_default_perc[3] = { 80, 80, 100 };

static const int pstPawnMg[3][64] = {
 //A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
-32, -16, -17, -27, -27, -17, -16, -32,
-25, -16, -16, -18, -18, -16, -16, -25,
-20, -17,  -7,  -2,  -2,  -7, -17, -20,
-12,  -3,   2,  16,  16,   2,  -3, -12,
  9,  22,  43,  39,  39,  43,  22,   9,
 15,  16,  76,  93,  93,  76,  16,  15,
  0,   0,   0,   0,   0,   0,   0,   0 },
//A8                                H8

//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
-15,  -5,   5,   5,   5,   5,  -5, -15,
-15,  -5,   5,  15,  15,   5,  -5, -15,
-15,  -5,  10,  25,  25,  10,  -5, -15,
-15,  -5,   5,  15,  15,   5,  -5, -15,
-15,  -5,   5,  15,  15,   5,  -5, -15,
-15,  -5,   5,  15,  15,   5,  -5, -15,
  0,   0,   0,   0,   0,   0,   0,   0},
//A8                                H8

//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
-23, -11,  -5,   2,   2,  -5, -11, -23,
-22, -10,  -4,   3,   3,  -4, -10, -22,
-21,  -9,  -3,   4,   4,  -3,  -9, -21,
-19,  -7,  -1,   6,   6,  -1,  -7, -19,
-18,  -6,   0,   7,   7,   0,  -6, -18,
-17,  -5,   1,   8,   8,   1,  -5, -17,
  0,   0,   0,   0,   0,   0,   0,   0}
//A8                                H8
 };

static const int pstPawnEg[3][64] = {
//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
-16,  -8,  -9,   2,   2,  -9,  -8, -16,
-20, -11, -18, -16, -16, -18, -11, -20,
-15,  -6, -20, -26, -26, -20,  -6, -15,
  2,   0, -10, -23, -23, -10,   0,   2,
 31,  37,  10,   0,   0,  10,  37,  31,
 49,  43,  39,  33,  33,  39,  43,  49,
  0,   0,   0,   0,   0,   0,   0,   0},
//A8                                H8

//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  3,   1,  -1,  -3,  -3,  -1,   1,   3,
  0,   0,   0,   0,   0,   0,   0,   0},
//A8                                H8

//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
 -2,  -4,  -6,  -8,  -8,  -6,  -4,  -2,
 -4,  -6,  -8, -10, -10,  -8,  -6,  -4,
 -5,  -7,  -9, -11, -11,  -9,  -7,  -5,
 -6,  -8, -10, -12, -12, -10,  -8,  -6,
 -7,  -9, -11, -13, -13, -11,  -9,  -7,
 -7,  -9, -11, -13, -13, -11,  -9,  -7,
  0,   0,   0,   0,   0,   0,   0,   0 }
//A8                                H8
 };

static const int pstKnightMg[3][64] = {

//A1                                 H1
{-62, -22, -30, -30, -30, -30, -22, -62,
 -25, -23, -10,  -7,  -7, -10, -23, -25,
 -19,  -2,   3,  22,  22,   3,  -2, -19,
 -14,  16,  17,  20,  20,  17,  16, -14,
  16,  14,  33,  36,  36,  33,  14,  16,
  12,  34,  73,  88,  88,  73,  34,  12,
 -17,  -1,  49,  61,  61,  49,  -1, -17,
 -84, -36,  -2,  18,  18,  -2, -36, -84},
//A8                                 H8

//A1                                 H1
{-50, -40, -30, -20, -20, -30, -40, -50,
 -35, -25, -15,   0,   0, -15, -25, -35,
 -20, -10,   0,  10,  10,   0, -10, -20,
 -10,   0,  10,  20,  20,  10,   0, -10,
  -5,   5,  15,  25,  25,  15,   5,  -5,
  -5,   5,  15,  25,  25,  15,   5,  -5,
 -20, -10,   0,  10,  10,   0, -10, -20,
-135, -25, -15,  -5,  -5, -15, -25, -135},
//A8                                 H8

//A1                                 H1
{-58, -42, -31, -27, -27, -31, -42, -58,
 -36, -20,  -9,  -5,  -5,  -9, -20, -36,
 -20,  -4,   7,  11,  11,   7,  -4, -20,
 -11,   5,  16,  20,  20,  16,   5, -11,
  -5,  11,  22,  26,  26,  22,  11,  -5,
  -7,   9,  20,  24,  24,  20,   9,  -7,
 -16,  10,  11,  15,  15,  11,  10, -16,
-120, -21, -10,  -6,  -6, -10, -21,-120 }
//A8                                 H8

};

static const int pstKnightEg[3][64] = {
//A1                                 H1
{-33, -44, -20, -10, -10, -20, -44, -33,
 -15,  -9,   1,   1,   1,   1,  -9, -15,
 -11,  -2,   7,  28,  28,   7,  -2, -11,
  -4,  21,  37,  42,  42,  37,  21,  -4,
  18,  25,  45,  51,  51,  45,  25,  18,
   1,  34,  37,  30,  30,  37,  34,   1,
  -9,  24,   9,  32,  32,   9,  24,  -9,
 -33,  10,   9,   2,   2,   9,  10, -33},
//A8                                 H8

//A1                                 H1
{-40, -30, -20, -10, -10, -20, -30, -40,
 -30, -20, -10,   0,   0, -10, -20, -30,
 -20, -10,   0,  10,  10,   0, -10, -20,
 -10,   0,  10,  20,  20,  10,   0, -10,
 -10,   0,  10,  20,  20,  10,   0, -10,
 -20, -10,   0,  10,  10,   0, -10, -20,
 -30, -20, -10,   0,   0, -10, -20, -30,
 -40, -30, -20, -10, -10, -20, -30, -40 },
//A8                                 H8

//A1                                H1
{-22, -17, -12,  -9,  -9, -12, -17, -22,
 -15,  -8,  -4,  -2,  -2,  -4,  -8, -15,
 -10,  -4,   1,   3,   3,   1,  -4, -10,
  -6,  -1,   4,   8,   8,   4,  -1,  -6,
  -4,   1,   6,  10,  10,   6,   1,  -4,
  -3,   3,   8,  10,  10,   8,   3,  -3,
  -8,  -1,   3,   5,   5,   3,  -1,  -8,
 -15, -10,  -5,  -2,  -2,  -5, -10, -15 }
//A8                                 H8
};

static const int pstBishopMg[3][64] = {
//A1                                 H1
{ -9,  -1, -14, -12, -12, -14,  -1,  -9,
  -5,   2,   5,  -7,  -7,   5,   2,  -5,
  -8,   7,  -2,   1,   1,  -2,   7,  -8,
   3,  -7,  -2,   9,   9,  -2,  -7,   3,
  -8,  -1,  20,  22,  22,  20,  -1,  -8,
   4,  37,  39,  25,  25,  39,  37,   4,
  -5, -15,   9, -12, -12,   9, -15,  -5,
 -31, -42, -26, -48, -48, -26, -42, -31},
//A8                                 H8

//A1                                 H1
{ -2,  -5, -16,  -5,  -5, -16,  -5,  -2,
  -5,   6,   3,   6,   6,   3,   6,  -5,
  -5,   5,   8,  10,  10,   8,   5,  -5,
  -5,   0,  10,  13,  13,  10,   0,  -5,
  -5,   0,   5,  13,  13,   5,   0,  -5,
  -5,   0,   5,   5,   5,   5,   0,  -5,
  -5,   0,   0,   0,   0,   0,   0,  -5,
  -5,  -5,  -5,  -5,  -5,  -5,  -5,  -5 },
//A8                                 H8

//A1                                 H1
{ -7,  -8, -11, -13, -13, -11,  -8,  -7,
  -3,   3,   0,  -2,  -2,   0,   3,  -3,
  -6,   0,   7,   6,   6,   7,   0,  -6,
  -8,  -2,   6,  15,  15,   6,  -2,  -8,
  -8,  -2,   6,  15,  15,   6,  -2,  -8,
  -6,   0,   7,   6,   6,   7,   0,  -6,
  -3,   3,   0,  -2,  -2,   0,   3,  -3,
  -2,  -3,  -6,  -8,  -8,  -6,  -3,  -2 }
//A8                                 H8
};

static const int pstBishopEg[3][64] = {
//A1                                 H1
{-29, -13,  -4,  -6,  -6,  -4, -13, -29,
 -11, -10,  -9,  -1,  -1,  -9, -10, -11,
  -1,   7,   5,  13,  13,   5,   7,  -1,
  -7,   5,  11,  15,  15,  11,   5,  -7,
   7,   6,   7,  20,  20,   7,   6,   7,
  18,  16,   5,   7,   7,   5,  16,  18,
  -7,  11,   0,   8,   8,   0,  11,  -7,
   6,  21,  19,  19,  19,  19,  21,   6},
//A8                                 H8

//A1                                 H1
{-15, -10,  -8,  -5,  -5,  -8, -10, -15,
 -10,  -8,   0,   5,   5,   0,  -8, -10,
  -5,   0,   5,  10,  10,   5,   0,  -8,
  -5,   5,  10,  15,  15,  10,   5,  -5,
  -5,   5,  10,  15,  15,  10,   5,  -5,
  -8,   0,   5,  10,  10,   5,   0,  -8,
  10,  -8,   0,   5,   5,   0,  -8, -10,
  -15, -10, -8,  -5,  -5,  -8, -10, -15 },
 //A8                                 H8

 //A1                                 H1
{  0,  -1,  -2,  -2,  -2,  -2,  -1,   0,
  -1,   1,   0,   0,   0,   0,   1,  -1,
  -2,   0,   3,   2,   2,   3,   0,  -2,
  -2,   0,   2,   5,   5,   2,   0,  -2,
  -2,   0,   2,   5,   5,   2,   0,  -2,
  -2,   0,   3,   2,   2,   3,   0,  -2,
  -1,   1,   0,   0,   0,   0,   1,  -1,
   0,  -1,  -2,  -2,  -2,  -2,  -1,   0 }
//A8                                 H8
};

static const int pstRookMg[3][64] = {
//A1                                H1
{-15,  -1,   0,   3,   3,   0,  -1, -15,
 -33, -11, -14, -11, -11, -14, -11, -33,
 -26, -13, -15,  -2,  -2, -15, -13, -26,
 -33,  -1, -26,  -9,  -9, -26,  -1, -33,
   1,  15,  -3,   9,   9,  -3,  15,   1,
  10,  41,  30,  37,  37,  30,  41,  10,
  27,  17,  51,  48,  48,  51,  17,  27,
  44,  39,  34,  16,  16,  34,  39,  44},
 //A8                                H8

 //A1                                H1
{-3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3,
 -3,  -1,   1,   3,   3,   1,  -1,  -3},
//A8                                H8

{-4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4,
 -4,   0,   4,   8,   8,   4,   0,  -4 }
 };

static const int pstRookEg[3][64] = {
//A1                                H1
{-12, -16,  -10, -12, -12, -10, -16, -12,
   0, -19,   -9, -12, -12,  -9, -19,   0,
   1,  -4,   -5, -12, -12,  -5,  -4,   1,
  22,   7,   17,   5,   5,  17,   7,  22,
  17,  17,   23,  13,  13,  23,  17,  17,
  22,  19,   21,  19,  19,  21,  19,  22,
  14,  26,   18,  31,  31,  18,  26,  14,
  13,  13,   18,  28,  28,  18,  13,  13},
 //A8                                H8

//A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0},
 //A8                                H8

 //A1                                H1
{ 0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
 -2,  -2,  -2 -2,   -2,   -2,  -2,  -2 }
 //A8                                H8
 };

static const int pstQueenMg[3][64] = {
//A1                                H1
{ 4,  -8,   3,  11,  11,   3,  -8,   4,
  2,  15,  13,  13,  13,  13,  15,   2,
  5,   5,  10,   2,   2,  10,   5,   5,
 -8,  -1,  -3,  -8,  -8,  -3,  -1,  -8,
 -6, -16, -13,  -9,  -9, -13, -16,  -6,
  2,  -3,  14,   3,   3,  14,  -3,   2,
 23, -13,   3,  -9,  -9,   3, -13,  23,
  5,  30,  11,  -8,  -8,  11,  30,   5},
//A8                                H8

//A1                                H1
{-5,  -5,  -5,  -5,  -5,  -5,  -5,  -5,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0},
//A8                                H8

//A1                                 H1
{-16, -12,  -9,  -7,  -7,  -9, -12, -16,
  -7,  -1,   1,   3,   3,   1,  -1,  -7,
  -4,   1,   5,   6,   6,   5,   1,  -4,
  -2,   3,   6,   9,   9,   6,   3,  -2,
  -2,   3,   6,   9,   9,   6,   3,  -2,
  -4,   1,   5,   6,   6,   5,   1,  -4,
  -7,  -1,   1,   3,   3,   1,  -1,  -7,
 -11,  -7,  -4,  -2,  -2,  -4,  -7, -11 }
 //A8                                H8
};

static const int pstQueenEg[3][64] = {
//A1                                 H1
{-26, -37, -35, -14, -14, -35, -37, -26,
 -32, -34, -26,  -8,  -8, -26, -34, -32,
 -19,  -6,  -2,   0,   0,  -2,  -6, -19,
  -8,  -5,   6,  29,  29,   6,  -5,  -8,
  -7,  21,  36,  49,  49,  36,  21,  -7,
  15,  36,  37,  47,  47,  37,  36,  15,
  24,  25,  27,  52,  52,  27,  25,  24,
  15,  27,  22,  14,  14,  22,  27,  15},
//A8                                 H8

//A1                                 H1
{-24, -16, -12,  -8,  -8, -12, -16, -24,
 -16,  -8,  -4,   0,   0,  -4,  -8, -16,
 -12,  -4,   0,   4,   4,   0,  -4, -12,
  -8,   0,   4,   8,   8,   4,   0,  -8,
  -8,   0,   4,   8,   8,   4,   0,  -8,
 -12,  -4,   0,   4,   4,   0,  -4, -12,
 -16,  -8,  -4,   0,   0,  -4,  -8, -16,
 -24, -16, -12,  -8,  -8, -12, -16, -24 },
//A8                                 H8

//A1                                H1
{-15, -10,  -8,  -7,  -7,  -8, -10, -15,
 -10,  -5,  -3,  -2,  -2,  -3,  -5, -10,
  -8,  -3,   0,   2,   2,   0,  -3,  -8,
  -7,  -2,   2,   5,   5,   2,  -2,  -7,
  -7,  -2,   2,   5,   5,   2,  -2,  -7,
  -8,  -3,   0,   2,   2,   0,  -3,  -8,
 -10,  -5,  -3,  -2,  -2,  -3,  -5, -10,
 -15, -10,  -8,  -7,  -7,  -8, -10, -15 }
};

static const int pstKingMg[3][64] = {
//A1                                H1
{ 13,  31, -14, -33, -33, -14,  31,  13,
  28,  19,  -5, -21, -21,  -5,  19,  28,
 -31,   8,  -8, -30, -30,  -8,   8, -31,
 -56, -15, -11, -14, -14, -11, -15, -56,
 -36,   1,  -3, -28, -28,  -3,   1, -36,
 -32,  28,  13, -39, -39,  13,  28, -32, // strange positive scores, retune manually
 -11,  17,   4, -18, -18,   4,  17, -11,
 -29,   1,  -5, -22, -22,  -5,   1, -29},
//A8                                H8

//A1                                H1
{ 40,  50,  30,   0,   0,  30,  50,  40,
  30,  40,  20,   0,   0,  20,  40,  30,
  10,  20,   0, -20, -20,   0,  20,  10,
   0,  10, -10, -30, -30, -10,  10,   0,
 -10,   0, -20, -40, -40, -20,   0, -10,
 -20, -10, -30, -50, -50, -30, -10, -20,
 -30, -20, -40, -60, -60, -40, -20, -30,
 -40, -30, -50, -70, -70, -50, -30, -40},
//A8                                 H8

//A1                                 H1
{ 44,  49,  19,  -1,  -1,  19,  49,  44,
  44,  49,  19,  -1,  -1,  19,  49,  44,
  38,  43,  13,  -7,  -7,  13,  43,  38,
  35,  40,  10, -10, -10,  10,  40,  35,
  30,  35,   5, -15, -15,   5,  35,  30,
  25,  30,   0, -20, -20,   0,  30,  25,
  15,  20, -10, -30, -30, -10,  20,  15,
   5,  10, -20, -40, -40, -20,  10,   5 }
//A8                                 H8
};

static const int pstKingEg[3][64] = {
//A1                                 H1
{-71, -29, -23, -32, -32, -23, -29, -71,
 -32, -14,  -3,   2,   2,  -3, -14, -32,
 -15,  -2,  11,  23,  23,  11,  -2, -15,
  -2,  20,  35,  40,  40,  35,  20,  -2,
  14,  39,  49,  48,  48,  49,  39,  14,
  26,  61,  76,  57,  57,  76,  61,  26,
  -6,  51,  58,  62,  62,  58,  51,  -6,
 -19,  36,  51,  54,  54,  51,  36, -19},
//A8                                 H8

//A1                                 H1
{-72, -48, -36, -24, -24, -36, -48, -72,
 -48, -24, -12,   0,   0, -12, -24, -48,
 -36, -12,   0,  12,  12,   0, -12, -36,
 -24,   0,  12,  24,  24,  12,   0, -24,
 -24,   0,  12,  24,  24,  12,   0, -24,
 -36, -12,   0,  12,  12,   0, -12, -36,
 -48, -24, -12,   0,   0, -12, -24, -48,
 -72, -48, -36, -24, -24, -36, -48, -72 },

//A1                                 H1
{-73, -50, -34, -28, -28, -34, -50, -73,
 -40, -15,  -3,   3,   3,  -3, -15, -40,
 -29,  -8,   7,  13,  13,   7,  -8, -29,
 -23,  -2,  13,  22,  22,  13,  -2, -23,
 -18,   3,  18,  27,  27,  18,   3, -18,
 -24,  -3,  12,  18,  18,  12,  -3, -24,
 -35, -10,   2,   8,   8,   2, -10, -35,
 -53, -30, -14,  -8,  -8, -14, -30, -53 }
//A8                                 H8
};

static const int pstDefendedPawn[64] = {
//A1                                H1
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  1,   1,   1,   1,   1,   1,   1,   1,
  3,   3,   3,   3,   3,   3,   3,   3,
  5,   5,   5,   5,   5,   5,   5,   5,
  8,   8,   8,   8,   8,   8,   8,   8,
 12,  12,  12,  12,  12,  12,  12,  12,
  0,   0,   0,   0,   0,   0,   0,   0
//A8                                H8
};

static const int pstPhalanxPawn[64] = {
//A1                                H1
  0,   0,   0,   0,   0,   0,   0,   0,
  2,   2,   2,   2,   2,   2,   2,   2,
  2,   2,   2,   5,   5,   2,   2,   2,
  6,   6,   8,  13,  13,   8,   6,   6,
 10,  10,  10,  15,  15,  10,  10,  10,
 16,  16,  16,  16,  16,  16,  16,  16,
 24,  24,  24,  24,  24,  24,  24,  24,
  0,   0,   0,   0,   0,   0,   0,   0,
//A8                                H8
};

static const int pstKnightOutpost[64] =
{
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   2,   3,   6,   6,   3,   2,   0,
  0,   2,   6,   9,   9,   6,   2,   0,
  0,   3,   9,  12,  12,   9,   3,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0
};

static const int pstBishopOutpost[64] =
{
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   1,   2,   4,   4,   2,   1,   0,
  0,   1,   4,   6,   6,   4,   1,   0,
  0,   2,   6,   8,   8,   6,   2,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0
};

static const int empty_ks[64] = 
{ 0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30,
  0,   0,   0,   0,   0,  -10,  -20,  -30};

static const int empty_qs[64] =
{ -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0,
  -30,  -20, -10,   0,   0,   0,   0,   0};

static const int passed_bonus_mg[2][8] = {
  { 0, 12, 12, 30, 50, 80, 130, 0 },
  { 0, 120, 80, 50, 30, 12, 12, 0 }
};

static const int passed_bonus_eg[2][8] = {
  { 0, 24, 24, 60, 100, 160, 260, 0 },
  { 0, 260, 160, 100, 60, 24, 24, 0 }
};

static const int phalanx_bonus[2][8] = {
  { 0, 0, 0, 2, 3, 4, 5, 0 },
  { 0, 5, 4, 3, 2, 0, 0, 0 }
};

struct sEvalHashEntry {
  U64 key;
  int score;
};

struct sPawnHashEntry {
  U64 key;
  int mg_pawns;
  int eg_pawns;
};

#define EVAL_HASH_SIZE 512*512
#define PAWN_HASH_SIZE 512*512
extern sEvalHashEntry EvalTT[EVAL_HASH_SIZE];
extern sPawnHashEntry PawnTT[PAWN_HASH_SIZE];

static const int isolated_malus_mg = -10;
static const int isolated_malus_eg = -20;
static const int isolated_open_malus = -10;
static const int backward_malus_mg[8] = { -5,  -7,  -9, -11, -11,  -9,  -7,  -5 };
static const int backward_malus_eg = -8;
static const int backward_open_malus = -8;

static const int islands[9] = { 0,  0, -10, -20, -30, -40, -50, -60 };

// mobility parameters [130]
// (could be decreased to 16)

static const int n_mob_mg[9] =  { -16, -12,  -8,  -4,  +0,  +4,  +8, +12, +16 };
static const int n_mob_eg[9] =  { -16, -12,  -8,  -4,  +0,  +4,  +8, +12, +16 };
static const int b_mob_mg[14] = { -35, -30, -25, -20, -15, -10,  -5,  +0,  +5, +10, +15, +20, +25, +30 };
static const int b_mob_eg[14] = { -35, -30, -25, -20, -15, -10,  -5,  +0,  +5, +10, +15, +20, +25, +30 };
static const int r_mob_mg[15] = { -14, -12, -10,  -8,  -6,  -4,  -2,  +0,  +2,  +4,  +6,  +8, +10, +12, +14 };
static const int r_mob_eg[15] = { -28, -24, -20, -16, -12,  -8,  -4,  +0,  +4,  +8, +12, +16, +20, +24, +28 };
static const int q_mob_mg[28] = { -14, -13, -12, -11, -10,  -9,  -8,  -7,  -6,  -5,  -4,  -3,  -2,  -1,  +0, 
                                   +1,  +2,  +3,  +4,  +5,  +6,  +7,  +8,  +9, +10, +11, +12, +13 };
static const int q_mob_eg[28] = { -28, -26, -24, -22, -20, -18, -16, -14, -12, -10,  -8,  -6,  -4,  -2,  +0,
                                   +2,  +4,  +6,  +8, +10, +12, +14, +16, +18, +20, +22, +24, +26 };	
					   
// parameters for evaluating material imbalance [5+9+2]

#define A  80 // advantage in both major and minor pieces
#define Rk 60 // advantage in major pieces only // WAS 50, TESTING
#define Nt 45 // advantage in minor pieces only
#define Ex 25 // exchange disadvantage [20 and 25 equal after 1700 games]
#define Mm 60 // two minors for a rook 

static const int adj[9] = { -4, -3, -2, -1, 0,  1,  2,  3,  4 };

static const int imbalance[9][9] = {
    /* n=-4  n=-3  n=-2  n=-1  n=0   n=+1  n=+2  n=+3  n=+4 */
    {  -A,   -A,   -A,   -A,  -Rk,    0,    0,    0,    0 }, // R = -4
    {  -A,   -A,   -A,   -A,  -Rk,    0,    0,    0,    0 }, // R = -3
    {  -A,   -A,   -A,   -A,  -Rk,    0,    0,    0,    0 }, // R = -2
    {  -A,   -A,   -A,   -A,  -Rk,  -Ex,   Mm,    0,    0 }, // R = -1
    { -Nt,   -Nt, -Nt,  -Nt,    0,   Nt,   Nt,   Nt,   Nt }, // R =  0
    {   0,    0,  -Mm,   Ex,   Rk,    A,    A,    A,    A }, // R = +1
    {   0,    0,    0,    0,   Rk,    A,    A,    A,    A }, // R = +2
    {   0,    0,    0,    0,   Rk,    A,    A,    A,    A }, // R = +3
    {   0,    0,    0,    0,   Rk,    A,    A,    A,    A }  // R = +4
};

// parameters for initializing danger table [4]

static const int maxAttUnit = 399;
static const double maxAttStep = 8.0;
static const double maxAttScore = 1280;
static const double attCurveMult = 0.027;

// parameters for evaluating king safety [10]

//                                 P   N   B   R   Q
static const int king_att  [7] = { 0,  6,  6,  9, 15,  0,  0 };
static const int chk_threat[7] = { 0,  4,  3,  9, 12,  0,  0 };
static const int q_contact_check = 36; // [24.. <36> ..42]
static const int r_contact_check = 24; // [16.. <24> ..?]

// parameters for piece/king tropism [8], taken from GambitFruit

//                                 P   N   B   R   Q
static const int tropism_mg[7] = { 0,  3,  2,  2,  2,  0,  0 };
static const int tropism_eg[7] = { 0,  3,  1,  1,  4,  0,  0 };

static const U64 bbQSCastle[2] = { SqBb(A1) | SqBb(B1) | SqBb(C1) | SqBb(A2) | SqBb(B2) | SqBb(C2),
                                   SqBb(A8) | SqBb(B8) | SqBb(C8) | SqBb(A7) | SqBb(B7) | SqBb(C7)
};
static const U64 bbKSCastle[2] = { SqBb(F1) | SqBb(G1) | SqBb(H1) | SqBb(F2) | SqBb(G2) | SqBb(H2),
                                   SqBb(F8) | SqBb(G8) | SqBb(H8) | SqBb(F7) | SqBb(G7) | SqBb(H7)
};