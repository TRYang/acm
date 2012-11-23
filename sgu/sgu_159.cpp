#include <stdio.h>
#define maxn 2010
int a[maxn];
int ans[100][maxn];
int n,m,tot;

void dfs(int p,int sum){
	if (p==n){
		if (p>1 && a[p-1]==0) return;
		int i;
		for (i=0;i<p;i++) ans[tot][i]=a[i];
		tot++;
		return;
	}
	for (int i=0;i<m;i++){
		a[p]=i;
		int j,s=0;
		for (j=0;j<=p;j++) s+=a[j]*a[p-j];
		if ((s+sum)%m==i) dfs(p+1,(s+sum)/m);
	}
}

int main(){
	int i,j,k;
	scanf("%d %d",&m,&n);
	tot=0;
	dfs(0,0);
	printf("%d\n",tot);
	for (i=0;i<tot;i++){
		for (j=n-1;j>=0;j--)
			if (ans[i][j]<10) printf("%d",ans[i][j]);else printf("%c",'A'+ans[i][j]-10);
		printf("\n");
	}
	return 0;
}
