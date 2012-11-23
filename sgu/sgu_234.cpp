#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 40010
#define maxm 250010

using namespace std;

const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
int st[maxn],nxt[maxm],ln;
unsigned short aim[maxm];
char flow[maxm],con[maxm];
unsigned short level[maxn];
unsigned short q[maxn],stack[maxn];
int next[maxn];
unsigned short g[210][210];
int source,remit;
int ans;
int n,m;
void in_edge(int x,int y,int f,int c){
//	printf("%d -> %d\n",x,y);
	aim[ln]=y;
	nxt[ln]=st[x];
	flow[ln]=f+1;
	con[ln]=c+1;
	st[x]=ln++;
//	printf("%d\n",ln);
}
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<n && y>=0 && y<m && g[x][y];
}
void bfs(){
	int qn=1;
	q[0]=source;
	memset(level,0,sizeof(level));
	level[source]=1;
	for (int p=0;p<qn;p++)
		for (int i=st[q[p]];i!=-1;i=nxt[i])
			if (level[aim[i]]==0 && flow[i]<con[i]){
				level[aim[i]]=level[q[p]]+1;
				q[qn++]=aim[i];
			}
}
int e[maxn];
void dfs(){
	int stn=1;
	stack[1]=source;
	next[source]=st[source];
	while (stn){
		int k=stack[stn],i;
		if (k==remit){
			int delta=100000;
			for (int i=1;i<stn;i++){
				int x=e[stack[i+1]];
				delta=min(delta,con[x]-flow[x]);
			}
			int p=-1;
			for (int i=stn-1;i>0;i--){
				int x=e[stack[i+1]];
				flow[x]+=delta;
				flow[x^1]-=delta;
				if (flow[x]==con[x]) p=i;
			}
			ans-=delta;
			stn=p;
			continue;
		}
		for (i=next[k];i!=-1;i=nxt[i])
			if (level[aim[i]]==level[k]+1 && flow[i]<con[i]){
				next[k]=nxt[i];
				next[aim[i]]=st[aim[i]];
				stack[++stn]=aim[i];
				e[aim[i]]=i;
				break;
			}
		if (i==-1){
			level[k]=(n*m*3);
			--stn;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) scanf("%d",&g[i][j]);
	memset(st,-1,sizeof(st));
	ln=0;
	source=n*m;
	remit=source+1;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if ((i+j)&1){
				if (g[i][j]){
					in_edge(i*m+j,remit,0,1);
					in_edge(remit,i*m+j,0,0);
				}
			}else{
				if (g[i][j]){
					in_edge(source,i*m+j,0,1);
					in_edge(i*m+j,source,0,0);
					for (int k=0;k<4;k++)
						if (check(i,j,k)){
							int v=(i+mx[k])*m+j+my[k];
							in_edge(i*m+j,v,0,1);
							in_edge(v,i*m+j,0,0);
						}
				}
			}
	ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) ans+=g[i][j];
	while (1){
		bfs();
		if (level[remit]==0) break;
		dfs();
	}
	printf("%d\n",ans);
	for (int i=st[source];i!=-1;i=nxt[i])
		if (flow[i]==con[i] && level[aim[i]]==0){
			int v=aim[i];
			g[v/m][v%m]=2;
		}
	for (int i=st[remit];i!=-1;i=nxt[i])
		if (level[aim[i]]>0){
			int v=aim[i];
			g[v/m][v%m]=2;
		}
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			if (g[i][j]==2) printf(".");else
			if (g[i][j]==0) printf("#");else printf("G");
		puts("");
	}
	return 0;
}
