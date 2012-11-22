#include <stdio.h>
#include <string.h>
#include <math.h>
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	printf("%.9lf\n",n-n*pow((n-1)/1.0/n,m));
	return 0;
}
