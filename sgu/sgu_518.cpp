#include <stdio.h>
#include <string.h>
#define maxn 210
int l[maxn][maxn];
int m,r[maxn];
int f[maxn][maxn];
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++) scanf("%d",&l[i][j]);
	for (scanf("%d",&m),i=0;i<m;i++) scanf("%d",r+i);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for (k=0;k<m;k++){
		for (i=0;i<n;i++)
			if (f[i][k])
				for (j=0;j<n;j++)
					if (l[i][j] && l[i][j]==r[k]) f[j][k+1]=1;
	}
	for (k=0,i=0;i<n;i++)
		if (f[i][m]) k++;
	printf("%d\n",k);
	for (i=0;i<n;i++)
		if (f[i][m]) printf("%d ",i+1);
	printf("\n");
	return 0;
}
