#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 1000010
int father[maxn];//并查集
int h[maxn];//高度
int len[maxn];//block的宽
int tot[maxn];//block的总积木数
int bn;//总的block数
int root,left[maxn],right[maxn],rp[maxn],sz[maxn];//平衡树
char s[100];
int m;
void init(){
	int i,j,k;
	bn=0;
	for (i=1;i<=1000000;i++) father[i]=i;
	for (i=1;i<=1000000;i++) len[i]=1;
	root=0;
	rp[0]=1000000000;
	sz[0]=0;
}
int Sign(char *s){
	if (s[0]=='p') return 0;
	if (s[0]=='t' && s[1]=='p') return 1;
	if (s[0]=='t' && s[1]=='o') return 2;
	if (s[0]=='c') return 3;
	if (s[0]=='l') return 4;
	return 5;
}
void right_rotate(int &x){
	int y=left[x];
	left[x]=right[y];
	right[y]=x;
	sz[y]=sz[x];
	sz[x]=1+sz[left[x]]+sz[right[x]];
	x=y;
}
void left_rotate(int &x){
	int y=right[x];
	right[x]=left[y];
	left[y]=x;
	sz[y]=sz[x];
	sz[x]=1+sz[left[x]]+sz[right[x]];
	x=y;
}
void Insert(int &p,int v){
	if (p==0){
		rp[v]=rand()%(10000000);
		sz[v]=1;
		left[v]=right[v]=0;
		p=v;
		return;
	}
	sz[p]++;
	if (v<p){
		Insert(left[p],v);
		if (rp[v]<rp[p]) right_rotate(p);
	}else{
		Insert(right[p],v);
		if (rp[v]<rp[p]) left_rotate(p);
	}
}
void Delete(int &p,int v){
	if (p==v){
		if (left[p]==0 && right[p]==0){
			p=0;
			return;
		}
		if (rp[left[p]]<rp[right[p]]){
			right_rotate(p);
			sz[p]--;
			Delete(right[p],v);
		}else{
			left_rotate(p);
			sz[p]--;
			Delete(left[p],v);
		}
		return;
	}
	sz[p]--;
	if (v<p) Delete(left[p],v);else Delete(right[p],v); 
}
int ask(int p,int rank){
	if (sz[left[p]]+1==rank) return p;
	if (rank<=sz[left[p]]) return ask(left[p],rank);else
		return ask(right[p],rank-1-sz[left[p]]);
}
int Find(int x){
	int fx,p,next;
	for (p=x;father[p]!=p;p=father[p]);
	fx=p;
	for (p=x;father[p]!=fx;p=next){
		next=father[p];
		father[p]=fx;
	}
	return fx;
}
int main(){
	int i,j,k;
	int x,c,t;
	//freopen("test.txt","r",stdin);
	init();
	for (scanf("%d",&m);m>0;m--){
		scanf("%s",s);
		int sgn=Sign(s);
		if (sgn==0){
			scanf("%d %d",&x,&c);
			h[x]+=c;
			tot[Find(x)]+=c;
			if (h[x]==c){
				if (h[x+1]>0){
					Delete(root,x+1);
					len[x]+=len[x+1];
					tot[x]+=tot[x+1];
					father[x+1]=x;
				}
				if (h[x-1]>0){
					k=Find(x-1);
					len[k]+=len[x];
					tot[k]+=tot[x];
					father[x]=k;
				}else{
					Insert(root,x);
				}
			}
		}
		if (sgn==1){
			scanf("%d %d %d",&t,&x,&c);
			k=ask(root,t);
			tot[k]+=c;
			h[k+x-1]+=c;
		}
		if (sgn==2){
			printf("%d towers\n",sz[root]);
		}
		if (sgn==3){
			scanf("%d",&t);
			k=ask(root,t);
			printf("%d cubes in %dth tower\n",tot[k],t);
		}
		if (sgn==4){
			scanf("%d",&t);
			k=ask(root,t);
			printf("length of %dth tower is %d\n",t,len[k]);
		}
		if (sgn==5){
			scanf("%d %d",&t,&x);
			k=ask(root,t);
			printf("%d cubes in %dth column of %dth tower\n",h[k+x-1],x,t);
		}
	}
	return 0;
}



/*
6 5 9 0 4 3 0 0
*/