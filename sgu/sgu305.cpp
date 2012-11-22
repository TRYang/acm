#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#define maxn 310

using namespace std;

int st[maxn],aim[maxn*maxn],nxt[maxn*maxn],ln;
int tag[maxn];
int c[maxn*maxn];
int match[maxn*maxn];
map<int,int> num;
int n,m;
int ans[maxn];
int N;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int dfs(int x){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=st[x];i!=-1;i=nxt[i])
		if (match[aim[i]]==-1 || dfs(match[aim[i]])){
			match[aim[i]]=x;
			ans[x]=c[aim[i]];
			return 1;
		}
	return 0;
}
void add(int x,long long value){
	if (value<=0 || value>m) return;
	int v=value;
//	printf("%d %d\n",x,v);
	if (num.find(v)==num.end()){
		num.insert(make_pair(v,N));
		c[N]=v;
		in_edge(x,N++);
	}else in_edge(x,num[v]);
}
int main(){
	scanf("%d%d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	N=0;
	num.clear();
	for (int i=0;i<n;i++){
		int A,B;
		scanf("%d%d",&A,&B);
		if (A==0){
			add(i,B);
		}else
		if (A>0){
			int st=0;
			if (B<0) st=(-B-1)/A+1;
			for (int k=0;k<n;k++) add(i,(long long)A*(st+k)+B);
		}else{
			if (B<=0) continue;
			int st=0;
			if (B>m) st=(B-m-1)/(-A)+1;
			for (int k=0;k<n;k++) add(i,(long long)A*(st+k)+B);
		}
	}
	memset(match,-1,sizeof(match));
	memset(tag,0,sizeof(tag));
	int tot=0;
	for (int i=0;i<n;i++)
		if (dfs(i)){
			++tot;
			memset(tag,0,sizeof(tag));
		}else ans[i]=-1;
	for (int i=0,p=1;i<n;i++)
		if (ans[i]<0){
			while (num.find(p)!=num.end() && match[num[p]]>-1) ++p;
			ans[i]=p;
			++p;
		}
	for (int i=0;i<n-1;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n-1]);
	return 0;
}
