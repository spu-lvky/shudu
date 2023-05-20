#include "sudoku_generate.h"
using namespace std;

extern int sudokuGenerate(int num, const char* filename);

int main(int argc,char argv[]) {
	const char* a = "result.txt";
	sudokuGenerate(2, a);
	return 0;
}