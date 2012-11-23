#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);
const double inf =1e+9;

int sign(double x){
	return x<-eps?-1:x>eps;
}
inline double sqr(double x){
	return x*x;
}
struct node{
	double x,y;
	node(){}
	node(double _x,double _y):x(_x),y(_y){}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	void Mul(double c){
		x*=c;
		y*=c;
	}
	void pr(){
		printf("%lf %lf\n",x+eps,y+eps);
	}
	friend node operator + (const node &a,const node &b){
		return node(a.x+b.x,a.y+b.y);
	}
	friend node operator += (node &a,const node &b){
		a=a+b;
		return a;
	}
	friend node operator - (const node &a,const node &b){
		return node(a.x-b.x,a.y-b.y);
	}
	friend node operator -= (node &a,const node &b){
		a=a-b;
		return a;
	}
	friend bool operator == (const node &a,const node &b){
		return sign(a.x-b.x)==0 && sign(a.y-b.y)==0;
	}
};
struct line{
	node a,b;
	line(){}
	line(node _a,node _b):a(_a),b(_b){}
};
struct oval{
	node a,b;
	double r;
	oval(){}
	oval(node _a,node _b,double _r):a(_a),b(_b),r(_r){}
};
//distance between two points
double dist(node p0,node p1){
	return hypot(p0.x-p1.x,p0.y-p1.y);
}
double dot(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
double delta_angle(node a,node b,node c){
	return acos(dot(b,a,c)/(dist(a,b)*dist(c,b)));
}
node rotate(node a,double alpha){
	double x=a.x*cos(alpha)+a.y*sin(alpha);
	double y=-a.x*sin(alpha)+a.y*cos(alpha);
	return node(x,y);
}
node mp(node a,node b){
	return node((a.x+b.x)*0.5,(a.y+b.y)*0.5);
}
node Vertical(node a){
	return node(-a.y,a.x);
}
int solve2poly(double A,double B,double C,double &x1,double &x2){
	double delta=sqr(B)-4*A*C;
	if (delta<-eps) return 0;
	if (sign(A)==0){
		if (sign(B)==0) return 0;
		x1=x2=-C/B;
		return 1;
	}
	x1=(-B+sqrt(delta))/(2*A);
	x2=(-B-sqrt(delta))/(2*A);
	return sign(delta)?2:1;
}
int ip_line_oval(line l,oval z,node &p1,node &p2){
	node A=z.a,B=z.b;
	if (A.y>B.y) swap(A,B);else
	if (sign(A.y-B.y)==0 && A.x>B.x) swap(A,B);
	double a=z.r,b=sqrt(sqr(a)-sqr(dist(A,B)/2));
	node O=mp(A,B);
	A-=O;
	B-=O;
	l.a-=O;
	l.b-=O;
	double alpha=acos(B.x/hypot(B.x,B.y));
	A=rotate(A,alpha);
	B=rotate(B,alpha);
	l.a=rotate(l.a,alpha);
	l.b=rotate(l.b,alpha);
	double t1,t2;
	double tx=(l.b.x-l.a.x),ty=(l.b.y-l.a.y);
	int ret=solve2poly(sqr(b*tx)+sqr(a*ty),sqr(b)*2*l.a.x*tx+sqr(a)*2*l.a.y*ty,sqr(b*l.a.x)+sqr(a*l.a.y)-sqr(a*b),t1,t2);
	if (ret==0) return 0;
	p1=l.b-l.a;
	p1.Mul(t1);
	p1+=l.a;
	p2=l.b-l.a;
	p2.Mul(t2);
	p2+=l.a;
	p1=rotate(p1,2*pi-alpha);
	p2=rotate(p2,2*pi-alpha);
	p1+=O;
	p2+=O;
	return ret;
}
int main(){
	int tn;
	for (scanf("%d",&tn);tn;tn--){
		node A,B,O;
		double R;
		O.read();
		scanf("%lf",&R);
		A.read();
		B.read();
		if (A==B){
			node ans=node(O.x,O.y+R);
			ans.pr();
			continue;
		}
		node p1,p2;
		if (A==O)
		ip_line_oval(line(mp(A,B),mp(A,B)+Vertical(A-B)),oval(O,B,R*0.5),p1,p2);else
		ip_line_oval(line(mp(A,B),mp(A,B)+Vertical(A-B)),oval(O,A,R*0.5),p1,p2);
		if (p1==O) p1=node(O.x,O.y+R);else{
			p1=p1-O;
			p1.Mul(R/hypot(p1.x,p1.y));
		}
		if (p2==O) p2=node(O.x,O.y+R);else{
			p2=p2-O;
			p2.Mul(R/hypot(p2.x,p2.y));
		}
		p1+=O;
		p2+=O;
		if (delta_angle(A,p1,B)>delta_angle(A,p2,B)){
			p1.pr();
		}else{
			p2.pr();
		}
	}
	return 0;
}
