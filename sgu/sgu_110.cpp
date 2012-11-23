#include <stdio.h>
#include <math.h>
#define maxn 55
#define eps 1e-15

struct node{
	double x,y,z;
	friend node operator + (const node &x,const node &y){
		node res;
		res.x=x.x+y.x;
		res.y=x.y+y.y;
		res.z=x.z+y.z;
		return res;
	}
	friend node operator - (const node &x,const node &y){
		node res;
		res.x=x.x-y.x;
		res.y=x.y-y.y;
		res.z=x.z-y.z;
		return res;
	}
} a[maxn];

node s,st;
double r[maxn];
int n;
int m;

double Dis(node p1,node p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z)+eps);
}

double dot(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y)+(p1.z-p0.z)*(p2.z-p0.z);
}

node mul(node x,double d){
	node res;
	res.x=x.x*d;
	res.y=x.y*d;
	res.z=x.z*d;
	return res;
}

int reflect(){
	int i,j,k=-1;
	double L,af1,af2;
	double L1,L2,L3,D,pl,tL,L4;
	for (i=0;i<n;i++)
		if (dot(s,s+st,a[i])>eps){
			L1=Dis(s,a[i]);
			L2=Dis(s+st,a[i]);
			L3=Dis(s,s+st);
			af1=acos((L1*L1+L3*L3-L2*L2)/2/L1/L3-eps);
			D=L1*sin(af1);
			if (D<r[i]-1e-8){
				pl=L1*L1-D*D;
				if (k==-1 || pl<L){
					k=i;
					L=pl;
				}
			}
		}
	if (k==-1) return 0;
	if (m==10) printf("etc.\n");else printf("%d ",k+1);
	L1=Dis(s,a[k]);
	L2=Dis(s+st,a[k]);
	L3=Dis(s,s+st);
	af1=acos((L1*L1+L3*L3-L2*L2)/2/L1/L3-eps);
	D=L1*sin(af1);
	pl=sqrt(L1*L1-D*D+eps);
	tL=sqrt(r[k]*r[k]-D*D+eps);
	pl-=tL;
	node ts,tst,v1,v2,v3;
	ts=s+mul(st,pl/L3);
	if (fabs(D)<eps){
		s=ts;
		st=mul(st,-1);
		return 1;
	}
//	printf("%.5lf %.5lf %.5lf\n",ts.x,ts.y,ts.z);
	L4=L1*((L1*L1+r[k]*r[k]-pl*pl)/2/L1/r[k]);
	v1=ts-a[k];
	v2=mul(v1,L4/r[k]);
	v3=a[k]+v2;
	v1=v3-s;
	v2=v1+v1;
	tst=(s+v2)-ts;
	s=ts;
	st=tst;
	//printf("%.5lf %.5lf %.5lf\n",st.x,st.y,st.z);
	return 1;
}

int main(){
	int i,j,k;
	freopen("test.txt","r",stdin);
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%lf %lf %lf %lf",&a[i].x,&a[i].y,&a[i].z,r+i);
	scanf("%lf %lf %lf %lf %lf %lf",&s.x,&s.y,&s.z,&st.x,&st.y,&st.z);
	m=0;
	while (1){
		if (!reflect()){
			printf("\n");
			break;
		}
		m++;
		if (m>10) break;
	}
	return 0;
}
