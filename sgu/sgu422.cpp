#include <stdio.h>
#include <string.h>
#define maxn 3010
double p[maxn],f[maxn];
double t;
int n;
int main(){
	scanf("%n%lf",&n,&t);
	for (int i=0;i<n;i++) scanf("%lf",p+i);
	for (int i=n-1;i>=0;i--){
		f[i]=10000;
		for (int j=1;j<=n-i;j++){
			double tmp=j+t,v=1;
			for (int k=0;k<j;k++)
		}
	}
	return 0;
}
