#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1010

using namespace std;

typedef long long LL;

struct node{
	int cost,id;
	friend bool operator < (const node &x,const node &y){
		return x.cost<y.cost;
	}
} a[maxn],b[maxn];
LL f[maxn][maxn][4];
int tag[maxn];
int an,bn;
int n,m;
inline void updata(int x,int y,int z,LL v){
	if (f[x][y][z]==-1 || v<f[x][y][z]) f[x][y][z]=v;
}
void pr(int x,int y,int z){	
	if (x==0) return;
	int ty=(z>>1)?y:y-1;
	for (int i=0;i<4;i++)
		if ((z>>1)>0){
			if ((i>>1)==(z&1) && i<3 && x-y>0 && f[x-1][ty][i]+b[x-y-1].cost*(m-x+1)==f[x][y][z]){
				if (f[x-1][ty][i]==-1) continue;
				pr(x-1,ty,i);
				printf("%d ",b[x-y-1].id+1);
				return;
			}
		}else{
			if ((i>>1)==(z&1) && i && y && f[x-1][ty][i]+a[y-1].cost*(m-x+1)==f[x][y][z]){
				if (f[x-1][ty][i]==-1) continue;
				pr(x-1,ty,i);
				printf("%d ",a[y-1].id+1);
				return;
			}
		}
}
int main(){
	int i,j,k;
	an=bn=0;
	scanf("%d %d",&m,&n);
	for (i=0;i<n;i++){
		scanf("%d %d",&j,&k);
		if (!k){
			a[an].cost=j;
			a[an++].id=i;
		}else{
			b[bn].cost=j;
			b[bn++].id=i;
		}
	}
	sort(a,a+an);
	sort(b,b+bn);
	memset(f,-1,sizeof(f));
	for (i=0;i<4;i++) f[0][0][i]=0;
	for (i=1;i<=m;i++)
		for (j=0;j<i;j++)
			for (k=0;k<4;k++)
				if (f[i-1][j][k]>-1){
					if (j<an && k>0){
						updata(i,j+1,k>>1,f[i-1][j][k]+a[j].cost*(m-i+1));
					}
					if (i-1-j<bn && k<3){
						updata(i,j,(k>>1)|2,f[i-1][j][k]+b[i-1-j].cost*(m-i+1));
					}
				}
	int ansx,ansy;
	LL ans=-1;
	for (i=0;i<=an;i++)
		for (j=0;j<4;j++)
			if (f[m][i][j]>-1)
				if (ans==-1 || f[m][i][j]<ans){
					ans=f[m][i][j];
					ansx=i;
					ansy=j;
				}
	if (ans==-1){
		printf("Impossible\n");
		return 0;
	}
	pr(m,ansx,ansy);
	puts("");
	return 0;
}