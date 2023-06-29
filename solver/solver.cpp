#pragma warning(disable : 4996)
#include "solver.h"
int Left[num], Right[num], Up[num], Down[num];	// ÿ��Ԫ�ص�4������������൱�������еļ�ͷ
int Col[num], Row[num];
int Size[maxcol];
int Head[maxrow]; //��¼ÿ�е�һ��Ԫ��
static char str[163];
static int index;
char* SudokuSolver::solve(char ch[]) {
	index = 0;
	transform(table, ch);
	link();
	int select = 0;
	// ����������Ŀ�Ѹ����ֵ��б�ѡ
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int k = table[i][j];
			
			if (k) {
				//��������Ϊ�����ʼ����ʱ���ȥ�ˣ�ֻ��Ҫ����Ķ�Ӧ�ͺ�
				int row = i * 81 + j * 9 + k - 1;
				select++;
				remove(Col[Head[row]]);
				for (int u = Right[Head[row]]; u != Head[row]; u = Right[u]) {
					remove(Col[u]);
				}
			}
		}
	}
	dfs(select + 1);
	/*for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << table[i][j];
		}
	}*/

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 8; j++) {
			str[index++] = char(table[i][j] + '0');
			str[index++] = ' ';
		}
		str[index++] = (table[i][8] + '0');
		str[index++] = '\n';
	}
	str[index++] = '\n';
	return str;


}
//����ĺ���������ʲô����
void SudokuSolver::transform(int table[][9], char ch[]) {


	int pos = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (isdigit(ch[pos])) {
				table[i][j] = ch[pos] - '0';
			}
			else {
				table[i][j] = 0;
			}
			pos++;
			//cout << table[i][j];
		}

	}
	//cout << endl;

	return;
}
void SudokuSolver::link() {
	for (int i = 0; i < maxcol; i++) {
		Left[i] = i - 1;
		Right[i] = i + 1;
		Up[i] = Down[i] = i;
		Col[i] = i;
		Row[i] = 0;
		Size[i] = 0;
	}
	Left[0] = maxcol - 1;
	Right[maxcol - 1] = 0;
	//��һ��Ԫ�ر�ţ�����������ǰ�治����һ��index������
	no = maxcol;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int k = table[i][j];
			if (table[i][j]) {
				//???????�����Ҿ���Ӧ����=0��<4��Ȼmaxcol���ֵ�ǿյ�ѽ
				for (int t = 1; t <= 4; t++) {
					Left[no + t] = no + t - 1;
					Right[no + t] = no + t + 1;
					Row[no + t] = i * 81 + j * 9 + table[i][j] - 1;
				}
				Left[no + 1] = no + 4;
				Right[no + 4] = no + 1;
				Head[Row[no + 1]] = no + 1;
				//  ��4��Ԫ�ز���������   ��Ϊ���ٶ������Ǵӵ�һ�п�ʼ�ģ���0����head���ڣ�����head����û��Ԫ�ص�
				insertNode(i * 9 + j + 1, no + 1);
				insertNode(81 + i * 9 + k, no + 2);
				insertNode(81 * 2 + j * 9 + k, no + 3);
				insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
				no += 4;
			}
			else {
				for (int k = 1; k <= 9; k++) {
					for (int t = 1; t <= 4; t++) {
						Left[no + t] = no + t - 1;
						Right[no + t] = no + t + 1;
						Row[no + t] = i * 81 + j * 9 + k - 1;
					}
					Left[no + 1] = no + 4;
					Right[no + 4] = no + 1;
					Head[Row[no + 1]] = no + 1;
					//  ��4��Ԫ�ز���������   ��Ϊ���ٶ������Ǵӵ�һ�п�ʼ�ģ���0����head���ڣ�����head����û��Ԫ�ص�
					insertNode(i * 9 + j + 1, no + 1);
					insertNode(81 + i * 9 + k, no + 2);
					insertNode(81 * 2 + j * 9 + k, no + 3);
					insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
					no += 4;
				}
			}
		}
	}
	/*for (int i = Right[0]; i != 0; i = Right[i]) {
		int size = Size[i];
		cout << i<<"  "<<size << endl;
	}*/

}
void SudokuSolver::insertNode(int col, int no) {
	/* ��Ԫ��col��Down[col]֮�����no */
	//�Ҿ����е����⣬��������up��down���෴�ģ����ҿ�������Ӧ������col��Up[col]֮�����no��,��������᲻��Ӱ��
	Up[Down[col]] = no;
	Down[no] = Down[col];
	Up[no] = col;
	Down[col] = no;
	Size[col]++;
	Col[no] = col;


}
void SudokuSolver::remove(int col) {
	Left[Right[col]] = Left[col];
	Right[Left[col]] = Right[col];
	for (int i = Down[col]; i != col; i = Down[i]) {
		for (int j = Right[i]; j != i; j = Right[j]) {
			Up[Down[j]] = Up[j];
			Down[Up[j]] = Down[j];
			Size[Col[j]]--;
		}
	}
}
void SudokuSolver::resume(int col) {
	Left[Right[col]] = Right[Left[col]] = col;
	for (int i = Up[col]; i != col; i = Up[i]) {
		for (int j = Left[i]; j != i; j = Left[j]) {
			Up[Down[j]] = Down[Up[j]] = j;
			Size[Col[j]]++;
		}
	}
}
bool SudokuSolver::dfs(int select) {
	//cout << "yunxing"<<endl;
	if (select > 81) {
		return true;
	}
	//cout << "yunxing1"<<endl;
	int col = 0;
	int min = INT_MAX;
	for (int i = Right[0]; i != 0; i = Right[i]) {
		int size = Size[i];
		//cout << size << endl;
		if (size == 0) {
			return false;
		}
		if (size < min) {
			min = size;
			col = i;
		}
	}
	//cout << "yunxing2" << endl;
	remove(col);
	//cout << "yunxing3"<<endl;
	/* �������и���1��Ԫ��,�������γ���,ʧ����ָ����Ƴ��Ľ�� */
	for (int i = Down[col]; i != col; i = Down[i]) {
		//cout << "yunxing";
		//select++;
		int row = Row[i];
		table[row / 81][row % 81 / 9] = row % 9 + 1;
		//cout << "�޸�" << row / 81 << " " << row % 81 / 9 << "Ϊ" << row % 9 + 1 << endl;
		//cout << table[9][9] << endl;
		for (int j = Right[i]; j != i; j = Right[j]) {
			remove(Col[j]);
		}
		if (dfs(select+1)) {
			
			return true;
		}
		for (int j = Left[i]; j != i; j = Left[i]) {
			resume(Col[j]);
		}
	}
	resume(col);
	return false;
}
//int main() {
//	ifstream in("C://Users//26937//Desktop//shudo.txt");
//	if (!in.is_open()) {
//		//cout << "�޷��򿪣�" << endl;
//		return 0;
//	}
//	char ch[81];
//	char c;
//	int count = 0;
//	SudokuSolver ss;
//	FILE* out = fopen("sudoku.txt", "wt");
//	while (in.get(c)) {	//in >> c ����Կհ׻س���
//		//cout << c;
//		/*if (isdigit(c)) {
//			
//		}*/
//		ch[count++] = c;
//		if (count == 81) {
//			count = 0;
//			//cout << "��������" << endl;
//			fputs(ss.solve(ch), out);
//		}
//		//cout << count << endl;
//	}
//	//cout <<endl<< int(ch[0])<<"  "<<count;
//	in.close();
//	if (count != 0) {
//		/*char* str = "���ڴ����ʽ��";
//		fputs(str, out);*/
//		cout << "���ڴ����ʽ��" << endl;
//	}
//	else
//		cout << "�ѽ���������" << endl;
//	fclose(out);
//	return 0;
//}
