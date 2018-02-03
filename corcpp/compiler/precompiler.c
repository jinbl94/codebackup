#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCLUDE "include"
#define DEFINE "define"

struct def{
	char name[20];
	char value[20];
	struct def *next;
};

struct file_included{
	char name[20];
	struct file_included *next;
};

struct file_included *head_file=NULL,*current_file,*new_file;

void scanfile(char *file_name);
int is_name(char c);
void file_check(char *string,char *name);
void define_check(char *string,struct def *head_def,char *name);

void main(int argc,char **argv){
	for(int i=1;i<argc;i++){
		scanfile(argv[i]);
		current_file=head_file;
		while(current_file!=NULL){
			new_file=current_file->next;
			free(current_file);
			current_file=new_file;
		}
		head_file=NULL;
	}
	return;
}

void scanfile(char *file_name){
	FILE *file;
	file=fopen(file_name,"r");
	char c;
	char string[20];
	char *p_string=string;
	struct def *head_def=NULL,*current_def,*new_def;

	if(head_file){
		new_file=(struct file_included*)malloc(sizeof(struct file_included));
		strcpy(new_file->name,file_name);
		new_file->next=NULL;
		current_file->next=new_file;
		current_file=new_file;
	}else{
		new_file=(struct file_included*)malloc(sizeof(struct file_included));
		strcpy(new_file->name,file_name);
		new_file->next=NULL;
		head_file=new_file;
		current_file=new_file;
	}
	//scanf the file, save the defines
	c=fgetc(file);
	while(!feof(file)){
		switch(c){
			case '#':
				fscanf(file,"%s",p_string);
				if(!strcmp(p_string,DEFINE)){
					fscanf(file,"%s",p_string);
					define_check(p_string,head_def,file_name);
					if(head_def){
						new_def=(struct def*)malloc(sizeof(struct def));
						strcpy(new_def->name,p_string);
						fscanf(file,"%s",new_def->value);
						new_def->next=NULL;
						current_def->next=new_def;
						current_def=new_def;
					}else{
						new_def=(struct def*)malloc(sizeof(struct def));
						strcpy(new_def->name,p_string);
						fscanf(file,"%s",new_def->value);
						new_def->next=NULL;
						head_def=new_def;
						current_def=new_def;
					}
				}
				break;
			case '\"':
				c=fgetc(file);
				while(c!='\"'){
					c=fgetc(file);
				}
				c=fgetc(file);
				break;
			case '\'':
				c=fgetc(file);
				while(c!='\''){
					c=fgetc(file);
				}
				c=fgetc(file);
				break;
			default:
				break;
		}
		c=fgetc(file);
	}

	//scan the file, make all the replacements (includes and defines).
	rewind(file);
	c=fgetc(file);
	while(!feof(file)){
		switch(c){
			case '#':
				fscanf(file,"%s",p_string);
				if(!strcmp(p_string,INCLUDE)){
					//include
					fscanf(file,"%s",p_string);
					p_string[strlen(p_string)-1]=0;
					file_check(&p_string[1],file_name);
					scanfile(&p_string[1]);
					c=fgetc(file);
				}else if(!strcmp(p_string,DEFINE)){
					//define
					fscanf(file,"%s",p_string);
					fscanf(file,"%s",p_string);
					c=fgetc(file);
					c=fgetc(file);
				}else{
					//other cases
				}
				break;
			case '\"':
				fprintf(stdout,"%c",c);
				c=fgetc(file);
				while(c!='\"'){
					fprintf(stdout,"%c",c);
					if(c=='\\'){
						c=fgetc(file);
						fprintf(stdout,"%c",c);
					}
					c=fgetc(file);
				}
				break;
			case '\'':
				fprintf(stdout,"%c",c);
				c=fgetc(file);
				while(c!='\''){
					fprintf(stdout,"%c",c);
					if(c=='\\'){
						c=fgetc(file);
						fprintf(stdout,"%c",c);
					}
					c=fgetc(file);
				}
				break;
			case '/':
				c=fgetc(file);
				if(c=='/'){
					fscanf(file,"%s",p_string);
					c=fgetc(file);
				}else{
					fprintf(stderr,"\"/%c\" unknown",c);
					exit(1);
				}
				break;
			default:
				//other cases
				if(is_name(c)){
					p_string=string;
					int i=0;
					for(;is_name(c);i++){
						string[i]=c;
						c=fgetc(file);
					}
					p_string[i]=0;
					current_def=head_def;
					while(current_def){
						//defined string
						if(!strcmp(p_string,current_def->name)){
							p_string=current_def->value;
							break;
						}
						current_def=current_def->next;
					}
					current_def=head_def;
					fprintf(stdout,"%s",p_string);
				}else{
					//other characters
				}
				break;
		}
		fprintf(stdout,"%c",c);
		c=fgetc(file);
	}

	//free malloced memory while scan file
	while(current_def!=NULL){
		new_def=current_def->next;
		free(current_def);
		current_def=new_def;
	}

	fclose(file);
}

int is_name(char c){
	if(('0'<=c&&'9'>=c)||('A'<=c&&'Z'>=c)||('a'<=c&&'z'>=c)||c=='_'){
		return 1;
	}else{
		return 0;
	}
}

void define_check(char *string,struct def *head_def,char *name){
	if(string){
		for(int i=0;i<strlen(string);i++){
			if(is_name(string[i])){
			}else{
				fprintf(stderr,"%s: ileagle define in %s\n",string,name);
				exit(1);
			}
		}
		struct def *temp=head_def;
		while(temp){
			if(!strcmp(string,temp->name)){
				fprintf(stderr,"%s: redefined in %s\n",string,name);
				exit(1);
			}
			temp=temp->next;
		}
	}else{
		fprintf(stderr,"%s: ileagle define in %s\n",string,name);
		exit(1);
	}
}

void file_check(char *string,char *name){
	new_file=head_file;
	while(new_file){
		if(!strcmp(string,new_file->name)){
			fprintf(stderr,"%s: includ error in %s\n",string,name);
			exit(1);
		}
		new_file=new_file->next;
	}
}
