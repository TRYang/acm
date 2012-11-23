#include <stdio.h>
#include <string.h>
#define maxn 1000010
int tag[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	n%=m;
	if (n==0){
		puts("0 0");
		return 0;
	}
	memset(tag,-1,sizeof(tag));
	tag[n]=0;
	for (int i=1;;i++){
		n=(n*10)%m;
		if (tag[n]>-1){
			printf("%d %d\n",tag[n],i-tag[n]);
			return 0;
		}else{
			tag[n]=i;
		}
		if (n==0){
			printf("%d 0\n",i);
			break;
		}
	}
	return 0;
}
