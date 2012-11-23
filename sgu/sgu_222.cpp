#include <stdio.h>
#include <string.h>
int f[11][11][11];
int n,m;

int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (m>n){
		printf("0\n");
	}else{
		memset(f,0,sizeof(f));
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++) f[i][j][0]=1;
		for (k=1;k<=m;k++)
			for (i=1;i<=n;i++)
				for (j=1;j<=n;j++) f[i][j][k]=j*f[i-1][j-1][k-1]+f[i-1][j][k];
		printf("%d\n",f[n][n][m]);
	}
	return 0;
}
