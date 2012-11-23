#include <stdio.h>
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	if (n%2==1){
		k=n;
		printf("%d ",k);
		for (i=1;i<=n-2;i++)
			for (j=1;j<=i;j++) printf("%d ",(i+2)*n-j+1);
		printf("\n");
		k+=2;
	}else{
		k=n;
		printf("%d ",k);
		for (i=1;i<=n-2;i++)
			for (j=1;j<=i;j++) printf("%d ",(i+2)*n-j+1);
		printf("\n");
		k++;
	}
	printf("%d ",k);
	for (i=0;i<n-1;i++) printf("%d ",(i+2)*n-i);
	printf("\n");
	k+=2;
	for (j=n;j>1;j--){
		printf("%d ",k);
		for (i=0;i<j;i++) printf("%d ",i*n+j-i);
		printf("\n");
		k+=2;
	}
	return 0;
}
