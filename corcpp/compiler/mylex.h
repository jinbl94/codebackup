#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

char character;
char token[100];
FILE file;
int num;
int val;

void getchar(){
	character=fgetc(file);
}

void getnbc(){
	while(character==" "||character=="\t"|| character=="\n"){
		getchar();
	}
}

void concat(){
	token[strlen(token)]=character;
}

bool letter(){
	if((character>="a"&&character<="z")||(character>="A"&&character<="Z"))
		return true;
	else
		return false;
}

bool digit(){
	if(character>="0"&&character<="9")
		return true;
	else
		return false;
}

void retract(){
	fseek(file,-1,SEEK_CUR);
	character="";
}

int reserve(){
	if(){
	}else{
		return 0;
	}
}

int symbol(){
}

int constant(){
}

void return(){
}

int error(int errnum){
	switch(errnum){
	}
	exit(errnum);
}

void LexAnalyze(){
	token=" ";
	getchar();
	getnbc();

	switch(character){
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'G':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			while(letter()||digit()){
				concat();
				getchar();
			}
			retract();
			num=reserve();
			if(num!=0)
				return(num,0);
			else{
				val=symbol();
				return($SYMBOL,val);
			}
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			while(digit()){
				concat();
				getchar();
			}	
			retract();
			val=constant();
			return($constant,val);
			break;
		case '<':
			getchar();
			if(character=="=")
				return($LE,0);
			else{
				retract();
				return($L,0);
			}
			break;
		case '>':
			getchar();
			if(character=="=")
				return($GE,0);
			else{
				retract();
				return($G,0);
			}
			break;
		case '=':
			getchar();
			if(character=="=")
				return($E,0);
			else{
				retract();
				return($ASSIGN,0);
			}
			break;
		case '!':
			getchar();
			if(character=="=")
				return($NE,0);
			else
				error();
			break;
		case '+':
			return($ADD,0);
			break;
		case '-':
			return($SUB,0);
			break;
		case '*':
			return($MUL,0);
			break;
		case '/':
			return(%DIV,0);
			break;
		case '(':
			return($LPAR,0);
			break;
		case ')':
			return($RPAR,0);
			break;
		case ',':
			return($COM,0);
			break;
		case ';':
			return($SEM,0);
			break;
		default:
			error();
	}
}
