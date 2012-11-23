#include <stdio.h>
#include <string.h>
int main(){
	int n;
	scanf("%d",&n);
	int ans=0,deg=1,dis=1;
	if (n==0) puts("0.000");else
	if (n==1) puts("1.000");else{
		ans=5;
		deg=2;
		dis=2;
		for (int i=3;i<=n;i++){
			if (deg<dis) ++deg;else ++dis;
			ans+=deg*dis;
		}
		printf("%d.000\n",ans);
	}
	return 0;
}
