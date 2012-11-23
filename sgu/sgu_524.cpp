#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define maxn 410

using namespace std;

double x[maxn],y[maxn],z[maxn];
int n;
double Cal(double det){
	int i;
	for (i=0;i<n;i++) y[i]=x[i]-i*det;
	sort(y,y+n);
	z[0]=y[n/2];
	for (i=0;i<n-1;i++) z[i+1]=z[i]+det;
	double res=0;
	for (i=0;i<n;i++) res+=fabs(z[i]-x[i]);
	return res;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%lf",x+i);
	double l=0,r=10000,m1,m2,d1,d2;
	while (r-l>1e-8){
		m1=l+(r-l)/3.0;
		m2=(m1+r)/2.0;
		d1=Cal(m1);
		d2=Cal(m2);
		if (d1<d2) r=m2;else l=m1;
	}
	printf("%.4lf\n",Cal(l));
	for (i=0;i<n;i++) printf("%.7lf ",z[i]);printf("\n");
	return 0;
}
