#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10010

using namespace std;

struct node{
	int x,y;
} a[maxn];
int p[maxn];
int row[maxn],col[maxn];
int x[maxn],xn;
int t[maxn];
int n;
bool cmpx(int x,int y){
	return a[x].x<a[y].x || (a[x].x==a[y].x && a[x].y<a[y].y);
}
bool cmpy(int x,int y){
	return a[x].y<a[y].y || (a[x].y==a[y].y && a[x].x<a[y].x);
}
int ask(int p){
	int res=0;
	for (;p>0;p-=(p&(p^(p-1)))) res+=t[p];
	return res;
}
void ins(int p,int x){
	for (;p<=xn;p+=(p&(p^(p-1)))) t[p]+=x;
}
int aabs(int x){return x>0?x:-x;}
int Cal(){
	int i,j,k;
	for (i=0;i<n;i++) x[i]=a[i].x;
	sort(x,x+n);
	xn=unique(x,x+n)-x;
	for (i=0;i<n;i++) a[i].x=upper_bound(x,x+xn,a[i].x)-x;
	for (i=0;i<n;i++) p[i]=i;
	sort(p,p+n,cmpx);
	for (i=1;i<n;i++)
		if (a[p[i]].x==a[p[i-1]].x && a[p[i]].y==a[p[i-1]].y) return 0;
	for (i=0;i<n;i=j+1){
		for (j=i;j<n-1 && a[p[j+1]].x==a[p[j]].x;j++);
		if ((j-i)%2==0) return 0;
		for (k=i;k<=j;k+=2){
			col[p[k]]=p[k+1];
			col[p[k+1]]=p[k];
		}
	}
	sort(p,p+n,cmpy);
	for (i=0;i<n;i=j+1){
		for (j=i;j<n-1 && a[p[j+1]].y==a[p[j]].y;j++);
		if ((j-i)%2==0) return 0;
		for (k=i;k<=j;k+=2){
			row[p[k]]=p[k+1];
			row[p[k+1]]=p[k];
		}
	}
	int ans=0;
	memset(t,0,sizeof(t));
	for (i=0;i<n;i++){
		if (a[p[i]].x<a[row[p[i]]].x){
			if (ask(a[row[p[i]]].x-1)-ask(a[p[i]].x)>0) return 0;
		}
		if (a[p[i]].y<a[col[p[i]]].y) ins(a[p[i]].x,1);else ins(a[p[i]].x,-1);
	}
	ans=aabs(x[a[row[0]].x-1]-x[a[0].x-1]);
	for (j=0,k=1,i=row[0];i!=0;k++){
		if (j==0){
			ans+=aabs(a[col[i]].y-a[i].y);
			i=col[i];
		}else{
			ans+=aabs(x[a[row[i]].x-1]-x[a[i].x-1]);
			i=row[i];
		}
		j^=1;
	}
	if (k<n) return 0;
	return ans;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d %d",&a[i].x,&a[i].y);
	printf("%d\n",Cal());
	return 0;
}
