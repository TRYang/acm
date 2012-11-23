#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define maxn 10010

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

line l[maxn];
node a[maxn];
int n;

int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) a[i].read();
	return 0;
}
