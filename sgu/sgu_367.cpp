#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 10010
int st[maxn],aim[maxm],nxt[maxm],ln;
int tag[maxn];
int deg[maxn];
int t[maxn];
int a[maxn],an;
int ans,tot;
int n,m;
int T;
void in_edge(int x,int y){
	deg[y]++;
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int main(){
	scanf("%d%d",&n,&T);
	for (int i=1;i<=n;i++) scanf("%d",t+i);
	memset(st,-1,sizeof(st));
	ln=0;
	scanf("%d",&m);
	for (int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		in_edge(u,v);
	}
	memset(tag,0,sizeof(tag));
	an=0;
	tot=ans=0;
	while (1){
		int p=-1;
		for (int i=1;i<=n;i++)
			if (!tag[i] && deg[i]==0)
				if (p==-1 || t[i]<t[p]) p=i;
		if (p==-1 || t[p]>T) break;
		T-=t[p];
		tot+=t[p];
		ans+=tot;
		a[an++]=p;
		tag[p]=1;
		for (int i=st[p];i!=-1;i=nxt[i]) deg[aim[i]]--;
	}
	printf("%d %d\n",an,ans);
	for (int i=0;i<an;i++) printf("%d ",a[i]);
	puts("");
	return 0;
}