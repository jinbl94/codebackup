#include<iostream>
#include<time.h>
#define DATA 100
#define SIZE 8
#define MAX 99
#define INIT 9999
#define ROOT 0
using namespace std;
typedef struct Node
{
	int source, destination, conduit;
	Node *next;
}node,*nodeptr;			//Retransimission list node.(转发表节点)
class Pack
{
private:
	int data, destination;						//Destination must be no bigger than SIZE.
public:
	Pack(){ srand((unsigned)time(NULL)); data = rand() % DATA + 1; }
	int r_data(){ return data; }
	int r_destination(){ return destination; }
	~Pack(){ cout << "Class Pack destroyed!!" << endl; }
};				//Data pack.
class Router
{
private:
	int connection[SIZE], p_destination;
	nodeptr list, p;
	Pack pack;
public:
	void creat_list(nodeptr t){ list = t; }
	void creat_connection(int t[SIZE]){ connection[SIZE] = t[SIZE]; }
	void recieve(Pack t){
		pack = t;
		p_destination = pack.r_destination();
	}
	void send(Router router[SIZE]){
		for (p = list; p->destination != p_destination&&p->next != NULL; p = p->next);
		if (p->destination == p_destination)
		{
			if (p->destination = p->conduit)
				cout << "Destination arrived!" << endl << "Data=" << pack.r_data() << endl;
			else
				router[p->conduit].recieve(pack);
		}
		else
			cout << "Erro! The destination is unaviliable!" << endl;
	}
	void pack_come(Pack t, Router router[SIZE]){ recieve(t); send(router); }		//Call this function when the pack is formed.
	~Router(){ cout << "Class Router destroyed!!" << endl; }
};
class Gateway
{
private:
	nodeptr list, p, s;
	Pack pack;
	int root_access, p_destination;
public:
	Gateway(){ root_access = ROOT; }					//Root_access represents the router which links to the gateway. I set it as the  router[0].
	void pull_info(Router router[SIZE]);			//Read the routers' information.
	void path_djstra();								//Search for the shortest pathes using djstra algorithm.
	void path_distribute(Router router[SIZE]);							//Form the retransmission lists, and distrabute them to the routers.
	void recieve(Pack t){ pack = t; p_destination = pack.r_destination; }
	void send(Router router[SIZE]){ router[root_access].pack_come(pack, router); }
	void pack_come(Pack t, Router router[SIZE]){ recieve(t); send(router); }		//Call this function when the pack is formed.
	~Gateway(){ cout << "Class Gateway destroyed!!" << endl; }
};
void Gateway::pull_info(Router router[SIZE]){
	//To do
}
void Gateway::path_djstra(){
	//To do
}
void Gateway::path_distribute(Router router[SIZE]){
	//To do
}
class Run
{
private:
	Router router[SIZE];
	Gateway gateway;
	int map[SIZE][SIZE];
	Pack pack;
public:
	Run(){ creat_map(); creat_router(); function_g(); }
	void creat_map(){
		srand((unsigned)time(NULL));
		for (int i = 0; i < SIZE; i++)
		{
			map[i][i] = 0;
			for (int j = i + 1; j < SIZE; j++){
				int b = rand() % 2;
				if (b){
					int temp = rand() % MAX + 1;
					map[i][j] = map[j][i] = temp;
				}
				else map[i][j] = map[j][i] = INIT;
			}
		}
	}
	void creat_router(){
		int connection[SIZE];
		for (int i = 0; i < SIZE; i++){
			for (int j = 0; j < SIZE; j++)connection[j] = map[i][j];
			router[i].creat_connection(connection);
		}
	}
	void function_g(){
		gateway.pull_info(router);
		gateway.path_djstra();
		gateway.path_distribute(router);
		gateway.pack_come(pack, router);
	}
	~Run(){ cout << "Class Run destroyed!!" << endl; }
};
void main(){
	Run run;
}