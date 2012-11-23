#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#define maxn 410

using namespace std;

struct node{
	int x,y;
	friend bool operator == (const node &x,const node &y){
		return x.x==y.x && x.y==y.y;
	}
} a[maxn],c1,c2;

struct inter_node{
	double x,y;
} d[10];

int dn;
int n,m;

int sgn(int x){
	if (x==0) return 0;
	if (x>0) return 1;else return -1;
}

int area(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

int dot(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}

double dis(inter_node p1,inter_node p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

bool cmp(node x,node y){
	return area(a[0],x,y)>0;
}

int cross(node p1,node p2,node q1,node q2){
	if (max(p1.x,p2.x)<=min(q1.x,q2.x)) return 0;
	if (max(p1.y,p2.y)<=min(q1.y,q2.y)) return 0;
	if (min(p1.x,p2.x)>=max(q1.x,q2.x)) return 0;
	if (min(p1.y,p2.y)>=max(q1.y,q2.y)) return 0;
	int k1=sgn(area(p1,p2,q1))*sgn(area(p1,p2,q2));
	int k2=sgn(area(q1,q2,p1))*sgn(area(q1,q2,p2));
	return k1<0 && k2<0;
}

void Make(node p1,node p2,double &a,double &b,double &c){
	if (p1.x==p2.x){
		a=1;b=0;c=-p1.x;
	}else
	if (p1.y==p2.y){
		a=0;b=1;c=-p1.y;
	}else{
		a=(double)(p1.y-p2.y)/(p1.x-p2.x);
		b=-1;
		c=-a*p1.x+p1.y;
	}
}

inter_node Inter(node p1,node p2,node q1,node q2){
	double a1,b1,c1;
	Make(p1,p2,a1,b1,c1);
	double a2,b2,c2;
	Make(q1,q2,a2,b2,c2);
	double tmp=a1*b2-a2*b1;
	inter_node res;
	res.x=(-c1*b2+c2*b1)/tmp;
	res.y=(-a1*c2+a2*c1)/tmp;
	return res;
}

int In_poly(node p){
	int i,j;
	for (i=0;i<n;i++){
		j=(i+1)%n;
		if (area(a[i],a[j],p)<=0) return 0;
	}
	return 1;
}

inter_node ch(node p){
	inter_node res;
	res.x=p.x;
	res.y=p.y;
	return res;
}

double Cal(node p1,node p2){
	int i,j,k;
	if (p1==p2) return 0;
	for (i=0;i<n;i++){
		j=(i+1)%n;
		if (area(a[i],a[j],p1)==0 && area(a[i],a[j],p2)==0) return 0;
	}
	dn=0;
	for (i=0;i<n;i++)
		if (a[i]==p1 || a[i]==p2) d[dn++]=ch(a[i]);
	for (i=0;i<n;i++){
		if (area(p1,p2,a[i])==0 && dot(p1,p2,a[i])>0 && dot(p2,p1,a[i])>0) d[dn++]=ch(a[i]);
		j=(i+1)%n;
		if (area(a[i],a[j],p1)==0 && dot(a[i],a[j],p1)>0 && dot(a[j],a[i],p1)>0) d[dn++]=ch(p1);
		if (area(a[i],a[j],p2)==0 && dot(a[i],a[j],p2)>0 && dot(a[j],a[i],p2)>0) d[dn++]=ch(p2);
		if (cross(p1,p2,a[i],a[j])) d[dn++]=Inter(p1,p2,a[i],a[j]);
	}
	if (dn==0){
		int t1=In_poly(p1),t2=In_poly(p2);
		if (t1 && t2) return dis(ch(p1),ch(p2));else return 0;
	}else
	if (dn==1){
		int t1=In_poly(p1),t2=In_poly(p2);
		if (t1==0 && t2) return dis(d[0],ch(p2));
		if (t1 && t2==0) return dis(d[0],ch(p1));
		if (!t1 && !t2) return 0;
	}else
	if (dn==2) return dis(d[0],d[1]);
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d %d",&a[i].x,&a[i].y);
	for (i=1;i<n;i++)
		if (a[i].y<a[0].y || (a[i].y==a[0].y && a[i].x<a[0].x)){
			node tmp;
			tmp=a[i];a[i]=a[0];a[0]=tmp;
		}
	sort(a+1,a+n,cmp);
	for (scanf("%d",&m);m>0;m--){
		scanf("%d %d %d %d",&c1.x,&c1.y,&c2.x,&c2.y);
		printf("%.2lf\n",Cal(c1,c2));
	}
	return 0;
}
