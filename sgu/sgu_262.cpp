#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

map<vector<int>,int> t;
int tn;
int ans;
int b[110];
int g[110][30000];
int a[10][110];
int tmp[10];
int n,m,pn;
int GetID(vector<int> b){
	if (t.find(b)==t.end()){
		t.insert(make_pair(b,tn));
		return tn++;
	}else return t[b];
}
int min(int x,int y){return x<y?x:y;}
int f(int p,vector<int> c){
	int tp=GetID(c);
	if (g[p][tp]==-1){
		int i,k=1;
		for (i=0;i<pn;i++)
			if (c[i]!=i) k=0;
		if (k){
			g[p][tp]=0;
			return 0;
		}
		if (p==n*m) return 100000;
		vector<int> next;
		next.resize(pn);
		for (i=0;i<pn;i++)
			if (c[i]==i){
				next[i]=i;
				tmp[i]=-1;
			}else{
				if (a[c[i]][p]!=a[i][p]){
					if (tmp[c[i]]==-1){
						tmp[c[i]]=i;
						next[i]=i;
					}else next[i]=tmp[c[i]];
				}else next[i]=c[i];
			}
		g[p][tp]=min(f(p+1,c),f(p+1,next)+1);
	}
	return g[p][tp];
}
void find(int p,vector<int> c){
	int tp=GetID(c);
	int i,k=1;
	for (i=0;i<pn;i++)
		if (c[i]!=i) k=0;
	if (k) return;
	if (g[p+1][tp]==g[p][tp]) find(p+1,c);else{
		b[p]=1;
		vector<int> next;
		next.resize(pn);
		for (i=0;i<pn;i++)
			if (c[i]==i){
				next[i]=i;
				tmp[i]=-1;
			}else{
				if (a[c[i]][p]!=a[i][p]){
					if (tmp[c[i]]==-1){
						tmp[c[i]]=i;
						next[i]=i;
					}else next[i]=tmp[c[i]];
				}else next[i]=c[i];
			}
		find(p+1,next);
	}
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&pn);
	memset(a,0,sizeof(a));
	for (i=0;i<pn;i++){
		char s[20];
		for (j=0;j<n;j++){
			scanf("%s",s);
			for (k=0;k<m;k++)
				if (s[k]=='1') a[i][j*m+k]=1;
		}
	}
	t.clear();
	tn=0;
	vector<int> tmp;
	tmp.resize(pn);
	for (i=0;i<pn;i++) tmp[i]=0;
	memset(g,-1,sizeof(g));
	ans=f(0,tmp);
	printf("%d\n",ans);
	memset(b,0,sizeof(b));
	find(0,tmp);
	for (i=0;i<n;i++){
		for (j=0;j<m;j++) printf("%d",b[i*m+j]);
		printf("\n");
	}
	return 0;
}
