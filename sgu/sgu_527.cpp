#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 30

using namespace std;

char s[maxn];
int a[maxn][maxn];
int col[maxn],row[maxn],p[maxn],d[maxn];
int l=0,r=0,mid;
int m,n;
int ans;
bool cmp(int x,int y){
	return col[x]>col[y];
}
int f(int x){
	int res=0;
	for (int i=x;i>0;i-=(i&(i^(i-1)))) res++;
	return res;
}
int dfs(int dep,int s,int tot,int st){
	int i,j;
	if (dep==m){
		if (tot==mid) return f(st)<=mid;
		return 0;
	}
	if (tot+m-dep<mid) return 0;
	if (tot>mid) return 0;
	if (f(st)>mid) return 0;
	if (dfs(dep+1,s|(1<<p[dep]),tot+1,st)) return 1;
	if (col[p[dep]]<=mid && dfs(dep+1,s,tot,st|d[p[dep]])) return 1;
	return 0;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(col,0,sizeof(col));
	memset(row,0,sizeof(row));
	memset(d,0,sizeof(d));
	for (i=0;i<n;i++){
		scanf("%s",s);
		for (j=0;j<m;j++)
			if (s[j]=='.') a[i][j]=0;else{
				a[i][j]=1;
				col[j]++;
				d[j]|=1<<i;
			}
	}
	for (i=0;i<m;i++) p[i]=i;
	sort(p,p+m,cmp);
	k=n;
	if (m<k) k=m;
	for (mid=0;mid<=k;mid++)
		if (dfs(0,0,0,0)){
			printf("%d\n",mid);
			break;
		}
	return 0;
}
