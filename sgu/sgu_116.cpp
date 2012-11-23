#include <stdio.h>
#include <string.h>
#define maxn 10010
#define maxm 203
int pr[1300],pn;
int spr[maxm],sn;
int f[maxn],g[maxn];
int n;

int check_pr(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (pn=0,i=2;i<=10000;i++)
		if (check_pr(i)) pr[++pn]=i;
	sn=0;
	for (i=2;i<=pn;i++)
		if (check_pr(i)) spr[++sn]=pr[i];
	for (i=1;i<=n;i++) f[i]=1000000;
	f[0]=0;
	for (k=1;k<=sn && spr[k]<=n;k++){
		for (i=spr[k];i<=n;i++)
			if (f[i-spr[k]]+1<f[i]){
				f[i]=f[i-spr[k]]+1;
				g[i]=i-spr[k];
			}
	}
	if (f[n]==1000000){
		printf("0\n");
		return 0;
	}
	printf("%d\n",f[n]);
	for (i=n;i!=0;i=g[i]) printf("%d ",i-g[i]);
	printf("\n");
	return 0;
}
