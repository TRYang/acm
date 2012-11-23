#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define maxn 40
#define eps 1e-6

using namespace std;

const double pi=acos(-1.0);

struct node{
	double x,y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
} b[maxn],a[maxn];

double dis(node p1,node p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double area(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
int sgn(double x){
	if (fabs(x)<eps) return 0;
	if (x>eps) return 1;else return -1;
}

double Ang(double a,double b,double c){
	return acos((a*a+b*b-c*c)/2/a/b);
}

int inside(node s,int pn){
	int i,j,k;
	double tot=0,A,B,C,w;
	for (i=0;i<pn;i++){
		j=(i+1)%pn;
		A=dis(s,a[i]);
		B=dis(s,a[j]);
		C=dis(a[i],a[j]);
		w=area(s,a[i],a[j]);
		if (A<eps || B<eps) return 0;
		tot+=sgn(w)*Ang(A,B,C);
	}
	if (tot<0) tot=-tot;
	return tot>=2*pi-eps && tot<=2*pi+eps;
}

int g[maxn][maxn];
int tag[maxn];
int stack[maxn];
int n;
node st,en;

int dfs(int dep,int x){
	stack[dep-1]=x;
	tag[x]=1;
	if (dep>1)
		for (int i=0;i<n;i++)
			if (i!=stack[dep-2] && g[x][i] && tag[i]){
				int an=0;
				for (int k=dep-1;k>=0 && stack[k]!=i;k--) a[an++]=b[stack[k]];
				a[an++]=b[i];
				if ((inside(st,an)^inside(en,an))>0) return 1;
			}
	for (int i=0;i<n;i++)
		if (g[x][i] && !tag[i])
			if (dfs(dep+1,i)) return 1;
	return 0;
}

int check(double R){
	memset(g,0,sizeof(g));
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (sgn(dis(b[i],b[j])-2.0*R)<0){
				g[i][j]=g[j][i]=1;
			}
	for (int i=0;i<n;i++){
		if (sgn(dis(st,b[i])-R)<0) return 0;
		if (sgn(dis(en,b[i])-R)<0) return 0;
	}
	for (int i=0;i<n;i++){
		memset(tag,0,sizeof(tag));
		if (dfs(1,i)) return 0;
	}
	return 1;
}

int main(){
	st.read();
	en.read();
	scanf("%d",&n);
	for (int i=0;i<n;i++) b[i].read();
	double L=0,R=200000,mid;
	while (L+1e-4<R){
		mid=(L+R)/2.0;
		if (check(mid)) L=mid;else R=mid;
	}
	printf("%.2lf\n",L);
	return 0;
}