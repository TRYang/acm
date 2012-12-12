#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010
#define INF 1000000000

using namespace std;

const int tx[]={-1,-1, 0, 1, 1, 1, 0,-1};
const int ty[]={ 0, 1, 1, 1, 0,-1,-1,-1};
const int mx[]={ 1, 0,-1,-1,-1, 0, 1, 1};
const int my[]={-1,-1,-1, 0, 1, 1, 1, 0};
const int gx[]={1, 1,-1,-1};
const int gy[]={1,-1,-1, 1};
struct node{
	int x,y;
} a[maxn];
int edge[maxn<<3][3],en;
int ca[maxn],ba[maxn],ga[maxn];
int idx[maxn<<3],pos[maxn];
int x[maxn],xn;
int tf[maxn],t[maxn];
int n;
bool cmp(int x,int y){
	return ca[x]<ca[y] || (ca[x]==ca[y] && ba[x]<ba[y]);
}
void ins(int p,int v,int k){
	for (;p<=xn;p+=(p&(p^(p-1))))
		if (v<t[p]){
			t[p]=v;
			tf[p]=k;
		}
}
int ask(int p){
	int ret=-1,retv=INF;
	for (;p>0;p-=(p&(p^(p-1))))
		if (t[p]<retv){
			retv=t[p];
			ret=tf[p];
		}
	return ret;
}
void work(int p){
	for (int i=0;i<n;i++) ca[i]=tx[p]*a[i].x+ty[p]*a[i].y;
	for (int i=0;i<n;i++) ba[i]=mx[p]*a[i].x+my[p]*a[i].y;
	for (int i=0;i<n;i++) ga[i]=gx[p>>1]*a[i].x+gy[p>>1]*a[i].y;
	for (int i=0;i<n;i++) idx[i]=i;
	sort(idx,idx+n,cmp);
	for (int i=0;i<n;i++) x[i]=ba[i];
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	for (int i=0;i<n;i++) pos[i]=upper_bound(x,x+xn,ba[i])-x;
	for (int i=1;i<=xn;i++) t[i]=INF;
	for (int i=0;i<n;i++){
		int k=idx[i];
		int s=ask(pos[k]-1);
		if (s>-1){
			edge[en][0]=k;
			edge[en][1]=s;
			edge[en++][2]=ga[s]-ga[k];
		}
		ins(pos[k],ga[k],k);
	}
}
bool cmp2(int x,int y){return edge[x][2]<edge[y][2];}
int father[maxn];
int Find(int x){return father[x]= father[x]==x ? x : Find(father[x]);}
int main(){
	int cp=0;
	while (scanf("%d",&n),n){
		for (int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y);
		en=0;
		for (int i=0;i<8;i++) work(i);
		for (int i=0;i<en;i++) idx[i]=i;
		sort(idx,idx+en,cmp2);
		for (int i=0;i<n;i++) father[i]=i;
		long long ans=0;
		for (int i=0,tot=0;i<en;i++){
			int u=Find(edge[idx[i]][0]),v=Find(edge[idx[i]][1]);
			if (u!=v){
				father[u]=v;
				ans+=edge[idx[i]][2];
				tot++;
				if (tot==n-1) break;
			}
		}
		printf("Case %d: Total Weight = %lld\n",++cp,ans);
	}
	return 0;
}