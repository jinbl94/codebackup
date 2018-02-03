#include<iostream>
#include<time.h>
#define MAX 2
#define SIZE 20
using namespace std;
class AOV_Node
{
private:
	int next[SIZE+1];			//next[0] is used to storage the number of its parent nodes;
	char data;
public:
	AOV_Node(){ next[SIZE] = 0; }
	bool chek(int temp);			//Check the value of next[temp].
	void addchar(char temp);
	void addpar();
	void addson(int temp);
	void parlea();
	void show();
};
class AOV_Gra
{
private:
	int Gra[SIZE][SIZE], nodenum = SIZE, used[SIZE];
	AOV_Node gra[SIZE];
public:
	AOV_Gra();
	void show_arry();
	void AOV_G_Link();
	void AOV_G_Sort();
	void run(){ AOV_G_Link(); AOV_G_Sort(); }
};
bool AOV_Node::chek(int tmep){
	bool b = 0;
	if (next[tmep] == 0)b = 1;
	return b;
}
void AOV_Node::addchar(char temp){
	data = temp;
}
void AOV_Node::addpar(){
	next[SIZE]++;
}
void AOV_Node::addson(int temp){
	next[temp] = 1;
}
void AOV_Node::parlea(){
	next[SIZE]--;
}
void AOV_Node::show(){
	cout << data << " ";
}
AOV_Gra::AOV_Gra(){
	int temp = 0, i = 0, j = 0;
	srand((unsigned)time(NULL));
	for (i = 0; i < SIZE; i++){
		used[i] = 0;
		for (j = 0; j < SIZE; j++){
			if (j>i){
				temp = rand() % MAX;
				Gra[i][j] = temp;
			}
			else Gra[i][j] = 0;
		}
	}
}
void AOV_Gra::show_arry(){
	char ch = 'A';
	for (int i = 0; i < SIZE; i++, ch++){
		cout << ch << " ";
		for (int j = 0; j < SIZE; j++){
			if (j>=i)cout << Gra[i][j] << " ";
			else cout << "  ";
		}
		cout << endl;
	}
}
void AOV_Gra::AOV_G_Link(){
	int i = 0, j = 0;
	char ch = 'A';
	for (i = 0; i < SIZE; i++, ch++){
		gra[i].addchar(ch);
		for (j = i + 1; j < SIZE; j++){
			if (Gra[i][j] == 1){
				gra[i].addson(j);
				gra[j].addpar();
			}
		}
	}
}
void AOV_Gra::AOV_G_Sort(){
	int i = 0, j = 0, temp = 0;
	cout << endl << "Result:";
	for (i = 0; i < SIZE; i++)
		if (gra[i].chek(SIZE))
			temp++;
		for (; nodenum != 0 && temp>0;){
			for (i = 0; i < SIZE&&temp != 0; i++){
				if (used[i] == 0){
					if (gra[i].chek(SIZE)){
						gra[i].show();
						used[i] = 1;
						nodenum--;
						temp--;

					}
				}
			}
			for (i = 0; i < SIZE; i++){
				if (used[i] == 1)
				for (j = i + 1; j < SIZE; j++){
					used[i] = 2;
					if (Gra[i][j])
						gra[j].parlea();
				}
				else if (gra[i].chek(SIZE) && used[i] == 0)temp++;
				else;
			}
		}
}
void main(){
	AOV_Gra aov;
	aov.show_arry();
	aov.run();
}