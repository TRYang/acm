#include <stdio.h>
#include <string.h>
#define maxn 110
int deg[maxn];
int st[maxn],aim[10010],link[10010],ln;
int a[maxn],an,p;
int ans[maxn];
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	memset(deg,0,sizeof(deg));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		deg[k]++;
	}
	an=0;
	for (i=1;i<=n;i++)
		if (!deg[i]) a[an++]=i;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i]){
			deg[aim[i]]--;
			if (!deg[aim[i]]) a[an++]=aim[i];
		}
	if (an==n){
		for (i=0;i<an;i++) ans[a[i]]=i+1;
		for (i=1;i<=n;i++) printf("%d ",ans[i]);
		printf("\n");
	}else printf("No solution\n");
	return 0;
}
