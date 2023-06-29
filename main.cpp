#define _CRT_SECURE_NO_WARNINGS

#include "generator/sudoku_generate.h"
#include "solver/solver.h"
using namespace std;

extern int sudokuGenerate(int num, const char* filename);

int main(int argc,char* argv[]) {
	const char* a = "sudoku.txt";
	if (argc != 3) {
		cout << "请按正确格式输入" << endl;
		cout << "生成终盘： -c 生成数量" << endl;
		cout << "求解数独： -s 数独位置" << endl;
		return 0;
	}
	if (strcmp(argv[1],"-c")==0) {
		int num = 0;
		if (sscanf(argv[2], "%d", &num)<0) {
			cout << "生成数量请用十进制整数表示" << endl;
			return 0;
		}
		if (num > 1000000 || num<0) {
			cout << "生成数量范围为1-1000000，请输入范围内的数字" << endl;
			return 0;
		}
		sudokuGenerate(num, a);
	}
	else if (strcmp(argv[1], "-s") == 0) {
		int num = 0;
		const char* filename = argv[2];
		FILE* in = fopen(filename, "r");

		if (in == NULL) {
			printf("无法打开文件 %s\n", filename);
			return 0;
		}

		SudokuSolver ss;
		FILE* out = fopen("sudoku.txt", "wt");
		int count = 0;
		while (in.get(c)) {	//in >> c 会忽略空白回车符
			//cout << c;
			/*if (isdigit(c)) {

			}*/
			ch[count++] = c;
			if (count == 81) {
				count = 0;
				//cout << "进行运算" << endl;
				fputs(ss.solve(ch), out);
			}
		}
		in.close();
		//cout << count;
		//TODO:调用函数读取数独并求解
	}
	else{
		cout << "请按正确格式输入" << endl;
		cout << "生成终盘： -c 生成数量" << endl;
		cout << "求解数独： -s 数独位置" << endl;
		return 0;
	}
	cout << "结束" << endl;
	return 0;
}