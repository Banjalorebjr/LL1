/*
*������ķ���Ԥ�������
*/
#include "LL1.h"
#include <ctype.h>
#include <fstream>
#include <algorithm>
#include <iomanip>

void First(const string s, vector<char>& first) {
	char c = s.at(0);

	 //���жϵ�һ���ַ�
	 if (isdigit(c) || '+' == c || '-' == c || '*' == c || '/'==c || '(' == c || ')' == c) {
		 //�ս��
		 first.push_back(c);
		 return;
	 }
	 else if (c == 'n') {
		 first.push_back('n');
		 return;
	 }
	 else if (c == '#') {
		 //��
		 first.push_back('#');
	 }
	 else {
		 //���ս��
		 switch (c) {
		 case 'E':  //E -> TE'
			 First("T", first);
			 break;
		 case 'e':  //E'->eplison|+TE'|-TE'
			 first.push_back('+');
			 first.push_back('-');
			 first.push_back('#');	//����������#������epslion
			 break;
		 case 'T':	//T -> FT'
			 First("F", first);
			 break;
		 case 't':	//T' -> #| *FT' | /FT'
			 first.push_back('#');
			 first.push_back('*');
			 first.push_back('/');
			 break;
		 case 'F':
			 first.push_back('(');
			 //num
			 first.push_back('0');
			 first.push_back('1');
			 first.push_back('2');
			 first.push_back('3');
			 first.push_back('4');
			 first.push_back('5');
			 first.push_back('6');
			 first.push_back('7');
			 first.push_back('8');
			 first.push_back('9');
			 first.push_back('n');
			 break;
		 default: 
			 break;
		 }//switch
	 }
}

void Follow(const char x, vector<char>& follow) {
	vector<char> first;

	switch (x) {
	case'E':
		//��ʼ��
		follow.push_back('$');
		First(")", follow);
		break;
	case'e':
		Follow('E', follow);
		break;
	case 'T':
		First("e", first);
		for (auto c : first) {
			if (c != '#')
				follow.push_back(c);
		}
		follow.push_back(')');
		follow.push_back('$');
		break;
	case 't':
		Follow('T', follow);
		break;
	case 'F':
		Follow('T', follow);
		follow.push_back('*');
		follow.push_back('/');
		break;
	default:
		break;
	}
}

void ClearVector(vector<char>& v) {
	//�����������С��������
	vector<char>().swap(v);	
}

void MakeTable(string table[][MAX_Y]) {
	vector<char> first, follow;

	//��ʼ��table,������λ�ö���ֵΪ��
	for (int i = 0;i < MAX_X;i++)
		for (int j = 0;j < MAX_Y; j++)
			table[i][j] = " ";

	for (auto g :GENERTOR) {
		//����ÿһ������ʽ
		char A = g.at(0);		//������ʽ�󲿵ķ��ս����ֵ��A
		string a(g, GEN_R);		//����ʼ�ڲ���ʽ�Ҳ����ַ�����ֵ��a
		ClearVector(first);
		First(a, first);	//First(a)

		for (auto b : T) {
			//����ÿ���ս����
			vector<char>::iterator find_a = find(first.begin(), first.end(), b);
			if (first.end() != find_a) {
				//b ����First(a):��A->a�����M[A,a]
				int x, y;
				for (int i = 0; i < N.size();i++)
					if (N[i] == A) {
						x = i;
						break;
					}

				if (isdigit(b)||b == 'n') {
					//num
					y = MAX_Y - 2;	//�����ڶ�����num
				}
				else {
					for (int i = 0; i < T.size(); i++)
						if (b == T[i]) {
							y = i;
							break;
						}
				}
				table[x][y] = g;	//������ʽ��ӽ�������
			}
		}

		//�����Ƿ��Ц�
		vector<char>::iterator find_it = find(first.begin(), first.end(), '#');
		if (find_it != first.end()) {
			//�ҵ���
			ClearVector(follow);
			Follow(A, follow);
			for (auto b : follow) {
				int x, y;
				for (int i = 0; i < N.size(); i++)
					if (A == N[i]) {
						x = i;
						break;
					}
				if (isdigit(b) || b == 'n')
					y = MAX_Y - 2;
				else if (b == '$')
					y = MAX_Y - 1;
				else {
					for (int i = 0; i < T.size(); i++)
						if (b == T[i]) {
							y = i;
							break;
						}
				}
				table[x][y] = g;
			};
		}
	}
}

void PrintTable(ofstream& out, string table[][MAX_Y]) {
	//���������ָ���ļ�
	//��ӡ��ͷ
	out << setw(3) << ' ';
	for (int i = 0; i < MAX_Y - 2;i++)
		out << setw(10) << T[i];  //������С������Ϊ10
	out << setw(10) << "num";
	out << setw(10) << '$' << endl << endl;

	for (int i = 0; i < MAX_X; i++) {
		out << setw(3) << N[i];
		for (int j = 0; j < MAX_Y;j++) {
			out << setw(10) << table[i][j];
		}
		out << endl << endl;
	}
}
int main(void) {
	//vector<char> follow;
	ofstream fout_table("out_table.txt");
	ofstream fout_process("out_process.txt");
	string table[MAX_X][MAX_Y]; //������
	MakeTable(table);
	PrintTable(fout_table, table);
	fout_table.close();
	fout_process.close();
	system("pause");
	return 0;
}