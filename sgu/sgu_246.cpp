#include <stdio.h>
int n;
int main(){
	scanf("%d",&n);
	n= n%3==0 ? n/2 : n/2+1;
	printf("%d\n",n);
	return 0;
}
