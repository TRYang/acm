#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1000010

using namespace std;

static int total=0;

struct node{
	int size;
	int f;
	char value;
	node *son,*bro;
	
	node(){
		value='?';
		son=bro=NULL;
		size=f=0;
	}
	node(char c){
		value=c;
		size=(c!='?');
		f=(c=='.');
		son=bro=NULL;
	}
	node* insert(char c){
		if (this->son==NULL || this->son->value>c){
			node *d=new node(c);
			d->bro=this->son;
			this->son=d;
			return d;
		}
		for (node *it=this->son;it!=NULL;it=it->bro){
			if (it->value == c) return it;
			if (it->value < c && (it->bro == NULL || it->bro->value > c)){
				node *d=new node(c);
				d->bro=it->bro;
				it->bro=d;
				return d;
			}
		}
	}
};

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
		root=new node();
	}
	Tnode* insert(char c){
		if (this->son==NULL || this->son->value > c){
			Tnode *d=new Tnode(c);
			d->bro=this->son;
			this->son=d;
			return d;
		}
		for (Tnode *it=this->son;it!=NULL;it=it->bro){
			if (it->value == c) return it;
			if (it->value < c && (it->bro == NULL || it->bro->value > c)){
				Tnode *d=new Tnode(c);
				d->bro=it->bro;
				it->bro=d;
				return d;
			}
		}
	}
} *root;

node* Merge(node* a,node* b){
	node *ret=new node(a->value);
	node *i=a->son,*j=b->son,*ti,*tj;
	node *pt=NULL;
	delete a;
	delete b;
	while (i!=NULL || j!=NULL){
		if (i!=NULL && j!=NULL && i->value == j->value){
			ti=i->bro;
			tj=j->bro;
			if (pt==NULL){
				ret->son=Merge(i,j);pt=ret->son;
			}else{
				pt->bro=Merge(i,j);pt=pt->bro;
			}
		}else
		if (j==NULL || (i!=NULL && i->value < j->value)){
			ti=i->bro;
			tj=j;
			if (pt==NULL){
				ret->son=i;pt=i;
			}else{
				pt->bro=i;pt=i;
			}
		}else{
			ti=i;
			tj=j->bro;
			if (pt==NULL){
				ret->son=j;pt=j;
			}else{
				pt->bro=j;pt=j;
			}
		}
		i=ti;
		j=tj;
		ret->size+=pt->size;
		ret->f+=pt->f;
	}
	return ret;
}

char s[maxn];
long long ans;

node *Q[maxn];
void bfs_sub(node *sp){
	int qn=1;
	Q[0]=sp;
	for (int tp=0;tp<qn;tp++)
		for (node *it=Q[tp]->son;it!=NULL;it=it->bro) Q[qn++]=it;
	for (int tp=qn-1;tp>=0;tp--){
		node *p=Q[tp];
		p->size=(p->value!='?');
		p->f=(p->value=='.');
		for (node *it=p->son;it!=NULL;it=it->bro){
			p->size+=it->size;
			p->f+=it->f;
		}
	}
}

Tnode *q[maxn];
void BFS(Tnode *sp){
	int qn=1;
	q[0]=sp;
	for (int p=0;p<qn;p++)
		for (Tnode *it=q[p]->son;it!=NULL;it=it->bro){
			q[qn++]=it;
		}
	for (int tp=qn-1;tp>0;tp--){
		Tnode *p=q[tp];
		bfs_sub(p->root);
		for (Tnode *it=p->son;it!=NULL;it=it->bro){
			if (it->root==NULL || it->root->size==0) continue;
			if (p->root==NULL || p->root->size==0) p->root=it->root;else
			if (p->root->size > it->root->size){
				p->root = Merge(p->root,it->root);
			}else{
				p->root = Merge(it->root,p->root);
			}
		}
		if (p->value != '.') ans+=(p->root->size - p->root->f);
	}
	// printf("c=%c : %d %d\n",p->value,p->root->size,p->root->f);
}

int main(){
	int maxl=-1;
	root=new Tnode();
	while (scanf("%s",s)!=EOF){
		int len=strlen(s);
		maxl=max(maxl,len);
		int p=0;
		while (p<len && s[p]!='@') ++p;
		if (p==len) continue;
		Tnode *tmp=root;
		for (int i=p+1;i<len;i++){
			if ((s[i-1]=='.' || s[i-1]=='@') && s[i]=='.') break;
			tmp=tmp->insert(s[i]);	
		}
		node *cur=tmp->root;
		if (cur==NULL) continue;
		for (int i=p-1;i>=-1;i--){
			if (i==-1 || ((s[i+1]=='.' || s[i+1]=='@') && s[i]=='.')){
				for (int j=i+1;j<p;j++)
					if (s[j]=='.') tmp->root->f++;
				break;
			}
			cur=cur->insert(s[i]);
		}
	}
	ans=0;
	BFS(root);
	printf("%lld\n",ans);
	return 0;
}