#include <stdio.h>
#include <string.h>
#include <math.h>
#define maxn 310
#define eps 1e-6
struct node{
	double x,y;
} a[maxn],s;
const double pi=acos(-1.0);
double r[maxn];
int g[maxn][maxn];
int tag[maxn];
int st[maxn],p[maxn];
int n;
int ans;

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

int check(int pn){
	int i,j,k;
	double tot=0,A,B,C,w;
	for (i=0;i<pn;i++){
		j=(i+1)%pn;
		A=dis(s,a[p[i]]);
		B=dis(s,a[p[j]]);
		C=dis(a[p[i]],a[p[j]]);
		w=area(s,a[p[i]],a[p[j]]);
		if (A<eps || B<eps) return 0;
		tot+=sgn(w)*Ang(A,B,C);
	}
	if (tot<0) tot=-tot;
	return tot>=2*pi-eps && tot<=2*pi+eps;
}

void dfs(int dep,int x){
	st[dep]=x;
	tag[x]=1;
	int i,j,k;
	for (i=0;i<n;i++)
		if (g[x][i] && tag[i] && dep>1 && i!=st[dep-1]){
			for (j=dep,k=0;st[j]!=i;j--) p[k++]=st[j];
			p[k++]=i;
			if (check(k)){
				ans=1;
				return;
			}
		}
	for (i=0;i<n;i++)
		if (g[x][i] && !tag[i]){
			dfs(dep+1,i);
			if (ans) return;
		}
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%lf %lf %lf",&a[i].x,&a[i].y,r+i);
	scanf("%lf %lf %lf",&s.x,&s.y,r+n);
	for (i=0;i<n;i++) r[i]+=r[n];
	memset(g,0,sizeof(g));
	for (i=0;i<n-1;i++)
		for (j=i+1;j<n;j++){
			if (r[i]+r[j]>dis(a[i],a[j])+eps){
				g[i][j]=g[j][i]=1;
			}
		}
	memset(tag,0,sizeof(tag));
	ans=0;
	for (i=0;i<n && !ans;i++)
		if (!tag[i]) dfs(1,i);
	if (!ans) printf("YES\n");else printf("NO\n");
	return 0;
}
