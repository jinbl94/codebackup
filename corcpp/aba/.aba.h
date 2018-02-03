#ifndef ABA_H
#define ABA_H
const static char TK[64]={
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
};
const static char T[128]={
	110,64,100,79,68,119,92,102,3,117,65,94,74,115,99,123,
	114,116,12,69,66,9,20,88,5,76,75,89,84,121,107,67,
	122,8,82,126,70,128,2,86,38,101,17,37,23,44,105,26,
	25,42,80,78,46,34,7,96,11,113,29,13,30,40,118,41,
	1,10,22,31,4,19,36,71,72,73,18,47,48,77,51,33,
	50,81,53,83,28,85,39,87,45,27,90,91,6,93,56,95,
	55,97,98,14,61,63,54,103,104,52,106,60,108,109,43,111,
	112,57,16,59,49,21,62,24,120,58,32,15,124,125,35,127,
};
bool subkey[7][64];
class ABA{
private:
	static void setsubkey(char* key);
	static void aba(char In[16],char Out[16]);
	static void func(bool In[64],bool key[64]);
	static void transform(bool* Out,bool* In,const char* t,int len);
	static void Xor(bool* In1,bool* In2,int len);
	static void btbi(bool* Out,char* In,int len);
	static void bitb(char* Out,bool* In,int len);
public:
	ABA(char* In,char* Out,long len,char* key);
	~ABA();
};
#endif
