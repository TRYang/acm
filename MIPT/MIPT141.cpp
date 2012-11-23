#include <stdio.h>
#include <string.h>
#define maxn 1010
double f[maxn][maxn];
double p[maxn];
int n;
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%lf",p+i);
	for (int l=1;l<n;l++)
		for (int i=0;i+l<n;i++){
			int j=i+l;
			double dp=1.0-p[i]*p[j];
			f[i][j]=0;
			f[i][j]+=(1.0-p[i])*p[j]*(f[i+1][j]+1);
			f[i][j]+=p[i]*(1.0-p[j])*(f[i][j-1]+1);
			f[i][j]+=(1.0-p[i])*(1.0-p[j])*(f[i+1][j-1]+1);
			f[i][j]+=p[i]*p[j];
			f[i][j]/=dp;
		}
	printf("%.9lf\n",f[0][n-1]);
	return 0;
}