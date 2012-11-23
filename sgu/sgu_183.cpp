#include <stdio.h>
#define maxn 10010
#define maxm 110
int f[maxm][maxm];
int a[maxn];
int n,m;
int ans;
int min(int x,int y){return x<y?x:y;}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",a+i);
	for (i=0;i<m;i++)
		for (j=1;j<m;j++) f[i][j]=300000000;
	int p=0,t;
	ans=300000000;
	for (i=n-1;i>0;i--){
		if (i+m>n){
			for (j=1;j<m;j++)
				if (i+j<=n) f[p][j]=a[i+j];
		}
		for (j=1;j<m;j++){
			if (f[p][j]<300000000) f[p][j]+=a[i];
			if (i+j<=m) ans=min(ans,f[p][j]);
		}
		k=300000000;
		for (j=i-m+1;j<i;j++)
			if (j>0){
				if (j+m<=n) k=min(k,f[p][j+m-i]);
				t=(p+i-j)%m;
				f[t][i-j]=min(f[t][i-j],k);
			}
		for (j=1;j<m;j++) f[p][j]=300000000;
		p=(p+1)%m;
	}
	printf("%d\n",ans);
	return 0;
}
