#include <stdio.h>
#include <string.h>
#define maxn 15
#define mod 2007
struct matrix{
	int v[maxn][maxn];
	void pr(int n){
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++) printf("%d ",v[i][j]);
			puts("");
		}
	}
} A,B;
int f[100][100];
int n,m;
matrix Mult(matrix a,matrix b){
	matrix c;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++){
			c.v[i][j]=0;
			for (int k=1;k<=m;k++){
				c.v[i][j]+=a.v[i][k]*b.v[k][j];
				c.v[i][j]%=mod;
			}
		}
	return c;
}
matrix Mul(matrix A,int x){
	matrix ret;
	for (int i=1;i<=m;i++)
		for (int j=1;j<=m;j++) ret.v[i][j]=(i==j);
	while (x){
		if (x&1) ret=Mult(ret,A);
		A=Mult(A,A);
		x>>=1;
	}
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	if (n<100){
		memset(f,0,sizeof(f));
		f[1][1]=1;
		for (int i=2;i<=n;i++)
			for (int j=1;j<=m;j++){
				f[i][j]=f[i-1][j-1]+j*f[i-1][j];
				f[i][j]%=mod;
			}
		printf("%d\n",f[n][m]);
	}else{
		memset(A.v,0,sizeof(A.v));
		for (int i=1;i<=m;i++){
			A.v[i][i-1]=1;
			A.v[i][i]=i;
		}
		B=Mul(A,n-1);
		printf("%d\n",B.v[m][1]);
	}
	return 0;
}
