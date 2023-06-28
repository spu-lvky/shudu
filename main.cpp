#define _CRT_SECURE_NO_WARNINGS

#include "generator/sudoku_generate.h"
#include "solver/solver.h"
using namespace std;

extern int sudokuGenerate(int num, const char* filename);

int main(int argc,char* argv[]) {
	const char* a = "sudoku.txt";
	if (argc != 3) {
		cout << "�밴��ȷ��ʽ����" << endl;
		cout << "�������̣� -c ��������" << endl;
		cout << "��������� -s ����λ��" << endl;
		return 0;
	}
	if (strcmp(argv[1],"-c")==0) {
		int num = 0;
		if (sscanf(argv[2], "%d", &num)<0) {
			cout << "������������ʮ����������ʾ" << endl;
			return 0;
		}
		if (num > 1000000 || num<0) {
			cout << "����������ΧΪ1-1000000�������뷶Χ�ڵ�����" << endl;
			return 0;
		}
		sudokuGenerate(num, a);
	}
	else if (strcmp(argv[1], "-s") == 0) {
		int num = 0;
		const char* filename = argv[2];

		//TODO:���ú�����ȡ���������
	}
	else{
		cout << "�밴��ȷ��ʽ����" << endl;
		cout << "�������̣� -c ��������" << endl;
		cout << "��������� -s ����λ��" << endl;
		return 0;
	}
	cout << "����" << endl;
	return 0;
}