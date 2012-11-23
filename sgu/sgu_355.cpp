#include <stdio.h>
#include <string.h>
#define maxn 10010
int pr[maxn],pn;
int a[maxn];
int n;
int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}
int main(){
	int i,j,k;
	pn=0;
	for (i=2;i<=100000;i++)
		if (check(i)) pr[pn++]=i;
	scanf("%d",&n);
	int ans=0;
	for (i=1;i<=n;i++){
		k=1;
		int x=i;
		for (j=0;x>1 && j<pn && pr[j]*pr[j]<=x;j++)
			while (x%pr[j]==0){
				x/=pr[j];
				k++;
			}
		if (x>1) k++;
		a[i]=k;
		if (k>ans) ans=k;
	}
	printf("%d\n",ans);
	for (i=1;i<n;i++) printf("%d ",a[i]);
	printf("%d\n",a[n]);
	return 0;
}
