#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#define maxn 410

using namespace std;

int a[maxn],p[maxn];
int st[maxn],aim[maxn*maxn],link[maxn*maxn],ln;
int from[maxn],tag[maxn];
int c[maxn];
int n;

void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}

bool cmp(int x,int y){
	return a[x]>a[y];
}

int dfs(int x){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=st[x];i!=-1;i=link[i])
		if (from[aim[i]]==-1 || dfs(from[aim[i]])){
			from[aim[i]]=x;
			return 1;
		}
	return 0;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	ln=0;
	memset(st,-1,sizeof(st));
	for (i=0;i<n;i++){
		for (scanf("%d",&k);k>0;k--){
			scanf("%d",&j);
			in_edge(i,j);
		}
	}
	for (i=0;i<n;i++) p[i]=i;
	sort(p,p+n,cmp);
	memset(from,-1,sizeof(from));
	for (i=0;i<n;i++){
		memset(tag,0,sizeof(tag));
		dfs(p[i]);
	}
	memset(c,0,sizeof(c));
	for (i=1;i<=n;i++)
		if (from[i]>-1) c[from[i]]=i;
	for (i=0;i<n;i++) printf("%d ",c[i]);
	printf("\n");
	return 0;
}
