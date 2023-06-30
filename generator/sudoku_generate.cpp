// Copyright 2023 cy gyk
#include "./sudoku_generate.h"

int g_final_set[9][9];
int g_final_set_seed[280] = {0};
int g_seed_num = 0;

int getFinalSetSeed() {
    if (g_seed_num == 280) {
        return -1;
    }
    srand(time(0));
    int id = rand() % 280;
    int num_list[9] = {0};
    while (g_final_set_seed[id] == 1) id = rand() % 280;
    for (int i = 0; i < 9; i++) {
        g_final_set[3 + i / 3][3 + i % 3] = i + 1;
    }
    if (id < 190) {
        if (id > 9) {
            int n1 = (id - 10) / 60;
            int n = (id - 10) % 60 / 10;
            g_final_set[3][3 + n1] = n + 4;
            g_final_set[4 + n / 3][3 + n % 3] = n1 + 1;
        }
        int n2 = id % 10;
        if (n2 > 0) {
            n2--;
            int n = g_final_set[4][n2 / 3];
            g_final_set[4][n2 / 3] = g_final_set[5][n2 % 3];
            g_final_set[5][n2 % 3] = n;
        }
    } else {
        g_final_set[4][3] = 2;
        g_final_set[5][3] = 3;
        int n2 = (id - 190) * 8;
        int n3 = 720;
        int list[6] = {1, 1, 1, 1, 1, 1};
        for (int i = 6; i > 0; i--) {
            n3 /= i;
            int n4 = n2 / n3;
            n2 = n2 % n3;
            int n = -1;
            for (int j = 0; j < 6; j++) {
                if (n + list[j] >= n4) {
                    n = j;
                    break;
                }
                n += list[j];
            }
            list[n] = 0;
            g_final_set[3 + (6 - i) / 2][4 + (6 - i) % 2] = n + 4;
        }
    }
    g_final_set_seed[id] = 1;
    g_seed_num++;
    return id;
}

bool getFirstFinalSet() {
    for (int i = 0; i < 9; i++) {
        int x = 3 + i / 3;
        int y = 3 + i % 3;
        g_final_set[x][i % 3] = g_final_set[3 + (1 + i / 3) % 3][y];
        g_final_set[x][6 + i % 3] = g_final_set[3 + (2 + i / 3) % 3][y];
    }
    for (int i = 0; i < 9; i++) {
        int x = 3 + i / 3;
        int y = 3 + i % 3;
        g_final_set[i / 3][y] = g_final_set[x][3 + (i + 1) % 3];
        g_final_set[6 + i / 3][y] = g_final_set[x][3 + (i + 2) % 3];
    }
    for (int i = 0; i < 9; i++) {
        int x = 3 + i / 3;
        int y = 3 + i % 3;
        g_final_set[i / 3][i % 3] = g_final_set[(1 + i / 3) % 3][3 + i % 3];
        g_final_set[i / 3][6 + i % 3] = g_final_set[(1 + i / 3) % 3][3 + i % 3];
        g_final_set[6 + i / 3][i % 3] = g_final_set[6 + (1 + i / 3) % 3][y];
        g_final_set[6 + i / 3][6 + i % 3] = g_final_set[6 + (1 + i / 3) % 3][y];
    }
    return true;
}


bool printFinalSet(ofstream &outFile) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            outFile << g_final_set[i][j];
        }
    }
    outFile << endl;
    return true;
}

void swapRow(int x1, int x2) {
    for (int i = 0; i < 9; i++) {
        int n = g_final_set[x1][i];
        g_final_set[x1][i] = g_final_set[x2][i];
        g_final_set[x2][i] = n;
    }
}

void swapCol(int y1, int y2) {
    for (int i = 0; i < 9; i++) {
        int n = g_final_set[i][y1];
        g_final_set[i][y1] = g_final_set[i][y2];
        g_final_set[i][y2] = n;
    }
}

int sudokuGenerate(int num, const char* filename) {
    ofstream outFile;
    outFile.open(filename);
    while (num > 0) {
        if (getFinalSetSeed() < 0) {
            return -1;
        }
        getFirstFinalSet();
        int i = 0;
        while (num > 0 && i < 8) {
            switch (i % 4) {
            case 0:
                swapRow(6, 0);
                swapRow(7, 1);
                swapRow(8, 2);
                for (int i = 0; i < 9; i++) {
                    int n = g_final_set[i / 3][i % 3];
                    g_final_set[i / 3][i % 3] = g_final_set[i / 3][6 + i % 3];
                    g_final_set[i / 3][6 + i % 3] = n;
                }
                break;
            case 1:
                swapCol(0, 6);
                swapCol(1, 7);
                swapCol(2, 8);
                break;
            case 2:
                swapRow(0, 6);
                swapRow(1, 7);
                swapRow(2, 8);
                break;
            case 3:
                swapCol(6, 0);
                swapCol(7, 1);
                swapCol(8, 2);
                break;
            }
            int x1 = 0;
            while (num > 0 && x1 < 6) {
                int x2 = 0;
                while (num > 0 && x2 < 6) {
                    int x3 = 0;
                    while (num > 0 && x3 < 6) {
                        int y1 = 0;
                        while (num > 0 && y1 < 6) {
                            int y2 = 0;
                            while (num > 0 && y2 < 6) {
                                int y3 = 0;
                                while (num > 0 && y3 < 6) {
                                    swapCol(6 + y3 % 2, 7 + y3 % 2);
                                    printFinalSet(outFile);
                                    num--;
                                    y3++;
                                }
                                swapCol(3 + y2 % 2, 4 + y2 % 2);
                                y2++;
                            }
                            swapCol(y1 % 2, 1 + y1 % 2);
                            y1++;
                        }
                        swapRow(6 + x3 % 2, 7 + x3 % 2);
                        x3++;
                    }
                    swapRow(3 + x2 % 2, 4 + x2 % 2);
                    x2++;
                }
                swapRow(x1 % 2, 1 + x1 % 2);
                x1++;
            }
            i++;
        }
    }
    return 0;
}
