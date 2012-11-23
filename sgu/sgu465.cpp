#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 110

using namespace std;

int p[maxn];
int g[maxn][maxn];
int e[maxn*maxn][3];
int n,m,R;
double ans;
double calc(int d,double x){
	double ret=0;
	for (int i=0;i<n;i++)
		if (p[i]>0){
			if (g[e[d][0]][i]==100000000 && g[e[d][1]][i]==100000000) return 1e9;
			ret+=min(x+g[e[d][0]][i],e[d][2]-x+g[e[d][1]][i])*p[i]/10000.0;
		}
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&m,&R);
	for (int i=0;i<n;i++) scanf("%d",p+i);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) g[i][j]=100000000;
	for (int i=0;i<n;i++) g[i][i]=0;
	for (int i=0;i<m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		--u,--v;
		e[i][0]=u;
		e[i][1]=v;
		e[i][2]=w;
		g[u][v]=g[v][u]=w;
	}
	if (n==1){
		if (R==0) puts("0.00000");else puts("-1");
		return 0;
	}
	for (int k=0;k<n;k++)
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if (g[i][k]+g[k][j]<g[i][j]) g[i][j]=g[i][k]+g[k][j];
	ans=1e9;
	for (int i=0;i<m;i++){
		if (e[i][2]<2*R) continue;
		double l=R,r=e[i][2]-R,m1,m2;
		for (int t=0;t<50;t++){
			m1=l+(r-l)/3.0;
			m2=r-(r-l)/3.0;
			double v1=calc(i,m1),v2=calc(i,m2);
			if (v1>1e8) break;
			if (v1<v2) r=m2;else l=m1;
		}
		ans=min(ans,calc(i,l));
	}
	if (R==0){
		for (int i=0;i<n;i++){
			double sum=0;
			for (int j=0;j<n;j++)
				if (p[j]>0){
					if (g[i][j]==100000000){
						sum=1e9;
						break;
					}
					sum+=g[i][j]*p[j]*1.0/10000.0;
				}
			ans=min(ans,sum);
		}
	}
	if (ans>1e8) puts("-1");else
	printf("%.5lf\n",ans);
	return 0;
}
