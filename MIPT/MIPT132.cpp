#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 50010

using namespace std;

struct node{
	int l,r,tag;
	int id;
	node(){}
	node(int _l,int _r,int t){
		l=_l;
		r=_r;
		tag=t;
	}
	friend bool operator < (const node &x,const node &y){
		return x.l<y.l;
	}
} a[maxn];
int f[22][maxn];
char g[22][maxn];
int dt[maxn];
int idx[maxn*22];
int t[maxn*22];
int n;
int ans;
int m;
int stack[maxn],stn;
bool cmp(int x,int y){
	return a[t[x]>>5].l+(t[x]&31) < a[t[y]>>5].l+(t[y]&31);
}
int check(){
	a[n++]=node(-100,-100,1);
	a[n++]=node(2000000100,2000000100,1);
	sort(a,a+n);
	// for (int i=0;i<n;i++) printf("%d %d\n",a[i].l,a[i].r);
	int prev=0;
	for (int i=1;i<n;i++)
		if (a[i].tag){
			if (a[i].l+10<a[prev].r-10) return -1;
			m=0;
			for (int k=i-1;k>prev;k--)
				for (int j=-10;j<=10;j++){
					idx[m]=m;
					t[m++]=(k<<5)|(j+10);
				}
			sort(idx,idx+m,cmp);
			int tag=0;
			for (int j=-10;j<=10;j++){
				int dx=j+10,p,dp,dk=10;
				f[dx][i]=-1;
				while (dk>=-10 && a[prev].r+dk>a[i].l+j) --dk;
				if (dk>=-10 && f[dk+10][prev]>-1){
					f[dx][i]=f[dk+10][prev];
					g[dx][i]=dk+10;
				}
				for (int tot=0,k=m-1,T=a[i].l+j;k>=0;k--){
					if (dk<-10) break;
					p=t[idx[k]]>>5;
					dp=(t[idx[k]]&31)-10;
					if (a[p].r+dp<=T){
						++tot;
						T=a[p].l+dp;
					}
					while (dk>=-10 && a[prev].r+dk>T) --dk;
					if (dk<-10) break;
					if (f[dk+10][prev]>-1 && f[dk+10][prev]+tot>f[dx][i]){
						f[dx][i]=f[dk+10][prev]+tot;
						g[dx][i]=dk+10;
					}
				}
				if (f[dx][i]>-1){
					if (i<n-1) ++f[dx][i];
					tag=1;
				}
			}
			if (!tag) return -1;
			prev=i;
		}
	int ret=-1;
	for (int i=0;i<=20;i++) ret=max(ret,f[i][n-1]);
	return ret;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int tag,l,r;
		scanf("%d%d%d",&l,&r,&tag);
		a[i]=node(l,r,tag);
		a[i].id=i;
	}
	ans=check();
	if (ans==-1) puts("NO SOLUTION");else{
		// for (int i=0;i<n;i++) printf("%d %d\n",a[i].l,a[i].r);
		printf("%d\n",ans);
		for (int k=0;k<=20;k++)
			if (f[k][n-1]==ans){
				int i=n-1,c=k;
				while (i){
					dt[i]=c;
					c=g[c][i];
					for (i--;!a[i].tag;i--);
				}
				break;
			}
		for (int i=1,prev=0;i<n;i++)
			if (a[i].tag){
				m=0;
				for (int k=i-1;k>prev;k--)
					for (int j=-10;j<=10;j++){
						idx[m]=m;
						t[m++]=(k<<5)|(j+10);
					}
				sort(idx,idx+m,cmp);
				int dy=g[dt[i]][i];
				stn=0;
				for (int k=m-1,T=a[i].l+dt[i]-10;k>=0;k--){
					if (f[dy][prev]+stn+(i<n-1)==f[dt[i]][i]) break;
					int p=(t[idx[k]]>>5),dp=(t[idx[k]]&31)-10;
					if (a[p].r+dp<=T){
						stack[++stn]=t[idx[k]];
						T=a[p].l+dp;
					}
				}
				for (;stn;stn--) printf("%d %d\n",a[stack[stn]>>5].id,(stack[stn]&31)-10);
				if (i<n-1) printf("%d %d\n",a[i].id,dt[i]-10);
				prev=i;
			}
	}
	return 0;
}