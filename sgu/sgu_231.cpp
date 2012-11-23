#include <stdio.h>
#define maxn 1000010
int tag[maxn];
int n;
int ans;
int main(){
	int i,j,k;
	scanf("%d",&n);
	ans=0;
	for (i=2;i<=n;i++)
		if (!tag[i]){
			for (k=i+i;k<=n;k+=i) tag[k]=1;
			if (i>4 && !tag[i-2]) ans++;
		}
	printf("%d\n",ans);
	for (i=2;i+2<=n;i++)
		if (!tag[i] && !tag[i+2]) printf("2 %d\n",i);
	return 0;
}
