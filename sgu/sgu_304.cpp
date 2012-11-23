#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 610

using namespace std;

struct node{
	int a,p;
	friend bool operator < (const node &x,const node &y){
		return x.a<y.a;
	}
} a[maxn][maxn];
int an[maxn];
int tag[maxn];
int s[maxn][maxn];
int f[maxn][maxn];
int b[maxn];
int n,m,p;
inline void updata(int x,int y,int v){
	if (f[x][y]==-1 || v<f[x][y]) f[x][y]=v;
}
void Find(int x,int y){
	if (x==0) return;
	for (int i=0;i<=an[x];i++)
		if (y>=i && f[x-1][y-i]+s[x][i]==f[x][y]){
			for (int j=1;j<=i;j++) tag[a[x][j].p]=1;
			Find(x-1,y-i);
			return;
		}
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&p);
	for (i=1;i<=m;i++) scanf("%d",b+i);
	for (i=0;i<n;i++){
		scanf("%d %d",&j,&k);
		a[k][++an[k]].a=j;
		a[k][an[k]].p=i+1;
	}
	for (i=1;i<=m;i++)
		if (an[i]>0) sort(a[i]+1,a[i]+an[i]+1);
	for (i=1;i<=m;i++) a[i][1].a+=b[i];
	for (i=1;i<=m;i++){
		s[i][0]=0;
		for (j=1;j<=an[i];j++) s[i][j]=s[i][j-1]+a[i][j].a;
	}
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for (i=1;i<=m;i++)
		for (j=0;j<=n;j++)
			if (f[i-1][j]>-1){
				updata(i,j,f[i-1][j]);
				for (k=1;k<=an[i];k++)
					if (j+k<=n) updata(i,j+k,f[i-1][j]+s[i][k]);
			}
	int ans=0;
	for (i=1;i<=n;i++)
		if (p>=f[m][i]) ans=i;
	printf("%d\n",ans);
	Find(m,ans);
	for (i=1;i<=n;i++)
		if (tag[i]) printf("%d ",i);
	printf("\n");
	return 0;
}
