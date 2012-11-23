#include <stdio.h>
#include <string.h>
#include <math.h>
#define maxn 55
#define eps 1e-8
double w[maxn],v[maxn];
double u,t;
double least[maxn],a[maxn];
int n;
int sign(double x){
	return x<-eps?-1:x>eps;
}
double sqr(double x){
	return x*x;
}
double calc(int p,double t){
	return v[p]*t+sqrt(sqr(u*t)-sqr(w[p]));
}
int Swap(int x,int y){
	double lower=least[x],upper=a[x]+a[y]-least[y];
	double now=a[x];
	double value=calc(x,a[x])+calc(y,a[y]);
	int ret=0;
	double tp,tmp,tv;
	for (double step=upper-lower,cp=0;step>1e-6 && cp<30;step/=2,cp++){
		tp=now;
		for (int d=-1;d<=1;d+=2){
			tmp=tp+d*step;
			if (sign(tmp-lower)<0) tmp=lower;
			if (sign(tmp-upper)>0) tmp=upper;
			tv=calc(x,tmp)+calc(y,a[x]+a[y]-tmp);
			if (sign(tv-value)>0){
				value=tv;
				now=tmp;
				ret=1;
			}
		}
	}
	a[y]=a[x]+a[y]-now;
	a[x]=now;
	return ret;
}
int main(){
	scanf("%d%lf%lf",&n,&u,&t);
	for (int i=0;i<n;i++) scanf("%lf%lf",w+i,v+i);
	for (int i=0;i<n;i++) least[i]=w[i]/u;
	double tmp=0;
	for (int i=0;i<n;i++) tmp+=least[i];
	if (sign(tmp-t)>0){
		puts("-1");
		return 0;
	}
	for (int i=0;i<n;i++) a[i]=least[i]+(t-tmp)/n;
	while (1){
		int flag=0;
		for (int i=0;i<n;i++)
			for (int j=i+1;j<n;j++)
				if (i!=j && Swap(i,j)) flag=1;
		if (!flag) break;
	}
	double tot=0;
	for (int i=0;i<n;i++) tot+=calc(i,a[i]);
	double tw=0;
	for (int i=0;i<n;i++) tw+=w[i];
	double ans=hypot(tw,tot);
	printf("%.8lf\n",ans);
	for (int i=0;i<n;i++) printf("%.8lf ",a[i]);
	puts("");
	return 0;
}
