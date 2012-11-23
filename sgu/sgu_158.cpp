#include <stdio.h>
#include <string.h>
#include <math.h>
#define maxn 310
int p[maxn],d[maxn];
int l;
int n,m;
double ans,st,tmp,ts;

double cal(double s){
	double res=0;
	int i,j=0;
	for (i=0;i<n;i++){
		while (j<m-1 && fabs(s+d[j]-p[i])>fabs(s+d[j+1]-p[i])) j++;
		res+=fabs(s+d[j]-p[i]);
	}
	return res;
}

int main(){
	int i,j,k;
	scanf("%d",&l);
	for (scanf("%d",&n),i=0;i<n;i++) scanf("%d",p+i);
	scanf("%d",&m);
	for (i=1;i<m;i++) scanf("%d",d+i);
	d[0]=0;
	ans=cal(0);
	st=0;
	tmp=cal(l-d[m-1]);
	if (tmp>ans){
		ans=tmp;
		st=l-d[m-1];
	}
	for (i=0;i<n;i++)
		for (j=0;j<m-1;j++){
			ts=(double)p[i]-d[j]-(d[j+1]-d[j])/2.0;
			if (ts>-1e-8 && ts+d[m-1]<l+1e-8){
				tmp=cal(ts);
				if (tmp>ans){
					ans=tmp;
					st=ts;
				}
			}
		}
	printf("%.2lf %.2lf\n",st,ans);
	return 0;
}
