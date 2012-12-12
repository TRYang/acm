/*
	1~n的字符串,在头和尾加一个字符,下标变为2~n+1.
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 400010
#define P 37

using namespace std;

typedef unsigned int LLU;

//一定要预处理
LLU pow[maxn];

struct node{
	int key,size;
	int rev;
	LLU hv[2];
	node *ch[2];
	node *father;
	node(){
		key=rev=size=hv[0]=hv[1]=0;
		ch[0]=ch[1]=NULL;
		father=NULL;
	}
	node(int x,node *c1,node *c2){
		key=x;
		father=NULL;
		rev=0;size=1;
		hv[0]=hv[1]=x;
		ch[0]=c1;ch[1]=c2;
	}
	void clear(){
		if (this->ch[0]!=NULL) this->ch[0]->clear();
		if (this->ch[1]!=NULL) this->ch[1]->clear();
		delete this;
	}
};
struct splay_tree{
	node *root;
		
	void init(){
		root=NULL;
	}
	
	void updata(node *p){
		if (p->rev){
			if (p->ch[0]!=NULL){
				p->ch[0]->rev^=1;
				swap(p->ch[0]->hv[0],p->ch[0]->hv[1]);
			}
			if (p->ch[1]!=NULL){
				p->ch[1]->rev^=1;
				swap(p->ch[1]->hv[0],p->ch[1]->hv[1]);
			}
			swap(p->ch[0],p->ch[1]);
			p->rev=0;
		}
		p->size=1;
		p->hv[0]=p->hv[1]=p->key;
		if (p->ch[0]!=NULL){
			p->hv[0] = p->ch[0]->hv[0] + p->hv[0] * pow[p->ch[0]->size];
			p->hv[1] += p->ch[0]->hv[1] * pow[1];
			p->size += p->ch[0]->size;
		}
		if (p->ch[1]!=NULL){
			p->hv[0] += p->ch[1]->hv[0] * pow[p->size];
			p->hv[1] = p->hv[1] * pow[p->ch[1]->size] + p->ch[1]->hv[1];
			p->size += p->ch[1]->size;
		}
	}
	
	void Rotate(node *p,int f){
		node *t=p->ch[f];
		p->ch[f]=t->ch[!f];
		if (t->ch[!f]!=NULL) t->ch[!f]->father=p;
		t->ch[!f]=p;
		t->father=p->father;
		if (t->father!=NULL){
			node *tf=t->father;
			tf->ch[tf->ch[1]==p]=t;
			updata(tf);
		}
		p->father=t;
		updata(p);
		updata(t);
	}
	
	void Splay(node *p){
		while (p->father!=NULL){
			node *fp=p->father;
			if (fp->father==NULL){
				Rotate(fp,fp->ch[1]==p);
			}else{
				node *ffp=fp->father;
				int d1=(ffp->ch[1]==fp),d2=(fp->ch[1]==p);
				if (d1==d2){
					Rotate(ffp,d1);
					Rotate(fp,d1);
				}else{
					Rotate(fp,d2);
					Rotate(ffp,d1);
				}
			}
		}
		root=p;
	}
	
	node* select(int rank){
		if (rank<=0 || rank>root->size) return NULL;
		node *p=root;
		int tot;
		while (1){
			updata(p);
			tot= (p->ch[0]==NULL)?0:p->ch[0]->size;
			if (tot+1==rank){
				Splay(p);
				return p;
			}
			if (rank<=tot) p=p->ch[0];else{
				rank-=(tot+1);
				p=p->ch[1];
			}
		}
	}
	
	node* maxmimum(node *p){
		updata(p);
		while (p->ch[1]!=NULL){
			p=p->ch[1];
			updata(p);
		}
		Splay(p);
		return p;
	}
	
	node* minimum(node *p){
		updata(p);
		while (p->ch[0]!=NULL){
			p=p->ch[0];
			updata(p);
		}
		Splay(p);
		return p;
	}
	
	void insert(int x,int key){
		node *p=select(x+1);
		root=new node(key,p->ch[0],p);
		p->ch[0]=NULL;
		if (root->ch[0]!=NULL){
			root->ch[0]->father=root;
			updata(root->ch[0]);
		}
		if (root->ch[1]!=NULL){
			root->ch[1]->father=root;
			updata(root->ch[1]);
		}
		updata(root);
	}
	
	void erase(int x){
		select(x);
		node *p1=root->ch[0],*p2=root->ch[1];
		p1->father=NULL;
		p2->father=NULL;
		delete root;
		root=join(p1,p2);
	}
	
	node* join(node *p1,node *p2){
		if (p1==NULL) return p2;
		if (p2==NULL) return p1;
		node *p=maxmimum(p1);
		p->ch[1]=p2;
		p2->father=p;
		updata(p2);
		updata(p);
		return p;
	}
	
	void reverse(int l,int r){
		node *tl,*tr;
		select(r);
		tr=root->ch[1];
		root->ch[1]=NULL;
		tr->father=NULL;
		updata(root);
		select(l);
		tl=root->ch[0];
		root->ch[0]=NULL;
		tl->father=NULL;
		
		updata(root);
		root->rev^=1;
		swap(root->hv[0],root->hv[1]);
		root=join(tl,root);
		root=join(root,tr);
	}
	
	LLU getHashValue(int l,int r){
		node *tl,*tr;
		select(r);
		tr=root->ch[1];
		root->ch[1]=NULL;
		tr->father=NULL;
		updata(root);
		select(l);
		tl=root->ch[0];
		root->ch[0]=NULL;
		tl->father=NULL;
		
		updata(root);
		LLU ret=root->hv[0];
		root=join(tl,root);
		root=join(root,tr);
		return ret;
	}
	
	int lcp(int l,int r){
		if (l>r) swap(l,r);
		if (l==r) return root->size-l;
		int L=1,R=root->size-r,mid;
		int ret=0;
		while (L<=R){
			mid=(L+R)>>1;
			if (getHashValue(l,l+mid-1)==getHashValue(r,r+mid-1)){
				L=mid+1;
				ret=mid;
			}else R=mid-1;
		}
		return ret;
	}
	
	void pr(node *p){
		updata(p);
		if (p->ch[0]!=NULL) pr(p->ch[0]);
		printf("%d ",p->key);
		if (p->ch[1]!=NULL) pr(p->ch[1]);
		if (p==root) puts("");
	}
	
	node* MakeTree(node *fp,char *s,int st,int en){
		int mid=(st+en)>>1;
		node *p=new node(s[mid]-'a'+7,NULL,NULL);
		if (fp!=NULL) p->father=fp;
		if (st<mid)	p->ch[0]=MakeTree(p,s,st,mid-1);
		if (mid<en) p->ch[1]=MakeTree(p,s,mid+1,en);
		updata(p);
		return p;
	}
	
} spt;