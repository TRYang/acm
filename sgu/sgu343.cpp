#include <stdio.h>
#include <string.h>
#define maxn 11
#define maxt 10010
double price[maxt][maxn];
int a[maxn];
double v[maxn];
int n,m;
int main(){
	scanf("%d%d",&m,&n);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	for (int t=0;t<=m;t++){
		for (int i=0;i<n;i++) scanf("%lf",&price[t][i]);
	}
	return 0;
}
