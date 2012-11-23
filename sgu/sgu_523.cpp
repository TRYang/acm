#include <stdio.h>
#include <string.h>
#define maxn 110
int tag[maxn];
int a[maxn];
int n,m;
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(tag,-1,sizeof(tag));
	for (i=0;i<n;i++){
		scanf("%d",a+i);
		tag[a[i]]=i;
	}
	int u=m,d=m;
	for (i=0;i<n;i++)
		if (a[i]>u || a[i]<d){
			if (a[i]>u){
				for (j=u+1;j<=a[i];j++)
					if (tag[j]>-1){
						printf("%d ",j);
						tag[j]=-1;
					}
				u=a[i];
			}else{
				for (j=d-1;j>=a[i];j--)
					if (tag[j]>-1){
						printf("%d ",j);
						tag[j]=-1;
					}
				d=a[i];
			}
		}
	printf("\n");
	return 0;
}
