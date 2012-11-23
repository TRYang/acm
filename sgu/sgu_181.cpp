#include <stdio.h>
#include <string.h>
#define maxm 1010
int A,B,C,x0;
int n,m;
int tag[maxm],T;
int g[maxm];
int f(int x){return (A*((x*x)%m)+B*x+C)%m;}
int main(){
	int i,j,k;
	scanf("%d %d %d %d %d %d",&x0,&A,&B,&C,&m,&n);
	if (n==0){
		printf("%d\n",x0);
		return 0;
	}
	memset(tag,-1,sizeof(tag));
	for (i=1,k=f(x0);tag[k]==-1;k=f(k),i++){
		tag[k]=i;
		if (i==n){
			printf("%d\n",k);
			return 0;
		}
	}
	T=i-tag[k];
	for (g[0]=k,i=1;i<T;i++) g[i]=f(g[i-1]);
	n-=tag[k];
	printf("%d\n",g[n%T]);
	return 0;
}
