#include <sstream>
#include <iostream>
#include <string>
#include<stdlib.h>
#include<cstdlib>
#include<cstring>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

void getNextToken(string inp);
int countOpen=0,errorFlag=0,eF2=0,cou=0,undef=0,condFlag=0,dCou=0,undef2;
string error="";
string invToken;
string trial2="(3 5 (XYZ) ()(7))(NIL 5 ( ) (( )) 7 (( ) 9 ( )) )(DEFUN F23 (X) (PLUS X 12 55))";
string trial="(DEFUN MEM (X LIST)(COND ( (NULL LIST) NIL )( T (COND( (EQ X (CAR LIST))T )( T (MEM X (CDR LIST)))))))(MEM 103 (QUOTE (0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144)))";
string x[20000];
int count=0,open=0;

struct Node{
	string data;
	Node *right;
	Node *left;
	
};
Node* root = NULL;




Node* GetNewNode(string data){
	Node* newNode =new Node();
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
Node* dList[10000];
//Node* aList;
//Node* aListTemp;
//Node* temp;



Node* eval(Node*, Node*);


void Insert(Node* root, string data)
{

		root->data=data;	
}


void makeTree(Node* root)
{

	if(x[count]=="(" && open!=0){
		root->left=GetNewNode("");
		count++;
		open++;
		makeTree(root->left);
		root->right=GetNewNode("");
		makeTree(root->right);
	}
	else if(x[count]==")"){
		root->data= "NIL";
		count++;
		open--;
	}

	else if(x[count][0]>47)
	{
		root->left=GetNewNode("");
		Insert(root->left, x[count]);
		
		root->right=GetNewNode("");
		count++;
		makeTree(root->right);
		
	}
}

//print tree function
void print(Node* root)
{
	
	if(root!=NULL){
		if(root->left==NULL && root->right==NULL)
		{
				cout<<root->data;
		}
		else{
			if(root->right->data=="NIL")
			{
				
				print(root->left);
				cout<<")";
			}
			else if(root->right->data!="NIL" && root->right->data!="")
			{
				
				print(root->left);
				cout<<" . ";
				print(root->right);
				cout<<")";
			}
			else if(root->right->data!="NIL")
			{
				print(root->left);
				cout<<" ";
				print(root->right);
			}
			
		}
	}
}

void printList(Node* root)
{
	if(undef2==2)return;
	else if(undef==1)
	{
		cout<<"ERROR: "+error;
		undef2=2;
		return;
		
	}
	else if(root!=NULL)
		{
			if(root->left==NULL && root->right==NULL)
			{
				cout<<root->data+" ";
			}
			else{
				cout<<"(";
				print(root);
			}
		}
		
}

//functions car, cdr, intcheck, plus, minus..

void copy(Node* s, Node* body)
{
	s->data=body->data;
	if(body->left!=NULL)
	{
		s->left=GetNewNode("");
		copy(s->left,body->left);
	}
	if(body->right!=NULL)
	{
		s->right=GetNewNode("");
		copy(s->right,body->right);
	}
}
Node* copyNode(Node* body)
{
	Node* s=GetNewNode("");
	Node* x=s;
	copy(x,body);
	return s;
	
}


int lengthh(Node* s)
{
	if(s->right!=NULL)
	{
		if(s->right->data=="NIL")
		return 1;
		else
		return 1+lengthh(s->right);
	}
	else return 1;
	
}


Node* car (Node* root){
	return root->left;
}
Node* cdr (Node* root){
	return root->right;
}

string intCheck(Node* s)
{
	if((s->data[0]>64 && s->data[0]<91)|| s->data[0]==40 || s->data[0]==41 || s->data[0]==32)
	{
		return "NIL";
	}
	else return "T";
}

string pluss(Node* a, Node* b)
{
	string sum;
	sum=SSTR(atoi(a->data.c_str())+atoi(b->data.c_str()));
	return sum;
}
string minuss(Node* a, Node* b)
{
	string sum;
	sum=SSTR(atoi(a->data.c_str())-atoi(b->data.c_str()));
	
	return sum;
}
string lesss(Node* a, Node* b)
{
	string sum;
	if(atoi(a->data.c_str())<atoi(b->data.c_str()))
	return "T";
	else return "NIL";
}
string times(Node* a, Node* b)
{
	string sum;
	sum=SSTR(atoi(a->data.c_str())*atoi(b->data.c_str()));
	return sum;
}
string greaterr(Node* a, Node* b)
{
	string sum;
	if(atoi(a->data.c_str())>atoi(b->data.c_str()))
	return "T";
	else return "NIL";
}
string atomm(Node* a)
{
	if(a->data!="")
	return "T";
	else return "NIL";
}
string equall(Node* a, Node* b)
{
	if(atomm(a)=="T" && atomm(b)=="T")
	{
	if(a->data==b->data)
	return "T";
	else return "NIL";
	}
	else {
	undef=1;
	error="EQ is undefined";
	return"";
	}
}

string nulll(Node* a)
{
	if(atomm(a)=="T"){
	if(a->data=="" || a->data=="NIL")
	return "T";
	else return "NIL";
	}
	else return "NIL";
}
Node* cond(Node* aList, Node* s)
{
	if(s->data=="NIL" && condFlag==0)
	{
		undef=1;
			error="COND is undefined";
			return s;
	}
	else
	{
		if(lengthh(car(s))==2)
		{
			if(eval(aList,car(car(s)))->data!="NIL")
			{
				return eval(aList,car(cdr(car(s))));
				condFlag=1;
			}
			else cond(aList,cdr(s));
		}
		else
		{
			undef=1;
			error="COND is undefined";
			return s;
		}
	}
}

string bound(Node* s,Node* a)
{
	if(a->data!="NIL"){
	if(car(car(a))->data==s->data)
	return "T";
	else
	return bound(s,cdr(a));
	}
	else return "NIL";
}

Node* getval(Node* s,Node* a)
{
	if(car(car(a))->data==s->data)
	return cdr(car(a));
	else
	getval(s,cdr(a));
}
bool checkAtoms(string s)
		{
			int i;
			bool ch=true;
			string arr[17]={"T", "NIL", "CAR", "CDR", "CONS", "ATOM", "EQ", "NULL", "INT", "PLUS", "MINUS", "TIMES", "LESS", "GREATER", "COND", "QUOTE", "DEFUN"};
			for(i=0;i<17;i++)
			{
				if(s==arr[i])
				{
					ch=false;
				}
			}
			return ch;
		}
void addToDList(Node* s)
{
	dList[dCou]->left=GetNewNode("");
	dList[dCou]->left->left=GetNewNode(s->left->data);
	dList[dCou]->left->right=GetNewNode("");
	dList[dCou]->left->right->left=s->right->left;
	dList[dCou]->left->right->right=s->right->right->left;
	dList[dCou]->right=GetNewNode("NIL");
}

void evlist(Node* aList, Node* s)
{
	while(s->data!="NIL")
	{
		s->left=eval(aList,s->left);
		s=s->right;
	}
}

Node *addPairs(Node* s, Node* y)
{
	int i;
	Node*aListTemp=NULL;
	Node* temp=NULL;
	aListTemp=GetNewNode("");
	temp=aListTemp;
	int len=lengthh(s);
	for(i=0;i<len;i++)
	{
		temp->left=GetNewNode("");
		temp->left->left=y->left;
		temp->left->right=s->left;
		temp->right=GetNewNode("");
		temp=temp->right;
		s=s->right;
		y=y->right;
	}
	temp->data="NIL";	
	//printList(aListTemp);
	//cout<<"\n";
	return aListTemp;
}


//eval(s) function

Node* evalAtom(Node* sExp)
{
	if(undef==1)
	{
		return sExp;
	}
	if(sExp->data=="T")
	{
		return sExp;
	}
	else if(sExp->data=="NIL")
	{
		return sExp;
	}
	else if(sExp->data!="NIL" && sExp->data!="T")
	{
		if(intCheck(sExp)=="T")
		{
			return sExp;
		}
		else{
			undef=1;
			error="S is a single literal atom";
			return sExp;
		}
	}
}
Node* eval(Node* aList,Node* sExp)
{
	if(undef==1)
	{
		return sExp;
	}
	if(sExp->data=="")
	{
		if(car(sExp)->data=="PLUS"||car(sExp)->data=="MINUS"||car(sExp)->data=="GREATER"||car(sExp)->data=="LESS"||car(sExp)->data=="TIMES"||car(sExp)->data=="CONS"||car(sExp)->data=="EQ")
		{
			if(lengthh(sExp)==3){
			if(car(sExp)->data=="PLUS")
			{
				string val;
				if(intCheck(eval(aList,car(cdr(sExp))))=="T" && intCheck(eval(aList,car(cdr(cdr(sExp)))))=="T" && cdr(cdr(cdr(sExp)))->data=="NIL"){
				val=pluss(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;}
				else {if(undef!=1){undef=1;error="PLUS is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="MINUS")
			{
				string val;
					if(intCheck(eval(aList,car(cdr(sExp))))=="T" && intCheck(eval(aList,car(cdr(cdr(sExp)))))=="T")
					{
						val=minuss(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
						sExp->data=val;
						
						sExp->right=NULL;
						sExp->left=NULL;
						return sExp;
					}
					else {if(undef!=1){undef=1;error="MINUS is undefined";}return sExp;}
				
			}
			else if(car(sExp)->data=="TIMES")
			{
				string val;
				if(intCheck(eval(aList,car(cdr(sExp))))=="T" && intCheck(eval(aList,car(cdr(cdr(sExp)))))=="T" && cdr(cdr(cdr(sExp)))->data=="NIL"){
				val=times(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;}
				else {if(undef!=1){undef=1;error="TIMES is undefined";}return sExp;}
			}
			
			else if(car(sExp)->data=="LESS")
			{
				string val;
				if(cdr(cdr(cdr(sExp)))->data=="NIL"){
				val=lesss(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="LESS is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="GREATER")
			{
				
				string val;
				if(cdr(cdr(cdr(sExp)))->data=="NIL"){
				val=greaterr(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="GREATER is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="EQ")
			{
				string val;
				if(cdr(cdr(cdr(sExp)))->data=="NIL"){
				val=equall(eval(aList,car(cdr(sExp))),eval(aList,car(cdr(cdr(sExp)))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="EQ is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="CONS")
			{
				sExp->left=eval(aList,car(cdr(sExp)));
				sExp->right=eval(aList,car(cdr(cdr(sExp))));
				return sExp;			
			}	
		}
		else{
			if(undef!=1){undef=1;error="Expression is undefined";}
			return sExp;
		}
		}
		
		
		
		
		else if(car(sExp)->data=="QUOTE"||car(sExp)->data=="CDR"||car(sExp)->data=="CAR"||car(sExp)->data=="INT"||car(sExp)->data=="NULL"||car(sExp)->data=="ATOM")
		{
			if(lengthh(sExp)==2){
			if(car(sExp)->data=="ATOM")
			{
				string val;
				if(cdr(cdr(sExp))->data=="NIL"){
				val=atomm(eval(aList,car(cdr(sExp))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="ATOM is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="INT")
			{
				if(cdr(cdr(sExp))->data=="NIL"){
				string val;
				val=intCheck(eval(aList,car(cdr(sExp))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="INT is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="NULL")
			{
				if(cdr(cdr(sExp))->data=="NIL"){
				string val;
				val=nulll(eval(aList,car(cdr(sExp))));
				sExp->data=val;
				sExp->right=NULL;
				sExp->left=NULL;
				return sExp;
				}
				else {if(undef!=1){undef=1;error="NULL is undefined";}return sExp;}
			}
		
		
			else if(car(sExp)->data=="CAR")
			{
				Node * s=eval(aList,car(cdr(sExp)));
				if(s->right!=NULL){
					
					return car(s);
					
				
				}
				else {if(undef!=1){undef=1;error="CAR is undefined";}return sExp;}
			}
			else if(car(sExp)->data=="CDR")
			{
				Node * s=eval(aList,car(cdr(sExp)));
					if(s->right!=NULL)
					{	
						return cdr(s);
					}
					else{if(undef!=1){undef=1;error="CDR is undefined";}return sExp;}
					
				
			}
			else if(car(sExp)->data=="QUOTE")
			{
				if(cdr(cdr(sExp))->data=="NIL"){
				return car(cdr(sExp));
				}
				else {undef=1;error="QUOTE is undefined";}return sExp;
			}
		}
		else{
			if(undef!=1){undef=1;error="Expression is undefined";}
			return sExp;
		}
		}
		
		
	
		
		
		else if(car(sExp)->data=="COND")
		{
			if(lengthh(sExp)!=1){
			if(car(sExp)->data=="COND")
			{
					if(car(cdr(sExp))->data=="")
					{
						return cond(aList,cdr(sExp));
					}
					else{
						if(undef!=1){undef=1;error="COND is undefined";} return sExp;	
					}
			}
			else
			{
				if(undef!=1){undef=1;error="Expression undefined";} return sExp;	
			}
		}
		
		}
		
		else if(car(sExp)->data=="DEFUN")
		{
			
			if(lengthh(sExp)==4)
			{
			if(checkAtoms(car(cdr(sExp))->data) && (((car(cdr(sExp))->right==NULL && (car(cdr(sExp)))->left==NULL))|| (car(cdr(sExp)))->data=="NIL") && intCheck(car(cdr(sExp)))=="NIL")
			{
				
				Node* params=sExp->right->right->left;
				if((params->left->left!=NULL && params->left->right!=NULL))
				{
					if(undef!=1){undef=1;error="Expression undefined2";} return sExp;
				}
				Node* paramsCheck=params;
				while(params->data!="NIL")
				{
					int paramFlag=0;
					while(paramsCheck->data!="NIL")
					{
						if(paramsCheck->left->data==params->left->data)
						{
							paramFlag++;
						}
						paramsCheck=paramsCheck->right;
					}
					if(paramFlag>1)
					{
						if(undef!=1){undef=1;error="Expression undefined3";} return sExp;
					}
					if(!checkAtoms(params->left->data) || ((params->left->right!=NULL)&&(params->left->left!=NULL)) || intCheck(params->left)=="T")
					{
						if(undef!=1){undef=1;error="Expression undefined4";} return sExp;
					}
					params=params->right;
				}
			
			dList[dCou]=GetNewNode("");
	
			addToDList(cdr(sExp));
			sExp->data=car(cdr(sExp))->data;
			sExp->left=NULL;
			sExp->right=NULL;
			dCou++;
			return sExp;
			}
			else
			{
				if(undef!=1){undef=1;error="Expression undefined";} return sExp;	
			}
			}
			else
			{
				if(undef!=1){undef=1;error="Expression undefined";} return sExp;	
			}
			
		}
		else if(intCheck(car(sExp))=="NIL" && car(sExp)->data!="")
		{
			
			int i;
			int funcFlag=0;
			for(i=0;i<dCou;i++)
			{
				if(car(sExp)->data==dList[i]->left->left->data)
				{
					
					
					Node* arg=cdr(sExp);
					Node* dListParams = dList[i]->left->right->left;
					if(lengthh(dListParams)==lengthh(arg))
					{
						funcFlag=1;
						evlist(aList,cdr(sExp));
						Node* aList=addPairs(cdr(sExp), dListParams);
						
						Node *bod=copyNode(dList[i]->left->right->right);
						
						sExp=eval(aList,bod);
						
						return sExp;
					}
					
				}
			}
			if(funcFlag==0)
			{
				if(undef!=1){undef=1;error="Expression is undefined";}
				return sExp;
			}
			return sExp;
			}
		
		else{
			if(undef!=1){undef=1;error="Expression is undefined";}
			return sExp;
			}
	}
		
	else if(sExp->data=="T")
	{
		return sExp;
	}
	else if(sExp->data=="NIL")
	{
		return sExp;
	}
	else if(sExp->data!="NIL" && sExp->data!="T")
	{
		if(intCheck(sExp)=="T")
		{
			return sExp;
		}
		else if(bound(sExp,aList)=="T")
		{
			//printList(aList);
			return getval(sExp,aList);
			
		}
		else{
			undef=1;
			error="Eval of literal atom";
			return sExp;
		}
	}
}


void parse(){

	if(x[count]=="(" && open==0)
	{
		root=GetNewNode("");
		open++;
		count++;
		makeTree(root);
		root=eval(NULL,root);
		
	printList(root);
		cout<<"\n";
	undef=0;	
	}
	else {
	root=GetNewNode(x[count]);
	root=evalAtom(root);
	
	printList(root);
	cout<<"\n";
	undef=0;	
	count++;
	}
}


void getNextToken(string inp)
{
	int i=0, num=0;
	string token;
	while(i<inp.length())
	{
		if(inp[i]>64 && inp[i]<91)
		{
			
			token=inp[i];
			i++;
			while(inp[i]!=32 && inp[i]!='\0' && inp[i]!=40 && inp[i]!=41)
			{
			
				token=token+inp[i];
				i++;
			}
			x[cou++]=token;
		}
		else if(inp[i]>47 && inp[i]<58)
		{
			token=inp[i];
			i++;
			while((inp[i]>47 && inp[i<58])  ||(inp[i]>64 && inp[i]<91))
			{
				if(inp[i]>64 && inp[i]<91)
				{
					errorFlag=1;
				}
				token=token+inp[i];
				i++;
			}
			invToken=token;
			x[cou++]=token;
			if(errorFlag==1)
			return;
		}
		else if(inp[i]==40)
		{
			countOpen++;
			i++;
			x[cou++]="(";
		}
		else if(inp[i]==41)
		{
			countOpen--;
			if(countOpen<0)
			{
				eF2=2;
				return;
			}
			i++;
			x[cou++]=")";
		}
		else if(inp[i]=='\0')
		{
			return;
		}
		else if(inp[i]==32)
		{
			i++;
		}
	}	
}
void checkGrammar(string inp)
{
	
	int i=0;
	while(i<inp.length()){
	if(inp[i]==40)
		{
			countOpen++;
			i++;
		}
	else if(inp[i]==41)
		{
			countOpen--;
			if(countOpen<0)
			{
				eF2=2;
				return;
			}
			i++;
		}
	else if(inp[i]=='\0')
		{
			return;
		}
	else
		{
			i++;
		}
	}
}
int main()
{
	
	string line,s="";
		while(getline(cin,line))
    	{
      		s=s+line;
      	}


	checkGrammar(s);
	if(countOpen!=0 || eF2==2)
	{
		cout<<"ERROR: Invalid input, Not equal opening and closing brackets or incorrectly placed";
		return 0;
	} 
	countOpen=0;
	getNextToken(s);
	if(errorFlag==1)
	{
		cout<<"ERROR: Invalid Token, "<<invToken;
		return 0;
	}
	else{
	int i=0;
	while(i!=cou){
		parse();
		i=count;
	}
}

}





