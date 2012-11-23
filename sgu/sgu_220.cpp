#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 15

using namespace std;

int a[maxn],an;
int n,m;
long long f[maxn][maxn<<1],G[2][maxn<<1];
long long ans;

bool cmp(int x,int y){
	return x>y;
}
void work(int x){
	int i,j,k;
	an=0;
	for (i=0;i<n;i++)
		if (i%2==x) a[an++]=i+1;
	for (i=1;i<n;i++)
		if ((i+n-1)%2==x) a[an++]=n-i;
	sort(a,a+an,cmp);
	a[an]=0;
	memset(f,0,sizeof(f));
	f[an][0]=1;
	for (i=an-1;i>=0;i--)
		for (j=0;j<=m && j<=a[i];j++){
			f[i][j]=f[i+1][j];
			if (j>0) f[i][j]+=(a[i]-j+1)*f[i+1][j-1];
		}
	for (i=0;i<=m;i++) G[x][i]=f[0][i];
}

int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (m>2*n-2 && n>1) printf("0\n");else{
		work(0);
		work(1);
		ans=0;
		for (i=0;i<=m;i++) ans+=G[0][i]*G[1][m-i];
		printf("%I64d\n",ans);
	}
	return 0;
}
