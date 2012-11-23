#include <stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	if (n==1){
		printf("1 0\n");
	}else
	if (n==2){
		printf("2 1\n1 2\n");
	}else
	if (n==3){
		printf("3 3\n");
		printf("1 2\n");
		printf("2 3\n");
		printf("3 1\n");
	}else{
		printf("%d %d\n",n,(n-2)*2);
		for (int i=3;i<=n;i++) printf("1 %d\n2 %d\n",i,i);
	}
	return 0;
}
