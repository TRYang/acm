#include <stdio.h>
#include <string.h>
#define maxn 100010
#define maxm 200010
int st[maxn],aim[maxm<<1],nxt[maxm<<1],ln;
int d[4][maxn];
int xp[4];
int dis[maxn],mask[maxn],cmask[maxn];
int pre[maxn],low[maxn],Tm;
int is_cut[maxn];
int stack[maxn],next[maxn];
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
void dfs(int sp){
	int stn=1;
	stack[1]=sp;
	memset(dis,-1,sizeof(dis));
	memset(cmask,0,sizeof(cmask));
	memset(mask,0,sizeof(mask));
	dis[sp]=0;
	d[sp][sp]=0;
	next[sp]=st[sp];
	mask[sp]=0;
	pre[sp]=low[sp]=Tm=1;
	xp[sp]=sp;
	memset(is_cut,0,sizeof(is_cut));
	while (stn){
		int k=stack[stn],i;
		for (i=next[k];i!=-1;i=nxt[i])
			if (stn==1 || aim[i]!=stack[stn-1]){
				if (dis[aim[i]]==-1){
					next[k]=nxt[i];
					int v=aim[i];
					next[v]=st[v];
					stack[++stn]=v;
					dis[v]=dis[k]+1;
					d[sp][v]=dis[v];
					pre[v]=low[v]=++Tm;
					if (v<=3){
						mask[v]|=(1<<v-1);
					}
					break;
				}else
				if (pre[aim[i]]<low[k]) low[k]=pre[aim[i]];
			}
		if (i==-1){
			--stn;
			if (stn){
				int x=stack[stn];
				mask[x]|=mask[k];
				if (low[k]>=pre[x]){
					is_cut[x]=1;
					cmask[x]|=mask[k];
				}else
				if (low[k]<low[x]) low[x]=low[k];
			}
			if (mask[k]==(7-(1<<sp-1)) && cmask[k]==mask[k] && is_cut[k] && dis[k]>dis[xp[sp]]){
				xp[sp]=k;
			}
		}
	}
}
int check(int x){
	int u=-1,v=-1;
	for (int i=1;i<4;i++)
		if (i!=x)
			if (u==-1) u=i;else v=i;
	x=xp[x];
	if (d[u][x]==1 && d[v][x]==1) return 1;
//	printf("%d %d %d\n",x,u,v);
	if (d[u][x]==1){
		return d[v][x]<=d[v][u];
	}else
	if (d[x][v]==1){
		return d[u][x]<=d[u][v];
	}else{
		return d[u][x]-1+d[v][x]-1<d[u][v];
	}
}
int main(){
	memset(st,-1,sizeof(st));
	ln=0;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		in_edge(u,v);
		in_edge(v,u);
	}
	memset(xp,-1,sizeof(xp));
	for (int i=1;i<4;i++) dfs(i);
//	for (int i=1;i<4;i++) printf("xp=%d\n",xp[i]);
	for (int i=1;i<4;i++)
		if (check(i)){
			puts("1");
			return 0;
		}
	puts("2");
	return 0;
}
