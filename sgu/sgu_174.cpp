#include <stdio.h>
#include <algorithm>
#include <string.h>
#define hashsize 1797001
#define maxn 200010

using namespace std;

int st[hashsize],vx[maxn<<1],vy[maxn<<1],link[maxn<<1],ln;
int f[maxn<<1];
int n;
int g(int x,int y){
	int v=(x+y)%hashsize;
	for (int i=st[v];i!=-1;i=link[i])
		if (vx[i]==x && vy[i]==y) return i;
	vx[ln]=x;
	vy[ln]=y;
	link[ln]=st[v];
	f[ln]=ln;
	st[v]=ln++;
	return ln-1;
}
int find(int x){
	int next,p,fx;
	for (p=x;f[p]!=p;p=f[p]);
	fx=p;
	for (p=x;p!=fx;p=next){
		next=f[p];
		f[p]=fx;
	}
	return fx;
}
int main(){
	int i,j,k;
	int x1,y1,x2,y2;
	scanf("%d",&n);
	ln=0;
	memset(st,-1,sizeof(st));
	for (i=0;i<n;i++){
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		j=find(g(x1,y1));
		k=find(g(x2,y2));
		if (j==k){
			printf("%d\n",i+1);
			return 0;
		}else f[j]=k;
	}
	printf("0\n");
	return 0;
}
