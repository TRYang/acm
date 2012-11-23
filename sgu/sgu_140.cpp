#include <stdio.h>
#include <string.h>
#define maxn 100
#define maxm 10000
int x[maxn],b[maxn];
int a[maxm],an,p,f[maxm],g[maxm];
int n,m,q;
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&q,&m);
	for (i=0;i<n;i++) scanf("%d",b+i);
	memset(f,-1,sizeof(f));
	an=1;a[0]=0;f[0]=0;
	for (p=0;p<an;p++)
		for (i=0;i<n;i++){
			k=(a[p]+b[i])%q;
			if (f[k]==-1){
				f[k]=i;
				g[k]=a[p];
				a[an++]=k;
			}
		}
	if (f[m]>-1){
		printf("YES\n");
		memset(x,0,sizeof(x));
		for (i=m;i>0;i=g[i]) x[f[i]]++;
		for (i=0;i<n;i++) printf("%d ",x[i]);
		printf("\n");
	}else printf("NO\n");
	return 0;
}
