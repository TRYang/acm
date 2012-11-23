#include <stdio.h>
#include <string.h>
#define maxn 11
#define maxm 110
int f[maxm][maxn][maxn][maxn][maxn];
int a[maxn],b[maxn];
int n,m;
int ans;

int min(int x,int y){return (x>-1 && x<y)?x:y;}

int main(){
	int i,j,k,l,p,t,s,st;
	scanf("%d %d",&m,&n);
	for (i=1;i<=n;i++) scanf("%d %d",a+i,b+i);
	a[0]=b[0]=0;
	memset(f,-1,sizeof(f));
	ans=m*m;
	f[0][0][0][0][0]=0;
	for (p=0;p<m;p++){
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				for (k=0;k<=n;k++)
					for (l=0;l<=n;l++)
						if (f[p][i][j][k][l]>-1){
							f[p][j][k][l][0]=min(f[p][j][k][l][0],f[p][i][j][k][l]+1);
							f[p][k][l][0][0]=min(f[p][k][l][0][0],f[p][i][j][k][l]+2);
							f[p][l][0][0][0]=min(f[p][l][0][0][0],f[p][i][j][k][l]+3);
							f[p][0][0][0][0]=min(f[p][0][0][0][0],f[p][i][j][k][l]+4);
						}
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				for (k=0;k<=n;k++)
					for (l=0;l<=n;l++)
						if (f[p][i][j][k][l]>-1){
							s=(1<<(n+1))-1;
							if (b[i]>3) s^=1<<i;
							if (b[j]>2) s^=1<<j;
							if (b[k]>1) s^=1<<k;
							if (b[l]>0) s^=1<<l;
							for (t=1;t<=n;t++)
								if ((s&(1<<t))>0){
									st=p+a[t]>m?m:p+a[t];
									f[st][j][k][l][t]=min(f[st][j][k][l][t],f[p][i][j][k][l]+1);
									if (st==m) ans=min(ans,f[st][j][k][l][t]);
								}
						}
	}
	printf("%d\n",ans);
	return 0;
}
