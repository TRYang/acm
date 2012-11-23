#include <stdio.h>
#define maxn 100010
int a[maxn],b[maxn];
int n;

int max(int x,int y){
	return x>y?x:y;
}

int main(){
	int i,j,k;
	a[0]=0;a[1]=1;
	b[1]=1;
	for (i=2;i<100000;i++)
		if ((i&1)==1){
			a[i]=a[i>>1]+a[(i>>1)+1];
			b[i]=max(a[i],b[i-1]);
		}else{
			a[i]=a[i>>1];
			b[i]=max(a[i],b[i-1]);
		}
	while (scanf("%d",&n),n){
		printf("%d\n",b[n]);
	}
	return 0;
}
