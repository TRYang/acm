#include <stdio.h>
int a0,b0,c0;
int a,b,c;
int check(int x){
	return a0/a>=x && b0/b>=x && c0/c>=x;
}
int main(){
	scanf("%d %d %d",&a0,&b0,&c0);
	scanf("%d %d %d",&a,&b,&c);
	int l=0,r=10000,mid;
	while (l<=r){
		mid=(l+r)>>1;
		if (check(mid)) l=mid+1;else r=mid-1;
	}
	printf("%d\n",l-1);
	return 0;
}
