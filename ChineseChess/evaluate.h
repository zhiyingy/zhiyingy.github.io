#ifndef _EVALUATE_H_
#define _EVALUATE_H_

#define B_ZU 30
#define B_SHI 120
#define B_XIANG 120
#define B_JU 600
#define B_MA 270
#define B_PAO 285

#define POSINF INT_MAX-1
#define NEGINF INT_MIN+1

const int RZUPLUS[10][9] = {  0,  3,  6,  9, 12,  9,  6,  3,  0,
                             18, 36, 56, 80,120, 80, 56, 36, 18,
                             14, 26, 42, 60, 80, 60, 42, 26, 14,
                             10, 20, 30, 34, 40, 34, 30, 20, 10,
                              6, 12, 18, 18, 20, 18, 18, 12,  6,
                               0,  0,  0,  0,  0,  0,  0,  0,  0,
                               0,  0,  0,  0,  0,  0,  0,  0,  0,
                               0,  0,  0,  0,  0,  0,  0,  0,  0,
                               0,  0,  0,  0,  0,  0,  0,  0,  0,
                               0,  0,  0,  0,  0,  0,  0,  0,  0};

const int BZUPLUS[10][9] = {  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,
                              6, 12, 18, 18, 20, 18, 18, 12,  6,
                             10, 20, 30, 34, 40, 34, 30, 20, 10,
                             14, 26, 42, 60, 80, 60, 42, 26, 14,
                             18, 36, 56, 80,120, 80, 56, 36, 18,
                              0,  3,  6,  9, 12,  9,  6,  3,  0};

const int RJUPLUS[10][9] = { 14, 14, 12, 18, 16, 18, 12, 14, 14,
                             16, 20, 18, 24, 26, 24, 18, 20, 16,
                             12, 12, 12, 18, 18, 18, 12, 12, 12,
                             12, 18, 16, 22, 22, 22, 16, 18, 12,
                             12, 14, 12, 18, 18, 18, 12, 14, 12,
                             12, 16, 14, 20, 20, 20, 14, 16, 12,
                              6, 10,  8, 14, 14, 14,  8, 10,  6,
                              4,  8,  6, 14, 12, 14,  6,  8,  4,
                              8,  4,  8, 16,  8, 16,  8,  4,  8,
                             -2, 10,  6, 14, 12, 14,  6, 10, -2};

const int BJUPLUS[10][9] = { -2, 10,  6, 14, 12, 14,  6, 10, -2,
                              8,  4,  8, 16,  8, 16,  8,  4,  8,
                              4,  8,  6, 14, 12, 14,  6,  8,  4,
                              6, 10,  8, 14, 14, 14,  8, 10,  6,
                             12, 16, 14, 20, 20, 20, 14, 16, 12,
                             12, 14, 12, 18, 18, 18, 12, 14, 12,
                             12, 18, 16, 22, 22, 22, 16, 18, 12,
                             12, 12, 12, 18, 18, 18, 12, 12, 12,
                             16, 20, 18, 24, 26, 24, 18, 20, 16,
                             14, 14, 12, 18, 16, 18, 12, 14, 14};

const int BMAPLUS[10][9] = {0,-4, 0, 0, 0, 0, 0,-4, 0,
                            0, 2, 4, 4,-2, 4, 4, 2, 0,
                            4, 2, 8, 8, 4, 8, 8, 2, 4,
                            2, 6, 8, 6,10, 6, 8, 6, 2,
                            4,12,16,14,12,14,16,12, 4,
                            6,16,14,18,16,18,14,16, 6,
                            8,24,18,24,20,24,18,24, 8,
                           12,14,16,20,18,20,16,14,12,
                            4,10,28,16, 8,16,28,10, 4,
                            4, 8,16,12, 4,12,16, 8, 4};

const int RMAPLUS[10][9] = { 4, 8,16,12, 4,12,16, 8, 4,
                             4,10,28,16, 8,16,28,10, 4,
                            12,14,16,20,18,20,16,14,12,
                             8,24,18,24,20,24,18,24, 8,
                             6,16,14,18,16,18,14,16, 6,
                             4,12,16,14,12,14,16,12, 4,
                             2, 6, 8, 6,10, 6, 8, 6, 2,
                             4, 2, 8, 8, 4, 8, 8, 2, 4,
                             0, 2, 4, 4,-2, 4, 4, 2, 0,
                             0,-4, 0, 0, 0, 0, 0,-4, 0};

const int BPAOPLUS[10][9] = {0,  0,  2,  6,  6,  6,  2,  0,  0,
                             0,  2,  4,  6,  6,  6,  4,  2,  0,
                             4,  0,  8,  6, 10,  6,  8,  0,  4,
                             0,  0,  0,  2,  4,  2,  0,  0,  0,
                            -2,  0,  4,  2,  6,  2,  4,  0, -2,
                             0,  0,  0,  2,  8,  2,  0,  0,  0,
                             0,  0, -2,  4, 10,  4, -2,  0,  0,
                             2,  2,  0,-10, -8,-10,  0,  2,  2,
                             2,  2,  0, -4,-14, -4,  0,  2,  2,
                             6,  4,  0,-10,-12,-10,  0,  4,  6};

const int RPAOPLUS[10][9] = { 6,  4,  0,-10,-12,-10,  0,  4,  6,
                              2,  2,  0, -4,-14, -4,  0,  2,  2,
                              2,  2,  0,-10, -8,-10,  0,  2,  2,
                              0,  0, -2,  4, 10,  4, -2,  0,  0,
                              0,  0,  0,  2,  8,  2,  0,  0,  0,
                             -2,  0,  4,  2,  6,  2,  4,  0, -2,
                              0,  0,  0,  2,  4,  2,  0,  0,  0,
                              4,  0,  8,  6, 10,  6,  8,  0,  4,
                              0,  2,  4,  6,  6,  6,  4,  2,  0,
                              0,  0,  2,  6,  6,  6,  2,  0,  0};

int evaluate(int **board, int curPlayer);

#endif