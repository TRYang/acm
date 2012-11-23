#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10010
#define inf (1000000000)

using namespace std;

struct node{
	int l,r,id,tag,value;
	node(){}
	node(int _l,int _r,int _x,int _y,int _z){
		l=_l;r=_r;
		id=_x;tag=_y;value=_z;
	}
	void read(){
		scanf("%d%d%d%d",&l,&r,&tag,&value);
	}
	friend bool operator < (const node &x,const node &y){
		return x.l<y.l;
	}
} a[maxn];
int f[21][maxn],h[21][maxn];
int g[maxn*21];
int idx[maxn*21];
int t[maxn*21];
int ansp,ans;
int flag;
int n,m;
bool cmp(int x,int y){
	return a[t[x]>>5].l+(t[x]&31)<a[t[y]>>5].l+(t[y]&31);
}
int Find(int l,int x){
	int r=m-1,mid,ret=-1,tmp;
	while (l<=r){
		mid=(l+r)>>1;
		tmp=t[idx[mid]];
		if (x<=a[tmp>>5].l+(tmp&31)){
			r=mid-1;
			ret=mid;
		}else l=mid+1;
	}
	return ret;
}
void work(){
	for (int i=0;i<21;i++) f[i][0]=0;
	for (int i=1,prev=0;i<n;i++)
		if (a[i].tag){
			m=0;
			for (int j=i-1;j>prev;j--)
				for (int k=-10;k<=10;k++){
					t[m]=(j<<5)|(k+10);
					idx[m]=m;
					++m;
				}
			sort(idx,idx+m,cmp);
			int Flag=0;
			for (int j=-10;j<=10;j++){
				int dx=j+10;
				f[dx][i]=-inf;
				int ty=10;
				while (ty>=-10 && a[prev].r+ty>a[i].l+j) --ty;
				if (ty<-10) continue;
				f[dx][i]=f[ty+10][prev];
				h[dx][i]=ty+10;
				for (int k=m-1;k>=0;k--){
					int p=(t[idx[k]]>>5),dp=(t[idx[k]]&31)-10;
					while (ty>=-10 && a[prev].r+ty>a[p].l+dp) --ty;
					if (ty<-10 || f[ty+10][prev]==-inf) break;
					if (k==m-1) g[k]=0;else g[k]=g[k+1];
					if (a[p].r+dp>a[i].l+j) continue;
					int tmp=a[p].value,np=Find(k+1,a[p].r+dp);
					if (np>-1) tmp+=g[np];
					if (k==m-1 || tmp>g[k+1]) g[k]=tmp;else g[k]=g[k+1];
					if (f[ty+10][prev]+g[k]>f[dx][i]){
						f[dx][i]=f[ty+10][prev]+g[k];
						h[dx][i]=ty+10;
					}
				}
				if (f[dx][i]>-inf){
					Flag=1;
					f[dx][i]+=a[i].value;
				}
			}
			if (!Flag){
				//No solution
				flag=0;
				return;
			}
			prev=i;
		}
	ans=-inf;
	for (int i=0;i<21;i++) ans=max(ans,f[i][n-1]);
}
int r[maxn],rn;
int xf[maxn];
int c[maxn*21];
void go(int value,int k){
	int p=(t[idx[k]]>>5),dp=(t[idx[k]]&31);
	r[rn++]=t[idx[k]];
	if (a[p].value==value) return;
	value-=a[p].value;
	for (int i=k+1;i<m;i++)
		if (a[p].r+dp<=a[t[idx[i]]>>5].l+(t[idx[i]]&31) && g[i]==value && c[i]){
			go(value,i);
			return;
		}
}
void Get(int dx){
	int d=n-1;
	rn=0;
	while (d>0){
		xf[d]=dx;
		if (d<n-1) r[rn++]=(d<<5)|dx;
		dx=h[dx][d];
		for (--d;!a[d].tag;d--);
	}
	xf[0]=dx;
	for (int i=1,prev=0;i<n;i++)
		if (a[i].tag){
			m=0;
			for (int j=i-1;j>prev;j--)
				for (int k=-10;k<=10;k++){
					t[m]=(j<<5)|(k+10);
					idx[m]=m;
					++m;
				}
			sort(idx,idx+m,cmp);
			int ty=xf[prev],dx=xf[i];
			if (f[ty][prev]+a[i].value<f[dx][i]){
				for (int k=m-1;k>=0;k--){
					int p=(t[idx[k]]>>5),dp=(t[idx[k]]&31);
					if (k==m-1) g[k]=0;else g[k]=g[k+1];
					c[k]=0;
					if (a[p].r+dp>a[i].l+dx) continue;
					int tmp=a[p].value,np=Find(k+1,a[p].r+dp);
					if (np>-1) tmp+=g[np];
					if (k==m-1 || tmp>g[k+1]){
						g[k]=tmp;
						c[k]=1;
					}else{
						g[k]=g[k+1];
						c[k]=0;
					}
					if (f[ty][prev]+g[k]+a[i].value==f[dx][i]){
						go(g[k],k);
						break;
					}
				}
			}
			prev=i;
		}
	for (int i=0;i<rn;i++) t[i]=r[i];
	for (int i=0;i<rn;i++) idx[i]=i;
	sort(idx,idx+rn,cmp);
	printf("%d %d\n",rn,ans);
	for (int i=0;i<rn;i++){
		int p=(t[idx[i]]>>5),dp=(t[idx[i]]&31)-10;
		printf("%d %d\n",a[p].id,dp);
	}
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		a[i].read();
		a[i].id=i;
	}
	a[n++]=node(-100100,-100000,-1,1,0);
	a[n++]=node(2000010000,2000020000,-2,1,0);
	sort(a,a+n);
	flag=1;
	work();
	if (flag){
		// printf("%d\n",ans);
		for (int i=0;i<21;i++)
			if (f[i][n-1]==ans){
				Get(i);
				break;
			}
	}else puts("NO SOLUTION");
	return 0;
}