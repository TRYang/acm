#include <stdio.h>
#include <string.h>
#define maxn 300
#define maxm 90010
int st[maxn],aim[maxm],nxt[maxm],ln;
int match[maxn];
int level[maxn],prev[maxn];
int cross_edge[maxn][2];
int father[maxn];
int tag[maxn];
int q[maxn],qn;
int n;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int Find(int x){return father[x]= father[x]==x ? x : Find(father[x]);}
int LCA(int x,int y,int root){
	while (x!=y && tag[x]!=1 && tag[y]!=0){
		tag[x]=0;
		tag[y]=1;
		if (x!=root) x=Find(prev[x]);
		if (y!=root) y=Find(prev[y]);
	}
	if (tag[y]==0){
		int k;
		k=x;x=y;y=k;
	}
	for (int i=x;i!=y;i=Find(prev[i])) tag[i]=-1;
	tag[y]=-1;
	return x;
}
void com(int root,int x,int u,int v){
	while (x!=root){
		father[x]=root;
		if (level[x]==1){
			q[qn++]=x;
			cross_edge[x][0]=u;
			cross_edge[x][1]=v;
		}
		x=Find(prev[x]);
	}
}
void FindPath(int root,int x){
	if (x==root) return;
	if (level[x]==1){			//奇点,需要绕花
		int tx=cross_edge[x][0],ty=cross_edge[x][1];
		FindPath(match[x],tx);
		FindPath(root,ty);
		match[tx]=ty;
		match[ty]=tx;
	}else{						//偶点
		FindPath(root,prev[prev[x]]);
		int y=prev[x];
		int z=prev[y];
		match[y]=z;
		match[z]=y;
	}
}
int FindAlterRoad(int sp){
	for (int i=0;i<n;i++) father[i]=i;
	memset(level,-1,sizeof(level));
	memset(tag,-1,sizeof(tag));
	qn=1;
	q[0]=sp;
	level[sp]=0;
	for (int p=0;p<qn;p++){
		int x=q[p];
		for (int i=st[x];i!=-1;i=nxt[i]){
			int y=aim[i];
			if (Find(y)==Find(x)) continue;
			if (match[y]==y) continue;
			if (level[y]==-1){
				if (match[y]==-1){		//找到增广路
					FindPath(sp,x);
					match[x]=y;
					match[y]=x;
					return 1;
				}else{					//继续增广
					int z=match[y];
					prev[z]=y;
					prev[y]=x;
					level[y]=1;
					level[z]=0;
					q[qn++]=z;
				}
			}else{						//形成花,要缩花
				if (level[Find(y)]==0){
					int tx=Find(x),ty=Find(y);
					int root=LCA(tx,ty,sp);
					com(root,tx,x,y);
					com(root,ty,y,x);
				}
			}
		}
	}
	return 0;
}
int MaximumMatch(){
	int ret=0;
	memset(match,-1,sizeof(match));
	for (int i=0;i<n;i++)
		if (match[i]==-1)
			if (FindAlterRoad(i)) ret++;else match[i]=i;
	return ret;
}
