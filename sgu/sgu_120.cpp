#include <stdio.h>
#include <string.h>
#include <math.h>
#define maxn 160
const double pi=acos(-1.0);
struct coor{
	double x,y;
	void pr(){
		if (fabs(x)<1e-8) x=fabs(x);
		if (fabs(y)<1e-8) y=fabs(y);
		printf("%.6f %.6lf\n",x,y);
	}
};
coor a[maxn],O,v,next;
double R;
int n,n1,n2;
double Dist(coor p1,coor p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
void work(int p1,int p2,int dn){
	double xs=a[p2].x-a[p1].x,ys=a[p2].y-a[p1].y;
	double Ang=(pi-(2.0*pi*dn/n))/2.0;
	double xt=xs*cos(Ang)-ys*sin(Ang),yt=xs*sin(Ang)+ys*cos(Ang);
	double l=Dist(a[p1],a[p2]);
	O.x=a[p1].x+(R/l)*xt;
	O.y=a[p1].y+(R/l)*yt;
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&n1,&n2);
	n1--;
	n2--;
	scanf("%lf %lf",&a[n1].x,&a[n1].y);
	scanf("%lf %lf",&a[n2].x,&a[n2].y);
	if (n1>n2){
		k=n1;n1=n2;n2=k;
	}
	R=(Dist(a[n1],a[n2])/2.0)/sin(pi*(n2-n1)/n);
//	printf("%.5lf\n",R);
	if (n%2==0 && n2-n1==n>>1){
		O.x=(a[n1].x+a[n2].x)/2.0;
		O.y=(a[n1].y+a[n2].y)/2.0;
	}else{
		if (n2-n1<=n>>1) work(n2,n1,n2-n1);else work(n1,n2,n1+n-n2);
	}
	double Ang=2.0*pi/n;
	v.x=a[n1].x-O.x;
	v.y=a[n1].y-O.y;
	for (i=(n1-1+n)%n;i!=n1;i=(i-1+n)%n){
		next.x=v.x*cos(Ang)-v.y*sin(Ang);
		next.y=v.x*sin(Ang)+v.y*cos(Ang);
		v=next;
		a[i].x=O.x+v.x;
		a[i].y=O.y+v.y;
	}
	for (i=0;i<n;i++) a[i].pr();
	return 0;
}
