#include <stdio.h>
#include <string.h>
#define maxn 2010
int b[maxn],bn,p;
int a[maxn][maxn];
int n;
void VS(int r,int x,int y){
	a[x][y]=a[y][x]=r;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	if (n==1){
		printf("0\n0\n");
		return 0;
	}
	if (n%2==0) printf("%d\n",n-1);else printf("%d\n",n);
	for (i=0;i<n-1;i++) b[i]=i+2;
	bn=n-1;
	if (n%2==1){
		b[bn++]=0;
	}
	int m= n%2==0 ? n-1 : n;
	memset(a,0,sizeof(a));
	p=bn-1;
	for (i=1;i<=m;i++){
		VS(i,1,b[p]);
		int p1=(p+1)%bn,p2=(p-1+bn)%bn;
		for (j=2;j<=(n+1)>>1;j++){
			VS(i,b[p1],b[p2]);
			p1=(p1+1)%bn;
			p2=(p2-1+bn)%bn;
		}
		p=(p+1)%bn;
	}
	for (i=1;i<=n;i++){
		for (j=1;j<=n;j++) printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
