#include <stdio.h>
#include <string.h>
#define maxn 110
int a[maxn];
int n,tag;
int main(){
	int i,j,k;
	scanf("%d",&n);
	tag=1;
	memset(a,-1,sizeof(a));
	for (i=1;i<=n;i++){
		scanf("%d",&k);
		if (!k) tag=0;
		while (k){
			if (a[i]==-1 && a[k]==-1){
				a[i]=0;
				a[k]=1;
			}else
			if (a[i]==-1){
				a[i]=a[k]^1;
			}else
			if (a[k]==-1){
				a[k]=a[i]^1;
			}
			scanf("%d",&k);
		}
	}
	if (!tag) printf("0\n");else{
		k=0;
		for (i=1;i<=n;i++)
			if (!a[i]) k++;
		printf("%d\n",k);
		for (i=1;i<=n;i++)
			if (!a[i]) printf("%d ",i);
		printf("\n");
	}
	return 0;
}
