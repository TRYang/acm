#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define maxn 1010
#define maxm 10010

using namespace std;

int st[maxn],aim[maxm],nxt[maxm],w[maxm],ln;
int id[maxm];
int dest[maxm];
vector<int> route[maxm];
map<int,int> Road[maxm];
map<int,int> f[maxm];
map<int, pair<int,int> > g[maxm];
int value_path[maxm];
priority_queue< pair<int, pair<int,int> > > Q;
int Head[maxm],Tail[maxm];
int n,m,S,T,r;
int ans,ansT,ansMask;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	nxt[ln]=st[x];
	w[ln]=z;
	st[x]=ln++;
}
vector<int> path;
void Find(int x,int mask){
	path.push_back(x);
	if (g[x][mask].first==-1) return;
	Find(g[x][mask].first,g[x][mask].second);
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&r,&S,&T);
	memset(st,-1,sizeof(st));
	for (int i=0;i<m;i++){
		route[i].clear();
		Road[i].clear();
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		id[ln]=i;
		in_edge(u,v,w);
		dest[i]=v;
	}
	for (int i=0;i<r;i++){
		int kn,tp,p;
		for (scanf("%d",&kn),tp=1;tp<=kn;tp++){
			scanf("%d",&p);
			--p;
			if (tp==1) Head[i]=p;
			if (tp==kn) Tail[i]=p;
			Road[p].insert(make_pair(i,route[p].size()));
			route[p].push_back(i);
		}
	}
	for (int i=0;i<m;i++)
		for (int j=0;j<route[id[i]].size();j++) value_path[route[id[i]][j]]+=w[i];
	for (int i=0;i<m;i++) f[i].clear();
	for (int i=0;i<m;i++) g[i].clear();
	while (!Q.empty()) Q.pop();
	for (int i=st[S];i!=-1;i=nxt[i]){
		int k=id[i];
		int mask=0;
		int value=w[i];
		for (int j=0;j<route[k].size();j++){
			if (Head[route[k][j]]==k) mask|=(1<<j);
			if (Tail[route[k][j]]==k && (mask&(1<<j))>0) value+=value_path[route[k][j]];
		}
		f[k].insert(make_pair(mask,value));
		g[k].insert(make_pair(mask,make_pair(-1,-1)));
		Q.push( make_pair( -value, make_pair(k,mask) ) );
	}
	ans=-1;
	while (!Q.empty()){
		int value=-Q.top().first;
		pair<int,int> state=Q.top().second;
		Q.pop();
		int k=state.first,mask=state.second;
		if (value>f[k][mask]) continue;
		int v=dest[k];
		if (v==T){
			if (ans==-1 || value<ans){
				ans=value;
				ansT=k;
				ansMask=mask;
			}
			continue;
		}
		for (int c=st[v];c!=-1;c=nxt[c]){
			int i=id[c];
			int tmask=0;
			int tvalue=value+w[c];
			for (int j=0;j<route[k].size();j++)
				if ((mask&(1<<j))>0){
					if (Road[i].find(route[k][j])!=Road[i].end()) tmask|=(1<<Road[i][route[k][j]]);
				}
			for (int j=0;j<route[i].size();j++){
				if (Head[route[i][j]]==i) tmask|=(1<<j);
				if (Tail[route[i][j]]==i && (tmask&(1<<j))>0) tvalue+=value_path[route[i][j]];
			}
			if (f[i].find(tmask)==f[i].end()){
				f[i].insert(make_pair(tmask,tvalue));
				g[i].insert(make_pair(tmask,make_pair(k,mask)));
				Q.push( make_pair( -tvalue, make_pair( i,tmask ) ) );
			}else
			if (tvalue<f[i][tmask]){
				f[i][tmask]=tvalue;
				g[i][tmask]=make_pair(k,mask);
				Q.push( make_pair( -tvalue, make_pair( i,tmask ) ) );
			}
		}
	}
	printf("%d\n",ans);
	if (ans==-1) return 0;
	path.clear();
	Find(ansT,ansMask);
	printf("%d\n",path.size());
	for (int i=path.size()-1;i>=0;i--) printf("%d ",path[i]+1);puts("");
	return 0;
}
