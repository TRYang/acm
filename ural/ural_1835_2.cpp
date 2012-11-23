#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
#define maxn 1000010

using namespace std;

struct node{
	char value;
	int size,f;
	node *son,*bro;
};
node *T[maxn];

struct Tnode{
	char value;
	Tnode *son,*bro;
	node *root;
	Tnode(){
		value='?';
		son=bro=NULL;
		root=NULL;
	}
	Tnode(char c){
		value=c;
		son=bro=NULL;
	}
};
Tnode *Tree[maxn];
int tn;

char s[maxn];
int main(){
	while (scanf("%s",s)!=EOF){
		int len=strlen(s);
		for (int i=0;i<len;i++)
			if (s[i]=='@'){
				int r=i+1;
				while (r<n){
					if (!islower(s[r]) && !islower(s[r-1])) break;
					++r;
				}
				
			}
	}
	return 0;
}