#include <stdio.h>
#include <string.h>
#define maxn 410
int st[maxn],aim[maxn*maxn],link[maxn*maxn],num[maxn*maxn],ln;
short int g[maxn][40000];
int gn[maxn];
int a[maxn];
int dis[maxn];
int s,t;
int n,m;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	link[ln]=st[x];
	num[ln]=z;
	st[x]=ln++;
}
int main(){
	int i,j,k;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k,i+1);
		in_edge(k,j,i+1);
	}
	int an=1;
	a[0]=s;
	memset(dis,-1,sizeof(dis));
	memset(gn,0,sizeof(gn));
	dis[s]=0;
	for (int p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i]){
			if (dis[aim[i]]==-1){
				dis[aim[i]]=dis[a[p]]+1;
				a[an++]=aim[i];
			}
			if (dis[aim[i]]==dis[a[p]]+1){
				k=dis[aim[i]];
				g[k][gn[k]++]=num[i];
			}
		}
	printf("%d\n",dis[t]);
	for (i=1;i<=dis[t];i++){
		printf("%d ",gn[i]);
		for (j=0;j<gn[i];j++) printf("%d ",g[i][j]);
		printf("\n");
	}
	return 0;
}
