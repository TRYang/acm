#include <stdio.h>
double b,n,m;
int s,t;
int main(){
	int i,j,k;
	scanf("%d %d %lf",&s,&t,&b);
	m=(t-s)*(t-s)*3600.0;
	n=m-((t-s)*60.0-b)*((t-s)*60.0-b);
	printf("%.7lf\n",n/m);
	return 0;
}
