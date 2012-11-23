#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 55
#define maxm 5010
using namespace std;
int f[maxn][maxm],g[maxn][maxm];
int tag[maxn];
int h[maxn];
int n;
int ans,ansp,ansc;
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",h+i);
	int per=0;
	for (int i=0;i<n;i++){
		per+=2+2*h[i];
		if (i<n-1) per-=2*min(h[i],h[i+1]);
	}
	int m=0;
	memset(f,-1,sizeof(f));
	ans=-1;
	for (int i=0;i<n;i++){
		int tm=m;
		m=max(m,2*h[i]+2);
		f[i][2*h[i]+2]=0;
		for (int j=0;j<i;j++) f[i][2*h[i]+2]+=h[j];
		g[i][2*h[i]+2]=-1;
		for (int j=i-1,s=0;j>=0;s+=h[j--])
			for (int k=1;k<=tm;k++)
				if (f[j][k]>-1){
					int t=k+h[i]*2+2-2*min(h[i],h[j]);
					if (f[j][k]+s>f[i][t]){
						f[i][t]=f[j][k]+s;
						g[i][t]=j;
					}
					m=max(m,t);
				}
		int ts=0;
		for (int j=i+1;j<n;j++) ts+=h[j];
		for (int j=1;j<=m;j++)
			if (j>=(per+1)/2 && f[i][j]+ts>ans){
				ans=f[i][j]+ts;
				ansp=i;
				ansc=j;
			}
	}
	printf("%d\n",ans);
	int tot=n;
	while (ansp!=-1){
		tag[ansp]=1;
		--tot;
		int tc=ansc;
		int tp=g[ansp][ansc];
		if (tp==-1) break;
		tc+=2*min(h[tp],h[ansp]);
		tc-=2+2*h[ansp];
		ansp=tp;
		ansc=tc;
	}
	printf("%d\n",tot);
	for (int i=0;i<n;i++)
		if (!tag[i]) printf("%d ",i+1);
	puts("");
	return 0;
}
