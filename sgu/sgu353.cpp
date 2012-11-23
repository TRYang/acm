#include <stdio.h>
#include <string.h>
int n,k1,k2,p1,p2,p3;
int main(){
	scanf("%d%d%d%d%d%d",&n,&k1,&k2,&p1,&p2,&p3);
	int ans=0;
	if (p1<=n){
		n-=p1;
		ans+=k1;
		if (n>0){
			int i=0;
			while (1){
				if (i<k2){
					n-=p2;
				}else{
					n-=p3;
				}
				i++;
				ans++;
				if (n<=0) break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
