#include <stdio.h>
#include <string.h>
#define maxn 10
int g[1<<9][1<<9];
long long f[10][1<<9];
int n,m;
int ns;
void dfs(int s,int st,int p){
	if (p==m){
		if (s==(1<<m)-1){
			g[ns][st]++;
		}
		return;
	}
	if (p<m-1 && (st&(1<<(p+1)))==0 && (st&(1<<p))==0) dfs(s,st|(3<<p),p+1);
	if ((s&(1<<p))>0){
		dfs(s,st,p+1);
		return;
	}
	if ((st&(1<<p))==0){
		dfs(s|(1<<p),st|(1<<p),p+1);
		if (p>0 && (st&(1<<(p-1)))==0) dfs(s|(1<<p),st|(3<<(p-1)),p+1);
		if (p<m-1 && (st&(1<<(p+1)))==0) dfs(s|(1<<p),st|(3<<p),p+1);
		if (p<m-1 && (s&(1<<(p+1)))==0) dfs(s|(3<<p),st|(1<<p),p+1);
	}
	if (p<m-1 && (s&(1<<(p+1)))==0 && (st&(1<<(p+1)))==0) dfs(s|(3<<p),st|(1<<(p+1)),p+2);
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(g,0,sizeof(g));
	for (ns=0;ns<1<<m;ns++) dfs(ns,0,0);
	memset(f,0,sizeof(f));
	f[0][(1<<m)-1]=1;
	for (i=1;i<=n;i++){
		for (j=0;j<1<<m;j++)
			if (f[i-1][j]>0)
				for (k=0;k<1<<m;k++) f[i][k]+=g[j][k]*f[i-1][j];
	}
	printf("%I64d\n",f[n][(1<<m)-1]);
	return 0;
}
