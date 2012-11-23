#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define maxn 210
#define maxm 90010

using namespace std;

int color[maxn];
int tag[maxn];
vector<int> adj[maxn];
vector< pair<int,int> > e1,e2;
int q[maxn];

int st[maxn],aim[maxm],nxt[maxm],ln;
int cap[maxm],cost[maxm],flow[maxm];
int dist[maxn],pre[maxn],e[maxn];

int n,m1,m2;

void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	cap[ln]=1;
	flow[ln]=0;
	cost[ln]=-1;
	st[x]=ln++;

	aim[ln]=x;
	nxt[ln]=st[y];
	cap[ln]=flow[ln]=0;
	cost[ln]=1;
	st[y]=ln++;
}

void bfs(int sp){
	int qn=1;
	q[0]=sp;
	color[sp]=0;
	for (int p=0;p<qn;p++)
		for (int i=0;i<adj[q[p]].size();i++)
			if (color[adj[q[p]][i]]==-1)
				color[q[qn++]=adj[q[p]][i]]=(color[q[p]]^1);
}

int spfa(int x){
	tag[x]=1;
	for (int i=st[x];i!=-1;i=nxt[i]){
		if (flow[i]==cap[i]) continue;
		int v=aim[i];
		if (dist[x]+cost[i]<dist[v]){
			dist[v]=dist[x]+cost[i];
			pre[v]=x;
			e[v]=i;
			if (tag[v]) return v;
			int ret=spfa(v);
			if (ret!=-1) return ret;
		}
	}
	tag[x]=0;
	return -1;
}

int negcir(){
	memset(dist,0,sizeof(dist));
	memset(tag,0,sizeof(tag));
	for (int u=0;u<n<<1;u++){
		int ret=spfa(u);
		if (ret!=-1) return ret;
	}
	return -1;
}

vector< pair<int,int> > ans1,ans2;
void loop(){
	while (1){
	}
}

int Circular_Flow(){
	while (1){
		int k=negcir();
		if (k==-1) break;
		int i=k;
		do{
			flow[e[i]]++;
			flow[e[i]^1]--;
			i=pre[i];
		}while (i!=k);
	}
	int ret=0;
	ans1.clear();
	ans2.clear();
	for (int i=n;i<n+n;i++)
		for (int j=st[i];j!=-1;j=nxt[j])
			if (cost[j]<0 && flow[j]){
				if (color[i-n]==0){
					ans1.push_back(make_pair(i-n+1,aim[j]+1));
				}else{
					ans2.push_back(make_pair(i-n+1,aim[j]+1));
				}
				++ret;
			}
//	if (ans1.size()!=(ret>>1) || (ans2.size()!=(ret>>1))){
//		for (int i=0;i<n;i++) printf("%d ",color[i]);
//		puts("");
//		printf("%d\n",ret);
//		printf("ans1=\n");
//		for (int i=0;i<ans1.size();i++) printf("(%d,%d) ",ans1[i].first,ans1[i].second);
//		puts("");
//		printf("ans2=\n");
//		for (int i=0;i<ans2.size();i++) printf("(%d,%d) ",ans2[i].first,ans2[i].second);
//		puts("");
//		loop();
//	}
//	int d1[maxn],d2[maxn];
//	memset(d1,0,sizeof(d1));
//	for (int i=0;i<ans1.size();i++){
//		int u=ans1[i].first,v=ans1[i].second;
//		if (d1[u]) loop();
//		if (d1[v]) loop();
//		d1[u]=d1[v]=1;
//	}
//	memset(d2,0,sizeof(d2));
//	for (int i=0;i<ans2.size();i++){
//		int u=ans2[i].first,v=ans2[i].second;
////		if (d2[u]) loop();
////		if (d2[v]) loop();
//		d2[u]=d2[v]=1;
//	}
////	for (int i=0;i<n;i++)
////		if (d1[i]!=d2[i]) loop();
	return ret>>1;
}

int main(){
	scanf("%d%d%d",&n,&m1,&m2);
	e1.clear();
	e2.clear();
	for (int i=0;i<n;i++) adj[i].clear();
	for (int i=0;i<m1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		--u,--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		e1.push_back(make_pair(u,v));
	}
	for (int i=0;i<m2;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		--u,--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		e2.push_back(make_pair(u,v));
	}
	memset(color,-1,sizeof(color));
	for (int i=0;i<n;i++)
		if (color[i]==-1) bfs(i);

	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<n;i++) in_edge(i,n+i);
	for (int i=0;i<m1;i++){
		int u=e1[i].first,v=e1[i].second;
		if (color[u]==0) in_edge(n+u,v);else in_edge(n+v,u);
	}
	for (int i=0;i<m2;i++){
		int u=e2[i].first,v=e2[i].second;
		if (color[u]) in_edge(n+u,v);else in_edge(n+v,u);
	}
	printf("%d\n",Circular_Flow());
	for (int i=0;i<ans1.size();i++) printf("%d %d\n",ans1[i].first,ans1[i].second);
	for (int i=0;i<ans2.size();i++) printf("%d %d\n",ans2[i].first,ans2[i].second);
	return 0;
}
