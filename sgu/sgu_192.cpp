#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define maxn 310

using namespace std;

struct node{
	int x,y;
} a[maxn][2];
double x[maxn*maxn+1000];
int p[maxn*maxn+1000];
double ty[maxn*maxn+1000];
int xn;
int col[maxn];
double tot[4];
char s[10];
int n;
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
int sgn(double x){
	if (fabs(x)<1e-8) return 0;
	if (x>-1e-8) return 1;else return -1;
}
int area(node p0,node p1,node p2){
	int k=(p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
	if (k<0) return -1;
	if (k>0) return 1;else return 0;
}
int cross(int p1,int p2){
	if (max(a[p1][0].x,a[p1][1].x)<=min(a[p2][0].x,a[p2][1].x) ||
		max(a[p1][0].y,a[p1][1].y)<=min(a[p2][0].y,a[p2][1].y) ||
		min(a[p1][0].x,a[p1][1].x)>=max(a[p2][0].x,a[p2][1].x) ||
		min(a[p1][0].y,a[p1][1].y)>=max(a[p2][0].y,a[p2][1].y)) return 0;
	if (area(a[p1][0],a[p1][1],a[p2][0])*area(a[p1][0],a[p1][1],a[p2][1])>=0) return 0;
	if (area(a[p2][0],a[p2][1],a[p1][0])*area(a[p2][0],a[p2][1],a[p1][1])>=0) return 0;
	return 1;
}
double inter_point(int p1,int p2){
	double k1=(double)(a[p1][1].y-a[p1][0].y)/(double)(a[p1][1].x-a[p1][0].x);
	double k2=(double)(a[p2][1].y-a[p2][0].y)/(double)(a[p2][1].x-a[p2][0].x);
	double b1=(double)(a[p1][0].y)-k1*a[p1][0].x;
	double b2=(double)(a[p2][0].y)-k2*a[p2][0].x;
	return (b2-b1)/(k1-k2);
}
int main(){
	int i,j,k;
	scanf("%d",&k);
	n=0;
	for (i=0;i<k;i++){
		scanf("%d %d %d %d %s",&a[n][0].x,&a[n][0].y,&a[n][1].x,&a[n][1].y,s);
		if (s[0]=='R') col[n]=1;else
		if (s[0]=='G') col[n]=2;else col[n]=3;
		if (a[n][0].x>a[n][1].x){
			node tmp=a[n][0];
			a[n][0]=a[n][1];a[n][1]=tmp;
		}
		if (a[n][0].x<a[n][1].x) n++;
	}
	xn=n<<1;
	for (i=0;i<n;i++){
		x[i<<1]=a[i][0].x;
		x[(i<<1)+1]=a[i][1].x;
	}
	for (i=0;i<n;i++)
		for (j=i+1;j<n;j++)
			if (cross(i,j)) x[xn++]=inter_point(i,j);
	sort(x,x+xn);
	k=xn;
	xn=1;
	for (i=1;i<k;i++)
		if (sgn(x[i]-x[xn-1])>0) x[xn++]=x[i];
	memset(p,-1,sizeof(p));
	for (i=0;i<n;i++){
		double kp=(double)(a[i][1].y-a[i][0].y)/(double)(a[i][1].x-a[i][0].x);
		int l=lower_bound(x,x+xn,a[i][0].x)-x,r=lower_bound(x,x+xn,a[i][1].x)-x;
		for (j=l;j<r;j++){
			double yy=kp*((x[j]+x[j+1])/2.0-a[i][0].x)+a[i][0].y;
			if (p[j]==-1 || yy<ty[j]){
				p[j]=col[i];
				ty[j]=yy;
			}
		}
	}
	tot[1]=tot[2]=tot[3]=0;
	for (i=0;i<xn-1;i++) tot[p[i]]+=x[i+1]-x[i];
	printf("R %.1lf\nG %.1lf\nB %.1lf\n",tot[1],tot[2],tot[3]);
	return 0;
}
