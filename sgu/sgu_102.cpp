#include <stdio.h>
int n,ans;
int gcd(int x,int y){
	return y==0 ? x : gcd(y,x%y);
}
int main(){
	int i;
	scanf("%d",&n);
	for (ans=0,i=1;i<=n;i++)
		if (gcd(i,n)==1) ans++;
	printf("%d\n",ans);
	return 0;
}
