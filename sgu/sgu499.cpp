#include <stdio.h>
#include <string.h>
#define maxn 1000010
int tag[maxn];
int n;
int check(int x){
	int tot=0;
	for (int i=x;i<=1000000 && tot<2;i+=x)
		tot+=tag[i];
	return tot>=2;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int k;
		scanf("%d",&k);
		tag[k]++;
	}
	int ans=1;
	for (int i=1000000;i>1;i--)
		if (check(i)){
			ans=i;
			break;
		}
	printf("%d\n",ans);
	return 0;
}
