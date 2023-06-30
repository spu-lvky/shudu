// Copyright 2023 cy gyk
#ifndef SOLVER_SOLVER_H_
#define SOLVER_SOLVER_H_
#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

const int maxrow = 9 * 9 * 9;
const int maxcol = 1 + 9 * 9 * 4;
const int num = maxcol + maxrow * 4;

class SudokuSolver {
 public:
    char* solve(char ch[]);

 private:
    int table[9][9];    // sodoku
    int no;
    void transform(int table[][9], char ch[]);
    void link();
    void insertNode(int col, int no);
    void remove(int col);
    void resume(int col);
    bool dfs(int k);
};
#endif  // SOLVER_SOLVER_H_
