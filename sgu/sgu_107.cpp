#include <stdio.h>
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	if (n<9) printf("0\n");else
	if (n==9) printf("8\n");else{
		printf("72");
		for (n-=10;n>0;n--) printf("0");
		printf("\n");
	}
	return 0;
}
