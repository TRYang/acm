#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 60010
#define MAXN 110
#define MAXM 2010
#define MAXK 21
#define det 1000

using namespace std;

struct node{
	int a,b,id;
	friend bool operator < (const node &a,const node &b){
		return a.a-a.b<b.a-b.b || (a.a-a.b==b.a-b.b && a.a+a.b>b.a+b.b);
	}
} a[maxn];
short fa[MAXN][MAXM][MAXK],fb[MAXN][MAXM][MAXK];
int tag[maxn];
short g[MAXN][MAXM][MAXK];
int sa[maxn],sb[maxn];
int stp[MAXN];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		scanf("%d%d",&a[i].a,&a[i].b);
		a[i].id=i+1;
	}
	sort(a,a+n);
	sa[0]=sb[0]=0;
	for (int i=0;i<n;i++){
		sa[i+1]=sa[i]+a[i].a;
		sb[i+1]=sb[i]+a[i].b;
	}
	memset(fa,-1,sizeof(fa));
	memset(fb,-1,sizeof(fb));
	int N=0;
	int value=50*m;
	fa[0][det][0]=0;
	fb[0][det][0]=0;
	for (int st=0,en;st<n;st=en+1){
		for (en=st;en<n-1 && a[en+1].a-a[en+1].b==a[en].a-a[en].b;en++);
		int cv=a[st].a-a[st].b;
		N++;
		stp[N]=st;
		for (int j=-value;j<=value;j++){
			for (int k=0;k<=m;k++){
				for (int c=0;c<=k;c++){
					if (c>en-st+1) break;
					if (j-c*cv<-value || j-c*cv>value) continue;
					int da=fa[N-1][j-c*cv+det][k-c];
					int db=fb[N-1][j-c*cv+det][k-c];
					if (da+db<0) continue;
					da+=sa[st+c]-sa[st];
					db+=sb[st+c]-sb[st];
					if (da+db>fa[N][j+det][k]+fb[N][j+det][k]){
						fa[N][j+det][k]=da;
						fb[N][j+det][k]=db;
						g[N][j+det][k]=c;
					}
				}
			}
		}
	}
	int ans=1000000,ansa,ansb;
	for (int i=-value;i<=value;i++)
		if (fa[N][i+det][m]>-1)
			if (abs(i)<abs(ans) || (abs(i)==abs(ans) && fa[N][i+det][m]+fb[N][i+det][m]>ansa+ansb)){
				ans=i;
				ansa=fa[N][i+det][m];
				ansb=fb[N][i+det][m];
			}
	printf("%d %d\n",ansa,ansb);
	memset(tag,0,sizeof(tag));
	for (int i=N;i;i--){
		int k=g[i][ans+det][m];
		for (int c=0;c<k;c++) tag[a[stp[i]+c].id]=1;
		int cv=a[stp[i]].a-a[stp[i]].b;
		ans-=cv*k;
		m-=k;
	}
	for (int i=1;i<=n;i++)
		if (tag[i]) printf("%d ",i);
	puts("");
	return 0;
}
