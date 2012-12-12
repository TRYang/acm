#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const double eps=1e-8;
const double pi=acos(-1.0);
const double inf=1e+9;

inline int sign(double x){
	return x<-eps ? -1 : x>eps;
}

inline double sqr(double x){
	return x*x;
}

struct node{
	double x,y;
	node(){}
	node(double _x,double _y):x(_x),y(_y){}
	//Read data
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	//print the point
	void pr(){
		printf("%lf %lf\n",x,y);
	}
	//module
	double len(){
		return hypot(x,y);
	}
	//Multiply a const
	void Mul(double c){
		x*=c;
		y*=c;
	}
	//Overloading the opreator +
	friend node operator + (const node &a,const node &b){
		return node(a.x+b.x,a.y+b.y);
	}
	//Overloading the operator +=
	friend node operator += (node &a,const node &b){
		a=a+b;
		return a;
	}
	//Overloading the opreator -
	friend node operator - (const node &a,const node &b){
		return node(a.x-b.x,a.y-b.y);
	}
	//Overloading the operator -=
	friend node operator -= (node &a,const node &b){
		a=a-b;
		return a;
	}
	//Overloading the opreator *
	friend double operator * (const node &a,const node &b);
	//Overloading the operator ==
	friend bool operator == (const node &a,const node &b){
		return sign(a.x-b.x)==0 && sign(a.y-b.y)==0;
	}
};

struct line{
	//line is define as a point and the direction vector
	//p is the a point on the line, a is the direction vector
	//the direction vector is (b-a)
	node a,b;
	line(){}
	line(node _a,node _b):a(_a),b(_b){}
};

struct circle{
	//circle is define as a point and a radius
	node c;
	double r;
	circle(){}
	circle(node O,double R):c(O),r(R){}
};

struct oval{
	//oval is define as two point and a conset A
	//oval is the set of point which dist(a,x)+dist(x,b)=2*a
	node a,b;
	double r;
	oval(){}
	oval(node _a,node _b,double _r):a(_a),b(_b),r(_r){}
};

//Dot product
double dot(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}

//Cross product
double cross(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

//distance between two points
double dist(node p0,node p1){
	return hypot(p0.x-p1.x,p0.y-p1.y);
}

//rotate the point with an angle of alpha
node rotate(node a,double alpha){
	double x=a.x*cos(alpha)+a.y*sin(alpha);
	double y=-a.x*sin(alpha)+a.y*cos(alpha);
	return node(x,y);
}

//middle point
node mp(node a,node b){
	return node((a.x+b.x)/2.0,(a.y+b.y)/2.0);
}

//delta_angle of ABC
double delta_angle(node a,node b,node c){
	return acos(dot(b,a,c)/(dist(b,a)*dist(b,c)));
}

//Overloading node's operator *
double operator * (const node &a,const node &b){
	return cross(node(0,0),a,b);
}

//return the Vertical Vector of a
node Vertical(node a){
	return node(-a.y,a.x);
}

//distance between a line and a point
double dist(line a,node b){
	return fabs(cross(a.a,a.b,b))/dist(a.a,a.b);
}

//calculate the intersection points of a line and a circle
//return the number of intersection points.
int ip_line_circle(line l,circle c,node &p1,node &p2){
	double d=dist(l,c.c);
	if (sign(d-c.r)>0) return 0;
	node a=l.a,b=l.b;
	node o=c.c;
	if (sign(d-c.r)==0){
		double dx=dot(a,b,o)/dist(a,b);
		p1=b-a;
		p1.Mul(dx/dist(a,b));
		p1=p1+a;
		return 1;
	}else{
		double dx=dot(a,b,o)/dist(a,b);
		double dy=sqrt(sqr(c.r)-sqr(d));
		p1=p2=b-a;
		p1.Mul((dx-dy)/dist(a,b));
		p1=p1+a;
		p2.Mul((dx+dy)/dist(a,b));
		p2=p2+a;
		return 2;
	}
}

//quadratic polynomial(Ax^2+Bx+C=0) solver
//return the number of solution
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

//calucate the intersection of a line and a oval
//return the number of intersection points
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
