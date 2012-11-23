#include <stdio.h>
#include <string.h>
#include <map>
#define maxn 10010
#define maxm 100010

using namespace std;

map<int,int> a[maxn];
int deg[maxn],id[maxn];
int st[maxn],aim[maxm],link[maxm],ln;
int c[maxn],next[maxn],cn,sp;
int n,m,N;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int find_cir(int x){
	if (a[x].empty()) return 0;
	int k=x,tmp;
	sp=cn;
	do{
		tmp=a[k].begin()->first;
		c[cn++]=tmp;
		a[k].erase(a[k].begin());
		a[tmp].erase(a[tmp].find(k));
		k=tmp;
	}while (k!=x);
	cn--;
	for (int i=sp;i<cn;i++) next[i]=i+1;
	return 1;
}
int main(){
	int i,j,k;
	freopen("test.txt","r",stdin);
	scanf("%d %d",&n,&m);
	memset(deg,0,sizeof(deg));
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		in_edge(k,j);
		deg[j]++;deg[k]++;
	}
	memset(id,-1,sizeof(id));
	N=0;
	for (i=1;i<=n;i++)
		if (id[i]==-1){
			id[i]=N++;
			if (deg[i]>2)
				for (j=st[i];j!=-1;j=link[j])
					if (deg[aim[j]]>2) id[aim[j]]=id[i];
		}
	for (i=0;i<N;i++) a[i].clear();
	memset(deg,0,sizeof(deg));
	for (i=1;i<=n;i++)
		for (j=st[i];j!=-1;j=link[j])
			if (id[aim[j]]!=id[i]){
				deg[id[i]]++;
				a[id[i]].insert(make_pair(id[aim[j]],1));
			}
	for (i=0;i<N;i++)
		if (deg[i]%2==1){
			printf("-1\n");
			return 0;
		}
	cn=1;c[0]=0;next[0]=-1;
	for (i=0;i!=-1;)
		if (find_cir(c[i])){
			next[cn-1]=next[i];
			next[i]=sp;
		}else i=next[i];
	
	return 0;
}
