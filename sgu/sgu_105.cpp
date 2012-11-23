#include <stdio.h>
int n,ans;
int main(){
	scanf("%d",&n);
	if (n%3==2) printf("%d\n",2*(n/3)+1);else printf("%d\n",2*(n/3));
	return 0;
}
