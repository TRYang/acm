#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 20010
#define INF 1500000000

using namespace std;

typedef long long LL;

int x[maxn],y[maxn];
int tag[maxn];
int n;
inline void cover(int tx,int ty,int d,int v){
	for (int i=0;i<n;i++)
		if (x[i]>=tx && x[i]<=tx+d && y[i]>=ty && y[i]<=ty+d)
			tag[i]+=v;
}
int check(int dep,LL d){
	int i,j,k;
	int minx=INF,miny=INF,maxx=-INF,maxy=-INF;
	for (i=0;i<n;i++)
		if (!tag[i]){
			minx=min(minx,x[i]);
			maxx=max(maxx,x[i]);
			miny=min(miny,y[i]);
			maxy=max(maxy,y[i]);
		}
	if (minx==INF) return 1;
	if (dep==3) return maxx-minx<=d && maxy-miny<=d;
	cover(minx,miny,d,1);
	if (check(dep+1,d)) return 1;
	cover(minx,miny,d,-1);

	cover(maxx-d,miny,d,1);
	if (check(dep+1,d)) return 1;
	cover(maxx-d,miny,d,-1);

	cover(minx,maxy-d,d,1);
	if (check(dep+1,d)) return 1;
	cover(minx,maxy-d,d,-1);

	cover(maxx-d,maxy-d,d,1);
	if (check(dep+1,d)) return 1;
	cover(maxx-d,maxy-d,d,-1);

	return 0;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d %d",x+i,y+i);
	LL L=1,R=2000000000,mid;
	LL ans;
	while (L<=R){
		mid=(L+R)>>1;
		memset(tag,0,sizeof(tag));
		if (check(1,mid)){
			R=mid-1;
			ans=mid;
		}else L=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
