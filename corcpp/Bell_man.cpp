#include<iostream>
#include<time.h>
#define INIT 99999				//Initial value of the edges' values.
#define SIZE 10					//Number of the points.
#define MAX 99					//The bigest value of the edge.
using namespace std;
class E
{
private:
	int m, n, cost;
public:
	void creat(int a, int b, int c){
		m = a; n = b; cost = c;
	}
	int rm(){
		return m;
	}//Return the value of m.
	int rn(){
		return n;
	}//Return the value of n.
	int rcost(){
		return cost;
	}//Return the value of cost.
};					//Edge links m and n.
class Stack
{
private:
	int member[SIZE], top = -1;
public:
	void Add(int t){
		top++;
		member[top] = t;
	}
	void popall (){
		for (; top != -1; top--)
			cout << member[top] << " ";
	}
};			//Stack. Used to record the path of the points.
class Gra
{
private:
	int cost[SIZE][SIZE], e_num = 0, Distance[SIZE], pre[SIZE];			//'pre' is used to record the point chosen before i.
	E *e;
	Stack *s;
public:
	Gra(){
		int temp = 0, b;
		srand((unsigned)time(NULL));
		for (int i = 0; i < SIZE; i++){
			cost[i][i] = 0;
			Distance[i] = (i == 0 ? 0 : INIT);				//Initialize distance.
			for (int j = i + 1; j < SIZE; j++){
				b = rand() % 2;								//'b' is used to determin whether to creat an edge. 1-'YES' 0-'NO'
				if (b)
				{
					temp = rand() % MAX + 1;				//Here you can adjust the costs of the points.
					cost[i][j] = cost[j][i] = temp;
					e_num += 2; temp = 0;
				}
				else cost[i][j] = cost[j][i] = INIT;
			}
		}
	}										//Form a graph.
	void show_gra(){
		for (int i = 0; i < SIZE; i++){
			cout << i << ": ";
			for (int j = 0; j < SIZE; j++){
				if (cost[i][j] == INIT)printf("%3c", '$');
				else
					printf("%3d", cost[i][j]);
			}
			cout << endl;
		}
	}
	void Link(){
		int linked = 0, k = 0;
		e = new E[e_num];
		for (int i = 0; i < SIZE&&linked < e_num; i++)
		for (int j = 0; j < SIZE&&linked < e_num; j++)
		if (cost[i][j] != INIT&&cost[i][j] != 0){
			e[k].creat(i, j, cost[i][j]);
			k++; linked++;
		}
	}						//Record the edges.
	bool Bell_man(){
		pre[0] = -1;
		for (int i = 1; i < SIZE; i++)
		for (int j = 0; j < e_num; j++){
			if (Distance[e[j].rm()]>Distance[e[j].rn()] + e[j].rcost())
			{
				Distance[e[j].rm()] = Distance[e[j].rn()] + e[j].rcost();
				pre[e[j].rm()] = e[j].rn();
			}
		}
		bool b = 0;
		for (int i = 0; i < SIZE;i++)
		if (Distance[e[i].rm()]>Distance[e[i].rm()] + e[i].rcost()){
			b = 1;
			break;
		}
		return b;
	}		//Bellman Ford. Return 'b' to tell if there is any negative edge. 1-'YES' 0-'NO'
	void dis_result(){
		s = new Stack[SIZE];
		cout << "Ditance from source to 'i'" << endl << "i" << '\t' << "Distance";
		for (int i = 1; i < SIZE; i++)cout << endl << i << '\t' << Distance[i];
	}			//Show the distances fron source to point i.
	void pat_result(){
		for (int i = 0; i < SIZE; i++)
		for (int j = i; pre[j] != -1; j = pre[j])
			s[i].Add(pre[j]);
		cout << endl << "Path from source to 'i'" << endl << "i" << '\t' << "Path";
		for (int i = 1; i < SIZE; i++){
			if (Distance[i] != INIT){
				cout << endl << i << '\t';
				s[i].popall();
				cout << i;
			}
		}
	}					//Show the path from source to i.
	~Gra(){
		delete(e);
		delete(s);
	}
};
class Run
{
private:
	Gra G;
	bool key;
public:
	Run(){
		G.show_gra();
		G.Link();
		key = G.Bell_man();				//'key' is used to tell wehter there is any negative edge.
		G.dis_result();
		if (key)cout << endl << "There's at least one negative edge in this graph!";		//We won't show the path when there' negative edge exists.
		else G.pat_result();
	}
	~Run(){
		cout << endl << "PROGRAM OVER!!" << endl;
	}
};				//Run.
void main(){
	Run run;
}