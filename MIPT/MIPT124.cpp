#include <stdio.h>
#include <string.h>
int n;
int main(){
	scanf("%d",&n);
	int N=n*n;
	for (int i=0;i<N;i++){
		int st=i/n,p=i%n;
		for (int j=0;j<N;j++){
			int k=((j/n)*n+st+p*n+(j%n))%N;
			printf("%d",k+1);
			if (j<N-1) printf(" ");else puts("");
		}
	}
	return 0;
}