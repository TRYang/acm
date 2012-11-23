#include <stdio.h>
#include <string.h>
#define maxn 55
typedef long long LL;
LL a[maxn];
int n,x;
int main(){
	scanf("%d%d",&n,&x);
	--x;
	for (int i=0;i<n;i++){
		int k;
		for (scanf("%d",&k);k;k--){
			int p;
			scanf("%d",&p);
			--p;
			a[i]|=(1ll<<p);
		}
	}
	LL ans=0;
	for (int i=0;i<n;i++)
		if (i!=x && ((a[x]>>i)&1)>0) ans|=a[i];
	if (ans) ans^=(1ll<<x);
	for (int i=0;i<n;i++)
		if (i!=x && ((a[x]>>i)&1)>0 && ((ans>>i)&1)>0) ans^=(1ll<<i);
	int tot=0;
	for (int i=0;i<n;i++)
		if ((ans>>i)&1) ++tot;
	printf("%d\n",tot);
	for (int i=0;i<n;i++)
		if ((ans>>i)&1) printf("%d ",i+1);
	if (tot) puts("");
	return 0;
}