#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <string>
#include <set>
#define maxn 70010
#define maxm 600000

using namespace std;

string list[maxn];
struct edge{
	int u,v;
	int cp;
	int x1,x2;
	edge(){}
	edge(int _u,int _v,int d1,int d2){
		u=_u;
		v=_v;
		cp=-1;
		x1=d1;
		x2=d2;
	}
	void pr(){
		printf("%s-%s",list[u].c_str(),list[v].c_str());
	}
} e[maxm];
map<int,int> g[maxn],gt[maxn];
int indeg[maxn],outdeg[maxn];
map<string,int> idx;
set<int> s;
int tag[maxn];
int n,m;
int M;
int getID(string x){
	if (idx.find(x)==idx.end()){
		idx.insert(make_pair(x,n));
		list[n]=x;
		g[n].clear();
		indeg[n]=outdeg[n]=0;
		return n++;
	}else return idx[x];
}
void in_edge(int x,int y,int p1,int p2){
	e[m]=edge(x,y,p1,p2);
	if (g[x].find(y)==g[x].end()){
		++M;
		if (g[x].size()==1 && gt[x].size()==1) s.erase(x);
		if (g[y].size()==1 && gt[y].size()==1) s.erase(y);
		
		g[x].insert(make_pair(y,m));
		gt[y].insert(make_pair(x,m));
		
		if (g[x].size()==1 && gt[x].size()==1) s.insert(x);
		if (g[y].size()==1 && gt[y].size()==1) s.insert(y);
	}else{
		int d=g[x][y];
		e[m].cp=e[d].cp;
		e[d].cp=m;
	}
	++m;
}
void pr(int p){
	if (e[p].cp==-1 && e[p].x1==-1 && e[p].x2==-1){
		e[p].pr();
		return;
	}
	if (e[p].cp==-1){
		printf("(");
		pr(e[p].x1);
		printf(" ");
		pr(e[p].x2);
		printf(")");
	}else{
		printf("[");
		int x=p;
		while (x!=-1){
			if (x!=p) printf(" ");
			if (e[x].x1>-1){
				printf("(");
				pr(e[x].x1);
				printf(" ");
				pr(e[x].x2);
				printf(")");
			}else e[x].pr();
			x=e[x].cp;
		}
		printf("]");
	}
}
int main(){
	idx.clear();
	n=0;
	char u[30],v[30];
	s.clear();
	m=0;
	M=0;
	while (scanf("%s%s",u,v)!=EOF){
		string su=u,sv=v;
		int xu=getID(su),xv=getID(sv);
		in_edge(xu,xv,-1,-1);
	}
	memset(tag,0,sizeof(tag));
	while (1){
		if (s.size()==0) break;
		int x=*s.begin();
		tag[x]=1;
		s.erase(s.begin());
		M-=2;
		int p1=gt[x].begin()->first,p2=g[x].begin()->first;
		int s1=gt[x].begin()->second,s2=g[x].begin()->second;
		
		if (g[p1].size()==1 && gt[p1].size()==1) s.erase(p1);
		if (g[p2].size()==1 && gt[p2].size()==1) s.erase(p2);
		g[p1].erase(x);
		gt[p2].erase(x);
		if (g[p1].size()==1 && gt[p1].size()==1) s.insert(p1);
		if (g[p2].size()==1 && gt[p2].size()==1) s.insert(p2);
		in_edge(p1,p2,s1,s2);
		g[x].clear();
		gt[x].clear();
	}
	int flag=0;
	for (int i=0;i<n;i++)
		if (!tag[i]) ++flag;
	if (M==1 && flag==2){
		puts("YES");
		for (int i=0;i<n;i++)
			if (g[i].size()>0) pr(g[i].begin()->second);
		puts("");
	}else puts("NO");
	return 0;
}