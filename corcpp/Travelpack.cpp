#include<iostream>
#include<time.h>
#define SIZEOFBOX 15//define the size of the boxes (can be changed as you like).
using namespace std;
typedef struct TrNode//Node of the Bitree. Used to form a binary tree.
{
	TrNode *Lchild, *Rchild;
	int size, number = 0;
}Tnode, *Tnodeptr;
typedef struct BoxNode//Node of the boxes. Used to form a list.
{
	BoxNode *next;
	int rest;
}Bnode, *Bnodeptr;
class TravelPack
{
private:
	Tnodeptr bt, m, Th, R;
	Bnodeptr head, Bh, p, s;
public:
	TravelPack()//Initialize the head node.
	{
		head = (Bnodeptr)malloc(sizeof(Bnode));
		head->rest = 0;
		head->next = NULL;
		bt = (Tnodeptr)malloc(sizeof(Tnode));
		bt->number = 0;
		bt->Lchild = bt->Rchild = NULL;
		bt->size = SIZEOFBOX / 2;
	}
	void en_tree(Tnodeptr s); 
	void b_form();
	void b_inorderR(Tnodeptr temp);
	void b_inorderL(Tnodeptr temp);
	void b_enbox();
	void destroy(Tnodeptr temp);
	void show(Tnodeptr temp);
	~TravelPack()
	{
		destroy(bt);
		p = head->next; cout << endl << "The left size of each box:"<<endl;
		for (; head->next != NULL;)
		{
			head->rest++;
			cout << p->rest << " ";//Output the rest size of each box.
			head->next = p->next;
			free(p);
			p = head->next;
		}
		cout <<endl<<"formed "<<head->rest<<" boxes totally!!"<< endl;
		free(head);
	}
};
void TravelPack::show(Tnodeptr temp)//Show the binary tree inorderly.
{
	if (temp != NULL)
	{
		show(temp->Lchild);
		cout << "(" << temp->size << "," << temp->number<<")";
		show(temp->Rchild);
	}
}
void TravelPack::en_tree(Tnodeptr s)//Make the en_tree function which is mean to add nodes to the binary tree
{
	Tnodeptr q;
	if (bt == NULL)bt = s;
	else
	{
		q = bt;
		for (;;)
		{
			if (s->size < q->size)
			{
				if (q->Lchild != NULL)q = q->Lchild;
				else{ q->Lchild = s; break; }
			}
			else if (s->size == q->size){ q->number++; break; }
			else
			{
				if (q->Rchild != NULL)q = q->Rchild;
				else{ q->Rchild = s; break; }
			}
		}
	}
}
void TravelPack::b_form()
{
	int temp=0;
	cout << "These are the size of each pack:"<<endl;
	srand((unsigned)time(NULL));
	for (int i=0; i < 100;i++)
	{
		temp = rand()%SIZEOFBOX+1;//Produce random number for the pack's size. Then form 100 (can be changed as you like) packs.
		m = (Tnodeptr)malloc(sizeof(Tnode));//Initialize the binary tree nodes.
		m->Lchild = m->Rchild = NULL;
		m->size = temp; m->number = 1; cout << " " << temp;
		en_tree(m);//Put the packs into the binary tree.
	}
	cout<< endl;
	R = bt->Rchild; Th = bt;
}
void TravelPack::b_inorderR(Tnodeptr temp)//Inorder run the right child.
{
	if (temp != NULL)
	{
		b_inorderR(temp->Lchild);
		for (; temp->number > 0;)
		{
			s = (Bnodeptr)malloc(sizeof(Bnode));
			s->rest = SIZEOFBOX - temp->size;
			s->next = head->next; head->next = s;
			temp->number--; cout << temp->size << " ";
		}
		b_inorderR(temp->Rchild);
	}
	Bh = head;
}
void TravelPack::b_inorderL(Tnodeptr temp)//Inorder run the left child.
{
	if (temp != NULL)
	{
		b_inorderL(temp->Lchild);
		for (; temp->number > 0;)
		{
			for (; Bh->rest < temp->size&&Bh->next != NULL; Bh = Bh->next);
			if (Bh->rest >= temp->size){ Bh->rest = Bh->rest - temp->size; temp->number--; cout << temp->size << " "; }
			else
			{
				s = (Bnodeptr)malloc(sizeof(Bnode));
				s->rest = SIZEOFBOX - temp->size;
				s->next = NULL; Bh->next = s;
				temp->number--; cout << temp->size << " ";
			}
		}
		b_inorderL(temp->Rchild);
	}
}
void TravelPack::b_enbox()//Put the right child tree firstly, the top node comes second and the left child last.
{
	cout << "Information of the nodes of the binray tree (SIZE,NUMBER):"<<endl; show(bt); cout << endl;//Use function "show()".
	cout << "The order of the packs' being put into the boxes:"<<endl;
	b_inorderR(R);
	for (; (bt->number + 1) / 2 != 0;)//Deal the top node.
	{
		s = (Bnodeptr)malloc(sizeof(Bnode));
		s->rest = SIZEOFBOX - 2 * bt->size;
		s->next = head->next; head->next = s;
		bt->number -= 2; cout << bt->size << " ";
	}
	if (bt->number == 1)
	{
		for (p=head; p->next != NULL; p = p->next);
		s = (Bnodeptr)malloc(sizeof(Bnode));
		s->rest = SIZEOFBOX - SIZEOFBOX / 2;
		s->next = NULL; p->next = s; cout << bt->size << " ";
	}
	b_inorderL(bt);
}
void TravelPack::destroy(Tnodeptr temp)//Destroy the binary tree.
{
	if (temp != NULL)
	{
		destroy(temp->Lchild);
		destroy(temp->Rchild);
		free(temp);
	}
}
void main()
{
	TravelPack travelpack;
	travelpack.b_form();
	travelpack.b_enbox();
}