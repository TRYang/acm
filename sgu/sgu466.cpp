#include <stdio.h>
#include <string.h>
#include <set>
#include <algorithm>
#include <queue>
#define maxn 100010

using namespace std;

set<int> slot[maxn];
int tree[maxn<<2];
int pos[maxn],tlen[maxn];
char s[maxn];
int bl[maxn];
int n,m;
void init(int p,int tl,int tr){
	tree[p]=0;
	if (tl==tr){
		slot[tl].clear();
		return;
	}
	int m=(tl+tr)>>1;
	init(p<<1,tl,m);
	init((p<<1)+1,m+1,tr);
}
void ins(int p,int tl,int tr,int k,int fp){
	if (tl==tr){
//		printf("%d %d\n",k,fp);
		slot[tl].insert(fp);
		bl[fp]=k;
		if (fp+k-1>n) bl[fp+k-1-n]=k;else bl[fp+k-1]=k;
		tree[p]=k;
		return;
	}
	int m=(tl+tr)>>1;
	if (k<=m) ins(p<<1,tl,m,k,fp);else ins((p<<1)+1,m+1,tr,k,fp);
	tree[p]=max(tree[p<<1],tree[(p<<1)+1]);
}
void del(int p,int tl,int tr,int k,int fp){
	if (tl==tr){
		slot[k].erase(fp);
		bl[fp]=-1;
		if (fp+k-1>n) bl[fp+k-1-n]=-1;else bl[fp+k-1]=-1;
		if (slot[tl].size()==0) tree[p]=0;else tree[p]=k;
		return;
	}
	int m=(tl+tr)>>1;
	if (k<=m) del(p<<1,tl,m,k,fp);else del((p<<1)+1,m+1,tr,k,fp);
	tree[p]=max(tree[p<<1],tree[(p<<1)+1]);
}
int get(int p,int tl,int tr,int x){
	if (tl==tr){
		set<int>::iterator it=slot[tl].begin();
		int ret=(*it);
		slot[tl].erase(it);
		if (slot[tl].size()==0) tree[p]=0;else tree[p]=tl;
		return ret;
	}
	int ret=0;
	int m=(tl+tr)>>1;
	if (tree[p<<1]>=x) ret=get(p<<1,tl,m,x);else ret=get((p<<1)+1,m+1,tr,x);
	tree[p]=max(tree[p<<1],tree[(p<<1)+1]);
	return ret;
}
inline int prev(int p){
	return p==1?n:p-1;
}
inline int nxt(int p){
	return p==n?1:p+1;
}
int park(int x){
	if (tree[1]<x) return -1;
	int p=get(1,1,n,x);
	int len=bl[p];
	bl[p]=-1;
	int tp=(p+x<=n?p+x:p+x-n);
	int ep=(p+len-1<=n?p+len-1:p+len-1-n);
	bl[ep]=-1;
	if (len>x) ins(1,1,n,len-x,tp);
	return p;
}
void remove(int x){
	int p=pos[x];
	int pt=prev(p),nt=(p+tlen[x]-1<=n?p+tlen[x]-1:p+tlen[x]-1-n);
	int sp=p,slen=tlen[x];
	nt=nxt(nt);
	if (bl[pt]!=-1){
		int stp=pt-bl[pt]+1;
		if (stp<=0) stp+=n;
		sp=stp;
		slen+=bl[pt];
		del(1,1,n,bl[pt],stp);
	}
	if (bl[nt]!=-1){
		slen+=bl[nt];
		del(1,1,n,bl[nt],nt);
	}
	if (slen==n) ins(1,1,n,n,1);else
	ins(1,1,n,slen,sp);
}
void pr(int l,int r){
	if (l==r) printf("%d",l);else printf("%d-%d",l,r);
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	int ln=0;
	for (ln=0;ln<n && s[ln]=='.';++ln);
	init(1,1,n);
	memset(bl,-1,sizeof(bl));
	if (ln==n){
		ins(1,1,n,n,1);
	}else{
		for (int i=ln,j;i<n;i=j+1){
			while (i<n && s[i]=='X') ++i;
			if (i==n){
				ins(1,1,n,ln,1);
				break;
			}
			for (j=i;j<n-1 && s[j+1]=='.';j++);
			if (j==n-1){
				ins(1,1,n,j-i+1+ln,i+1);
			}else{
				ins(1,1,n,j-i+1,i+1);
			}
		}
	}
	for (int t=0;t<m;t++){
		char type[10];
		scanf("%s",type);
		if (type[0]=='P'){
			int len;
			scanf("%d",&len);
			tlen[t]=len;
			pos[t]=park(len);
			if (pos[t]==-1) puts("NO ROOM");else{
				if (pos[t]+len-1<=n) pr(pos[t],pos[t]+len-1);else{
					pr(1,len-(n-pos[t]+1));
					printf(",");
					pr(pos[t],n);
				}
				puts("");
			}
		}else{
			int p;
			scanf("%d",&p);
			remove(p-1);
		}
	}
	return 0;
}
