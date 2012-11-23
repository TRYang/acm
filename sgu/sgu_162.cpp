#include <stdio.h>
#include <math.h>
double a,b,c,d,e,f;
double ans;
double vol(){
	double m=b*b+c*c-f*f;
	double n=a*a+c*c-e*e;
	double p=a*a+b*b-d*d;
	return sqrt(a*a*b*b*c*c-(a*a*m*m+b*b*n*n+c*c*p*p)/4+m*n*p/4)/6;
}
int main(){
	scanf("%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f);
	ans=vol();
	printf("%.4lf\n",ans);
	return 0;
}
