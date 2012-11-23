#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 5010
#define maxm 100010

using namespace std;

struct node{
	int p,x;
	friend bool operator < (const node &x,const node &y){
		return x.x<y.x;
	}
} a[maxn];
struct hor{
	int v,d;
	friend bool operator < (const hor &x,const hor &y){
		return x.v>y.v || (x.v==y.v && x.d>y.d);
	}
} c[maxm];
int st[maxn],tv[maxm],td[maxm],link[maxm],ln;
double f[maxn];
int n,m;
int b;
void in_edge(int x,int y,int z){
	tv[ln]=y;
	td[ln]=z;
	link[ln]=st[x];
	st[x]=ln++;
}
int main(){
	int i,j,k;
	scanf("%d %d",&b,&n);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<n;i++){
		scanf("%d",&a[i].x);
		a[i].p=i;
		int cn;
		scanf("%d",&cn);
		for (j=0;j<cn;j++) scanf("%d %d",&c[j].v,&c[j].d);
		if (a[i].x>=b) continue;
		sort(c,c+cn);
		k=cn;
		cn=1;
		for (j=1;j<k;j++)
			if (c[j].d>c[cn-1].d) c[cn++]=c[j];
		for (j=cn-1;j>=0;j--) in_edge(i,c[j].v,c[j].d);
	}
	a[n].x=b;
	a[n].p=n;
	n++;
	sort(a,a+n);
	 for (i=0;i<n;i++) f[i]=1e9;
	 if (a[0].x==0) f[0]=0;
	 double ans=1e9;
	 for (i=0;i<n;i++)
	 	if (f[i]<1e9){
	 		k=st[a[i].p];
	 		for (j=i+1;j<n;j++){
	 			for (;k!=-1 && a[i].x+td[k]<a[j].x;k=link[k]);
	 			if (k==-1) break;
	 			f[j]=min(f[j],f[i]+(a[j].x-a[i].x)*1.0/tv[k]);
	 		}
	 		if (a[i].x==b) ans=min(ans,f[i]);
	 	}
	 if (ans<1e9) printf("%.5lf\n",ans);else printf("-1\n");
	return 0;
}
