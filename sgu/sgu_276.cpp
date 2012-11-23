#include <stdio.h>
#include <string.h>
int main(){
	int i,j,k;
	scanf("%d %d",&i,&j);
	if (i<j){
		k=j-i;
		if (k<300) printf("1\n");else
		if (k<900) printf("2\n");else
		if (k<1800) printf("3\n");else printf("4\n");
	}else printf("0\n");
	return 0;
}
