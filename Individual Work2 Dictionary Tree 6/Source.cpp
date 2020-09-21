#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;

struct Tree
{
	string data;
	Tree *left, *right;
	short int Balance;
};
typedef Tree *PtrTree;

void AddNew(PtrTree &ptr, string x, bool &h);
void Print1(PtrTree ptr, int h);
string Print2(PtrTree ptr, string &S, int i);
void Print(PtrTree ptr);
void LLrotation(PtrTree &p);
void RRrotation(PtrTree &p);
void LRrotation(PtrTree &p);
void RLrotation(PtrTree &p);

void AddNew(PtrTree &ptr, string x, bool &h)
{ //с учЄтом балансировки
	if (ptr == NULL)
	{
		ptr = new Tree;
		ptr->data = x;
		ptr->Balance = 0;
		ptr->left = NULL;
		ptr->right = NULL;
		h = true;
		return;
	}
	if (x < ptr->data)
	{ //проверка левых ветвей
		AddNew(ptr->left, x, h);
		if (h == true)
		{ //если выросла лева€ ветвь
			switch (ptr->Balance)
			{
			case -1:
			{ //требуетс€ балансировка
				if (ptr->left->Balance == -1) LLrotation(ptr);
				else LRrotation(ptr);
				ptr->Balance = 0;
				h = false; break;
			}
			case 0: ptr->Balance = -1; break;
			case 1:
			{
				ptr->Balance = 0; h = false; break;
			}
			}
		}
	}
	else if (x > ptr->data)
	{ //проверка правых ветвей
		AddNew(ptr->right, x, h);
		if (h == true)
		{ //если выросла права€ ветвь
			switch (ptr->Balance)
			{
			case -1:
			{
				ptr->Balance = 0; h = false; break;
			}
			case 0: ptr->Balance = 1; break;
			case 1:
			{ //требуетс€ балансировка
				if (ptr->right->Balance == 1) RRrotation(ptr);
				else RLrotation(ptr);
				ptr->Balance = 0; h = false; break;
			}
			}
		}
	}
	else
	{ //защита от повторного включени€
		h = false;
	}
}

void Print(PtrTree ptr)
{ //выводим двум€ способами сразу
	Print1(ptr, 0);
	cout << endl << endl;
	string S = "";
	S = Print2(ptr, S, 0);
	cout << S;
	cout << "\n\n//===========================================" <<
		"========================================================" << endl;
}

void Print1(PtrTree ptr, int h)
{ //вывод деревом, наклонЄнным на бок
  //с выводом показателей балансировки узлов
	if (ptr != NULL)
	{
		Print1(ptr->right, h + 1);
		cout << setw(12 + h * 12) << ptr->data << "(" << ptr->Balance << ")";
		cout << endl << endl;
		Print1(ptr->left, h + 1);
	}
}

string Print2(PtrTree ptr, string &S, int i)
{ //вывод строкой в формате из TreeWork31 в PT4
  //с нововведением применени€ от 0 до 4 разных скобок
	if (i == 5) i = 0;
	if (ptr != NULL)
	{
		S += ptr->data;
		//если есть поддеревь€, то выводим их
		if (ptr->left == NULL && ptr->right == NULL);
		else
		{
			if (i == 0) S += "(";
			else if (i == 1) S += "{";
			else if (i == 2) S += "[";
			else if (i == 3) S += "/";
			else S += "<";
			//если есть поддерево, то выводим его
			if (ptr->left != NULL)
			{
				Print2(ptr->left, S, i + 1);
			}
			if (ptr->right != NULL)
			{
				//при наличии правого поддерева всегда ставитс€ зап€та€
				//дл€ обозначени€ левого поддерева
				S += ",";
				Print2(ptr->right, S, i + 1);
			}
			if (i == 0) S += ")";
			else if (i == 1) S += "}";
			else if (i == 2) S += "]";
			else if (i == 3) S += "\\";
			else S += ">";
		}
	}
	return S;
}


void LLrotation(PtrTree &p)
{
	cout << "Ќарушение балансировки в узле " << p->data << endl;
	PtrTree q = p->left;
	q->Balance = 0; p->Balance = 0;
	p->left = q->right;
	q->right = p;
	p = q;
	cout << "¬ыполнен LL-поворот:" << endl << endl;
}

void RRrotation(PtrTree &p)
{
	cout << "Ќарушение балансировки в узле " << p->data << endl;
	PtrTree q = p->right;
	q->Balance = 0; p->Balance = 0;
	p->right = q->left;
	q->left = p;
	p = q;
	cout << "¬ыполнен RR-поворот:" << endl << endl;
}

void LRrotation(PtrTree &p)
{
	cout << "Ќарушение балансировки в узле " << p->data << endl;
	PtrTree q = p->left; PtrTree r = q->right;
	if (r->Balance < 0)
	{
		p->Balance = 1; q->Balance = 0;
	}
	else if (r->Balance > 0)
	{
		p->Balance = 0; q->Balance = -1;
	}
	else
	{
		p->Balance = 0; q->Balance = 0;
	}
	r->Balance = 0;
	p->left = r->right; q->right = r->left;
	r->left = q; r->right = p;
	p = r;
	cout << "¬ыполнен LR-поворот:" << endl << endl;
}

void RLrotation(PtrTree &p)
{
	cout << "Ќарушение балансировки в узле " << p->data << endl;
	PtrTree q = p->right; PtrTree r = q->left;
	if (r->Balance > 0)
	{
		p->Balance = -1; q->Balance = 0;
	}
	else if (r->Balance < 0)
	{
		p->Balance = 0; q->Balance = 1;
	}
	else
	{
		p->Balance = 0; q->Balance = 0;
	}
	r->Balance = 0;
	p->right = r->left; q->left = r->right;
	r->left = p; r->right = q;
	p = r;
	cout << "¬ыполнен RL-поворот:" << endl << endl;
}

void main()
{
	SetConsoleOutputCP(1251);
	string x; PtrTree ptr = NULL; bool h = false;
	ifstream File; File.open("Individual_2.txt");
	if (!File) cout << "Ќевозможно открыть файл. ѕроверьте путь к нему и название";
	else
	while (!File.eof())
	{
		File >> x; AddNew(ptr, x, h);
		Print(ptr);
	}
	File.close();
	system("pause > nul");
}