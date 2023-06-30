// Copyright 2023 cy gyk
#define _CRT_SECURE_NO_WARNINGS

#include "generator/sudoku_generate.h"
#include "solver/solver.h"
using namespace std;

extern int sudokuGenerate(int num, const char* filename);

int main(int argc, char* argv[]) {
    const char* a = "sudoku.txt";
    if (argc != 3) {
        cout << "Please input in the correct format" << endl;
        cout << "To Generate Final Disk:  [-c] generate quantity" << endl;
        cout << "To Solving Sudoku:  [-s] sudoku position" << endl;
        sudokuGenerate(2, a);
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        int num = 0;
        if (sscanf(argv[2], "%d", &num) < 0) {
            cout << "Please use Decimal integer" << endl;
            return 0;
        }
        if (num > 1000000 || num < 0) {
            cout << "The generated quantity range is 1-1000000" << endl;
            return 0;
        }
        sudokuGenerate(num, a);
    } else if (strcmp(argv[1], "-s") == 0) {
        int num = 0;
        const char* filename = argv[2];
        // FILE* in = fopen(filename, "r");
        ifstream in(filename);

        if (!in.is_open()) {
            printf("Could not open file  %s\n", filename);
            return 0;
        }
        char ch[81];
        char c;
        SudokuSolver ss;
        FILE* out = fopen("sudoku.txt", "wt");
        int count = 0;
        while (in.get(c)) {
            ch[count++] = c;
            if (count == 81) {
                count = 0;
                fputs(ss.solve(ch), out);
            }
        }
        in.close();
    } else {
        cout << "Please input in the correct format" << endl;
        cout << "To Generate Final Disk:  [-c] generate quantity" << endl;
        cout << "To Solving Sudoku:  [-s] sudoku position" << endl;
        return 0;
    }
    cout << "end" << endl;
    return 0;
}
