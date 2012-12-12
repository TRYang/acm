#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 300010
#define bln_upp 400
#define bln_low 200

using namespace std;

struct block{
	int list[bln_upp+1];
	int f,st,en,len;
	block *nxt,*pre;
	void pr(){
		puts("");
		for (int i=st;i!=en;i+=f) printf("%d ",list[i]);
		puts("");
	}
	block (){
		len=0;f=1;
		st=1;en=1;
		nxt=pre=NULL;
	}
};
block *head,*tail;
int a[maxn];
int n,m;
void MakeList(int *a,int n,block * &h,block * &t){
	//将数组a构造一个块表,返回头块和尾块的指针
	block *cur=new block();
	h=cur;
	for (int i=0;i<n;i++){
		int value=a[i];
		if (cur->len==bln_upp){
			block *tmp=new block();
			cur->nxt=tmp;	//next
			tmp->pre=cur;	//previous
			cur=tmp;
		}
		cur->len++;cur->en++;
		cur->list[cur->len]=value;
	}
	t=cur;
}
void GetLocate(int p,block *&a,int &lp){//查找第p的位置在哪个块的哪个位置
	if (p>n){
		a=tail;
		lp=a->en;
		return;
	}
	a=head;
	int tot=a->len;
	while (tot<p){
		a=a->nxt;
		tot+=a->len;
	}
	lp=p-(tot-a->len);
}
block *Combine(block *a,block *b){//将a,b两个块合并
	block *pr=a->pre,*nt=b->nxt;
	block *cur=new block();
	for (int i=a->st;i!=a->en;i+=a->f){
		cur->len++;cur->en++;
		cur->list[cur->len]=a->list[i];
	}
	delete a;
	for (int i=b->st;i!=b->en;i+=b->f){
		cur->len++;cur->en++;
		cur->list[cur->len]=b->list[i];
	}
	delete b;
	cur->pre=pr;
	cur->nxt=nt;
	if (pr==NULL) head=cur;else cur->pre->nxt=cur;
	if (nt==NULL) tail=cur;else cur->nxt->pre=cur;
	return cur;
}
void split(block *&a,int p){//将a块从第p个位置断开,返回的块
	if (p==1 || p>a->len) return;
	block *cur=new block();
	p=a->st+(p-1)*a->f;
	for (int i=p;i!=a->en;i+=a->f){
		int value=a->list[i];
		cur->len++;
		cur->en++;
		cur->list[cur->len]=value;
	}
	a->en=p;
	a->len=a->en-a->st;
	if (a->len<0) a->len*=-1;
	cur->nxt=a->nxt;
	a->nxt=cur;
	cur->pre=a;
	if (cur->nxt!=NULL) cur->nxt->pre=cur;
	if (cur->nxt==NULL) tail=cur;
	a=cur;
}
void Get(int x,int y,block *&h,block *&t){//序列的第x个位置到第y个位置取出来
	block *cur;
	int xp;
	GetLocate(x,cur,xp);
	split(cur,xp);
	h=cur;
	GetLocate(y+1,cur,xp);
	split(cur,xp);
	t=cur->pre;
	if (h!=t){
		if (h->len+h->nxt->len<=bln_low){
			if (h->nxt==t){
				h=t=Combine(h,h->nxt);
				return;
			}
			h=Combine(h,h->nxt);
		}
		if (t->len+t->pre->len<=bln_low){
			if (t->pre==h){
				h=t=Combine(t->pre,t);
				return;
			}
			t=Combine(t->pre,t);
		}
	}
}
block *q[300000];
void Reverse(block *h,block *t){				//将h到t翻转
	int qn=0;
	for (block *cur=h;cur!=t;cur=cur->nxt) q[qn++]=cur;
	q[qn++]=t;
	if (h->pre!=NULL) h->pre->nxt=t;else head=t;
	if (t->nxt!=NULL) t->nxt->pre=h;else tail=h;
	t->pre=h->pre;
	h->nxt=t->nxt;
	for (int i=0;i<qn;i++){
		if (i<qn-1) q[i]->pre=q[i+1];
		if (i>0) q[i]->nxt=q[i-1];
		q[i]->st=q[i]->en-q[i]->f;
		q[i]->f*=-1;
		q[i]->en=q[i]->st+q[i]->f*q[i]->len;
	}
	if (t->pre!=NULL && t->len+t->pre->len<=bln_low){
		if (h==t){
			h=t=Combine(t->pre,t);
		}else t=Combine(t->pre,t);
	}
	if (h->nxt!=NULL && h->len+h->nxt->len<=bln_low){
		if (h==t){
			h=t=Combine(h,h->nxt);
		}else h=Combine(h,h->nxt);
	}
}
void Cut(block *h,block *t){//将h到t这些块切下来
	if (h->pre!=NULL) h->pre->nxt=t->nxt;else head=t->nxt;
	if (t->nxt!=NULL) t->nxt->pre=h->pre;else tail=h->pre;
}
void Insert(int p,block *h,block *t){//将h,t插入到第p个位置
	if (p==0){		//注意原序列非空
		h->pre=NULL;t->nxt=head;
		head->pre=t;head=h;
		if (t->nxt==NULL) tail=t;
		return;
	}
	if (p==n){		//注意原序列非空
		t->nxt=NULL;h->pre=tail;
		tail->nxt=h;tail=t;
		if (h->pre==NULL) head=h;
	}
	block *cur;
	int xp;
	GetLocate(p,cur,xp);
	split(cur,xp);
	block *tmp=cur;
	cur=cur->pre;
	cur->nxt=h;
	h->pre=cur;
	t->nxt=tmp;
	tmp->pre=t;
	if (h->pre!=NULL && h->len+h->pre->len<=bln_low){
		if (h==t){
			h=t=Combine(h->pre,h);
		}else t=Combine(h->pre,h);
	}
	if (t->nxt!=NULL && t->len+t->nxt->len<=bln_low){
		if (h==t){
			h=t=Combine(t,t->nxt);
		}else h=Combine(t,t->nxt);
	}
}
