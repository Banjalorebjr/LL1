#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define MAX_X 5
#define MAX_Y 8
#define GEN_R 5

vector<string> GENERTOR{
	"E -> Te",
	"e -> #","e -> +Te","e -> -Te",
	"T -> Ft",
	"t -> #", "t -> *Ft", "t -> /Ft",
	"F -> (E)","F -> num"
}; //����ʽ��
vector<char> T{
	'+','-','*','/','(',')','n','0','1','2','3','4','5',
	'6','7','8','9','$'
}; //�ķ����ս����
vector<char> N{
	'E','e','T','t','F'
};  //�ķ��ķ��ս����

//��ȡ���Ŵ�s��First��,ͨ��first���÷���
void First(const string s, vector<char>& first);
//��ȡ���ս��X��Follow����ͨ��follow���÷���
void Follow(const char x, vector<char>& follow);
//����������ݣ��ͷ��ڴ�ռ�
void ClearVector(vector<char>& v);