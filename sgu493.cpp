#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1010

using namespace std;

struct building{
	int h,l,r;
	void read(){
		scanf("%d%d%d",&l,&r,&h);
	}
	friend bool operator < (const building &a,const building &b){
		return a.l<b.l;
	}
} a[maxn];
int tag[maxn][2];
int f[maxn][2];
int n;
int ans;
int check(int p,int d){
	if (d==0){
		if (p==0) return 1;
		int dy=a[p-1].h,dx=a[p].l-a[p-1].r;
		for (int i=p-2;i>=0;i--){
			int dy2=a[i].h,dx2=a[p].l-a[i].r;
			if (dy2*dx>=dy*dx2) return 0;
		}
		return 1;
	}else{
		if (p==n-1) return 1;
		int dy=a[p+1].h,dx=a[p+1].l-a[p].r;
		for (int i=p+2;i<n;i++){
			int dy2=a[i].h,dx2=a[i].l-a[p].r;
			if (dy2*dx>=dy*dx2) return 0;
		}
		return 1;
	}
}
int main(){
	int tn;
	for (scanf("%d",&tn);tn;tn--){
		scanf("%d",&n);
		for (int i=0;i<n;i++) a[i].read();
		ans=0;
		sort(a,a+n);
		for (int i=0;i<n;i++){
			tag[i][0]=check(i,0);
			tag[i][1]=check(i,1);
		}
		memset(f,0,sizeof(f));
		for (int i=0;i<n;i++){
			if (tag[i][0]){
				if (i==0 || !f[i][0]){
					f[i][0]=1;
					++ans;
				}
			}
			if (tag[i][1]){
				f[i][1]=f[i+1][0]=1;
				++ans;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
