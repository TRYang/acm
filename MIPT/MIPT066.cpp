#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 4010

using namespace std;

struct query{
	int type;
	int x,y;
	int L;
	void read(){
		scanf("%d%d%d%d",&type,&x,&y,&L);
	}
} d;
int father[maxn<<1];
int size[maxn<<1];
int stack[maxn<<1],stn;
int belong[maxn];
int t[maxn];
int cnt;
int type;
int n,m;
int ans1,ans2;
int Find(int x){
	if (father[x]==x) return x;
	int fx=Find(father[x]);
	size[father[x]]-=size[x];
	size[fx]+=size[x];
	father[x]=fx;
	return fx;
}
inline int check(int x){
	if (size[x]==0) stack[++stn]=x;
}
inline void cover(int x,int y){
	if (belong[y]>-1){
		belong[y]=Find(belong[y]);
		--size[belong[y]];
		check(belong[y]);
		belong[y]=-1;
	}
}
int main(){
	scanf("%d",&type);
	scanf("%d%d",&n,&m);
	scanf("%d",&cnt);
	int pt=0;
	if (pt<cnt) d.read();
	stn=0;
	for (int i=0;i<8000;i++) stack[++stn]=i;
	memset(belong,-1,sizeof(belong));
	ans1=ans2=0;
	for (int i=1;i<=n;i++){
		int tag=0;
		for (int j=1;j<=m;j++){
			if (pt<cnt && d.x==i && d.y==j){
				if (d.type==1){
					t[d.y]=max(t[d.y],i+d.L-1);
				}else{
					tag=max(tag,j+d.L-1);
				}
				++pt;
				if (pt<cnt) d.read();
				cover(i,j);
			}else
			if (j>tag && i>t[j]){
				ans1++;
				if (belong[j]==-1 && (j==1 || belong[j-1]==-1)){
					int k=stack[stn--];
					father[k]=k;
					belong[j]=k;
					size[k]=1;
					++ans2;
				}
				if (belong[j]==-1 && (j>1 && belong[j-1]>-1)){
					int k=Find(belong[j-1]);
					belong[j]=k;
					size[k]++;
				}
				if (belong[j]>-1 && (j>1 && belong[j-1]>-1)){
					if (Find(belong[j-1])!=Find(belong[j])){
						int fx=belong[j-1],fy=belong[j];
						father[fy]=fx;
						size[fx]+=size[fy];
						--ans2;
					}
				}
			}else cover(i,j);
		}
	}
	if (type==1) printf("%d\n",ans1);else printf("%d\n",ans2);
	return 0;
}