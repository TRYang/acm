#include <stdio.h>
#define maxn 10010
double x[maxn],y[maxn];
double ans[2];
int n;
double abs(double x){return x>0.0?x:-x;}
int find(int p,double *r){
	double tot=0;
	int i;
	for (i=0;i<n;i++)
		if ((i%2)==0) tot+=r[i];else tot-=r[i];
	if (n%2==1){
		ans[p]=tot;
		return 1;
	}else{
		if (abs(tot)<1e-5){
			ans[p]=0;
			for (i=0;i<n;i++)
				if (r[i]>ans[p]) ans[p]=r[i]+1;
			return 1;
		}else return 0;
	}
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%lf %lf",x+i,y+i);
	if (find(0,x) && find(1,y)){
		printf("YES\n");
		for (i=0;i<n;i++){
			printf("%.3lf %.3lf\n",ans[0],ans[1]);
			ans[0]=2*x[i]-ans[0];
			ans[1]=2*y[i]-ans[1];
		}
	}else printf("NO\n");
	return 0;
}
