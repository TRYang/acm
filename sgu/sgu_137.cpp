#include <stdio.h>
#define maxn 1010
int a[maxn];
int n,K,m;
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	K=m/n;
	m=m%n;
	for (k=1;(m*k+1)%n;k++);
	i=0;
	do{
		i=(i+k)%n;
		a[i]=1;
	}while (i!=n-1);
	for (i=0;i<n;i++) printf("%d ",a[i]+K);printf("\n");
	return 0;
}
