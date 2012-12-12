#define maxn 100
#define maxm 20010
int st[maxn],aim[maxm],link[maxm],ln;		
int cap[maxm],flow[maxm],cost[maxm];		
int dist[maxn],pre[maxn],e[maxn];	
int tag[maxn];
int n;
void in_edge(int x,int y,int c,int d){
	/*add an edge x->y,the capacity is c,the cost is d*/
}
int spfa(int u){	//Find negative path
	tag[u]=1;
	for (int i=st[u];i!=-1;i=link[i]){
		if (flow[i]>=cap[i]) continue;
		int v=aim[i];
		if (dist[u]+cost[i]<dist[v]){
			dist[v]=dist[u]+cost[i];
			pre[v]=u;	e[v]=i;
			if (tag[v]) return v;
			int ret=spfa(v);
			if (ret!=-1) return ret;
		}
	}
	tag[u]=0;
	return -1;
}
int negcir(){	//Find negative circular path
	memset(dist,0,sizeof(dist));
	memset(tag,0,sizeof(tag));
	for (int u=0;u<n;u++){
		int ret=spfa(u);
		if (ret!=-1) return ret;
	}
	return -1;
}
int CirMaxFlow(){
	while (1){
		int k=negcir();
		if (k==-1) break;
		int minf=100000,i=k;
		do{
			j=e[i];
			if (cap[j]-flow[j]<minf) minf=cap[j]-flow[j];
			i=pre[i];
		}while (i!=k);
		i=k;
		do{
			j=e[i];
			flow[j]+=minf;flow[j^1]-=minf;
			i=pre[i];
		}while (i!=k);
	}
	int ret=0;
	for (i=0;i<n;i++)
		for (j=st[n+i];j!=-1;j=link[j])
			if (cost[j]<0) ret+=flow[j];
	return ret;
}
