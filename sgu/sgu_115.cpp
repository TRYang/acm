#include <stdio.h>
const int t[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int n,m;
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (n>t[m-1]) printf("Impossible\n");else{
		k=0;
		for (i=0;i<m-1;i++) k+=t[i];
		k+=n;
		printf("%d\n",(k-1)%7+1);
	}
	return 0;
}
