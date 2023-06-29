#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include<stdio.h>
using namespace std;

const int maxrow = 9 * 9 * 9;
const int maxcol = 1 + 9 * 9 * 4;
const int num = maxcol + maxrow * 4;	// ��Ԫ�ظ���,  ��һ��ΪHeadԪ��,����9*9*4��Ϊ�б�Ԫ��,���9*9*9*4��Ϊ��1��Ԫ��

class SudokuSolver {
public:
	char* solve(char ch[]);

private:
	int table[9][9];	// ����
	int no;				// Ԫ�ر��
	void transform(int table[][9], char ch[]);
	void link();
	void insertNode(int col, int no);
	void remove(int col);
	void resume(int col);
	bool dfs(int k);
};