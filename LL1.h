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
}; //产生式表
vector<char> T{
	'+','-','*','/','(',')','n','0','1','2','3','4','5',
	'6','7','8','9','$'
}; //文法的终结符号
vector<char> N{
	'E','e','T','t','F'
};  //文法的非终结符号

//获取符号串s的First集,通过first引用返回
void First(const string s, vector<char>& first);
//获取非终结符X的Follow集，通过follow引用返回
void Follow(const char x, vector<char>& follow);
//清空容器内容，释放内存空间
void ClearVector(vector<char>& v);