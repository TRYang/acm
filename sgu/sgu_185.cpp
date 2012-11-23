#include <stdio.h>
#include <string.h>
#define maxn 410
int st[maxn],aim[maxn*maxn],link[maxn*maxn],ln,l[maxn*maxn];
int f[maxn];
int con[maxn][maxn];
int a[maxn],an;
int tag[maxn];
int n,m;
int maxflow,mindis;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	link[ln]=st[x];
	l[ln]=z;
	st[x]=ln++;
}
int bfs(){
	int i,p,an;
	memset(tag,0,sizeof(tag));
	an=1;a[0]=1;
	tag[1]=1;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i])
			if (tag[aim[i]]==0 && con[a[p]][aim[i]]>0){
				tag[aim[i]]=a[p];
				a[an++]=aim[i];
			}
	if (tag[n]==0) return 0;
	for (i=n;i>1;i=tag[i]){
		con[tag[i]][i]--;
		con[i][tag[i]]++;
	}
	return 1;
}
void find(int x){
	if (x==1){
		printf("%d ",x);
		return;
	}
	for (int i=st[x];i!=-1;i=link[i])
		if (f[aim[i]]+l[i]==f[x] && con[x][aim[i]]>0){
			con[x][aim[i]]=0;
			find(aim[i]);
			printf("%d ",x);
			return;
		}
}
void dij(int s,int *f){
	int i,j,k;
	memset(tag,0,sizeof(tag));
	f[s]=0;
	for (k=1;k<=n;k++){
		j=-1;
		for (i=1;i<=n;i++)
			if (!tag[i] && f[i]>-1)
				if (j==-1 || f[i]<=f[j]) j=i;
		if (j==-1) return;
		if (j==n) return;
		tag[j]=1;
		for (i=st[j];i!=-1;i=link[i])
			if (f[aim[i]]==-1 || f[j]+l[i]<f[aim[i]]) f[aim[i]]=f[j]+l[i];
	}
}
int main(){
	int i,j,k;
	freopen("test.txt","r",stdin);
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (;m>0;m--){
		scanf("%d %d %d",&i,&j,&k);
		in_edge(i,j,k);
		in_edge(j,i,k);
	}
	memset(f,-1,sizeof(f));
	dij(1,f);
	if (f[n]==-1){
		printf("No solution\n");
		return 0;
	}
	//for (i=1;i<=n;i++) printf("%d ",f[i]);printf("\n");
	//for (i=1;i<=n;i++) printf("%d ",g[i]);printf("\n");
	for (i=1;i<n;i++)
		for (j=st[i];j!=-1;j=link[j])
			if (f[i]+l[j]==f[aim[j]]) con[i][aim[j]]=1;else con[i][aim[j]]=0;
	for (maxflow=0;maxflow<2 && bfs();maxflow++);
	if (maxflow==2){
		find(n);
		printf("\n");
		find(n);
		printf("\n");
	}else printf("No solution\n");
	return 0;
}
