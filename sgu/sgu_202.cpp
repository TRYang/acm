#include <stdio.h>
#include <string.h>
#define maxn 66

typedef long long lint;

lint g[maxn][maxn];
int a[maxn][maxn],an[maxn];
int n,m;

lint H(int n){
	int i;
	if (n>60) return 1000000000;
	lint res=1;
	for (i=0;i<n;i++) res=res+res;
	return res-1;
}

lint min(lint x,lint y){return x<y ? x : y;}

lint f(int x,int y){
	if (g[x][y]==-1){
		if (x==1) g[x][y]=1;else
		if (y==3) g[x][y]=H(x);else{
			g[x][y]=1000000000;
			for (int i=1;i<x;i++) g[x][y]=min(g[x][y],(f(i,y)<<1)+f(x-i,y-1));
		}
	}
	return g[x][y];
}

void pr(int Index,int x,int y,int st,int en){
	int i,j;
	if (x==1){
		if (an[en]==0){
			an[st]--;
			printf("move %d from %d to %d\n",Index,st,en);
			a[en][++an[en]]=Index;
		}else{
			an[st]--;
			printf("move %d from %d to %d atop %d\n",Index,st,en,a[en][an[en]]);
			a[en][++an[en]]=Index;
		}
	}else
	if (y==3){
		for (i=1;i<=m;i++)
			if (i!=st && i!=en && (an[i]==0 || a[i][an[i]]>Index+x-1)) break;
		pr(Index,x-1,y,st,i);
		pr(Index+x-1,1,y,st,en);
		pr(Index,x-1,y,i,en);
	}else{
		for (i=1;i<x;i++)
			if ((g[i][y]<<1)+g[x-i][y-1]==g[x][y]){
				for (j=1;j<=m;j++)
					if (j!=st && j!=en && (an[j]==0 || a[j][an[j]]>Index+i-1)) break;
				pr(Index,i,y,st,j);
				pr(Index+i,x-i,y-1,st,en);
				pr(Index,i,y,j,en);
				return;
			}
	}
}

int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(g,-1,sizeof(g));
	printf("%I64d\n",f(n,m));
	memset(an,0,sizeof(an));
	an[1]=n;
	for (i=1;i<=n;i++) a[1][i]=n-i+1;
	pr(1,n,m,1,m);
	return 0;
}
