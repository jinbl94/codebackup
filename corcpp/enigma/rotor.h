/***************************************************/
/*                     rotor.h                     */
/***************************************************/
//rotors used in the enigma.
//and you can define the rotors and plug board in the same way with the same data structure.
#include<iostream>
using namespace std;
class Rotor{
private:
	int step,a[26],b[26];
public:
	Rotor(){
		step=0;
		for(int i=0;i<26;i++){
			a[i]=0;b[i]=0;
		}
	}
	void init(int* arry){
		for(int i=0;i<26;i++){
			a[i]=arry[i];
			b[arry[i]]=i;
		}
	}
	//set-step function. and you can set the argument "s" to 1 to make step increase by one.
	//when you change the value of step you must change the value of arry a and b.
	int ss(int s){
		int statu=0;
		step+=s;
		if(step==26){
			statu=1;
			step=0;
		}
		return statu;
	}
	int l(int c){
		return (a[(c+step)%26]+26-step)%26;
	}
	int r(int c){
		return (b[(c+step)%26]+26-step)%26;
	}
};
