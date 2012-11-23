#include <stdio.h>
int n,m;
int f(long long N,int x){
	if (N==1) return 1;
	long long mid=N>>1;
	if (x<=mid){
		return N-mid+f(mid,mid-x+1);
	}else{
		return f(N-mid,N-x+1);
	}
}
int main(){
	scanf("%d %d",&n,&m);
	printf("%d\n",f(n,m));
	return 0;
}
