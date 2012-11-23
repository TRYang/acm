#include <stdio.h>
#include <math.h>
#define eps 1e-6
double b,c,m;
double x,y;
int main(){
	int i,j,k;
	scanf("%lf %lf %lf",&c,&b,&m);
	if (2*m<fabs(b-c) || 2*m>b+c) printf("Mission impossible\n");else{
		x=(4*m*m-b*b-c*c)/2/b;
		y= c*c-x*x>=0 ? sqrt(c*c-x*x) : 0;
		printf("0.00000 0.00000\n");
		printf("%.5lf %.5lf\n",x,y);
		printf("%.5lf 0.00000\n",b);
	}
	return 0;
}
