#include <stdio.h>
int f[9];
int n;
int cal(int x){
	int i,j,k=1;
	if (n==1) return 0;
	if (x==1) return 0;
	for (i=1;i<n-1;i++) k=(k*10+1)%x;
	k=(k*10+x)%x;
	return k;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=9;i++) f[i]=cal(i);
	for (k=0,i=1;i<9;i++)
		if (f[i]==f[i+1] && f[i]==0) k++;
	printf("%d\n",k);
	return 0;
}
