#include <stdio.h>
#include <string.h>
#define maxn 310
int col[maxn],r[maxn],T[maxn][2];
int g[maxn][maxn],d[maxn][maxn],gn[maxn];
int f[maxn],tag[maxn],h[maxn];
int n,m;
int ss,ee;
char s1[10];

int Get(int x,int y){
	if (y<r[x]) return col[x];
	y-=r[x];
	y%=T[x][0]+T[x][1];
	return y<T[x][col[x]^1] ? col[x]^1 : col[x];
}

int Next(int x,int y){
	if (y<r[x]) return r[x];
	int dt;
	if ((y-r[x])%(T[x][0]+T[x][1])<T[x][col[x]^1]) dt=T[x][col[x]^1]-((y-r[x])%(T[x][0]+T[x][1]));else
		dt=T[x][0]+T[x][1]-((y-r[x])%(T[x][0]+T[x][1]));
	return y+dt;
}

int stime(int x,int y,int t){
	int cx=Get(x,t),cy=Get(y,t);
	if (cx==cy) return t;
	if (T[x][0]==T[y][1] && T[x][1]==T[y][0] && r[x]==r[y]) return -10000000;
	int dx=Next(x,t),dy=Next(y,t);
	if (dx==dy){
		dx=Next(x,dx);
		dy=Next(y,dy);
		if (dx==dy){
			dx=Next(x,dx);
			dy=Next(y,dy);
			return dx<dy ? dx : dy;
		}else return dx<dy ? dx : dy;
	}else return dx<dy ? dx : dy;
}

void pr(int x){
	if (h[x]>0) pr(h[x]);
	printf("%d ",x);
}

int Dij(int st,int en){
	memset(f,-1,sizeof(f));
	memset(tag,0,sizeof(tag));
	int i,j,k,ll,p;
	f[st]=0;h[st]=0;
	for (ll=0;ll<n;ll++){
		p=-1;
		for (i=1;i<=n;i++)
			if (f[i]>-1 && !tag[i])
				if (p==-1 || f[i]<f[p]) p=i;
		if (p==-1) break;
		tag[p]=1;
		for (j=0;j<gn[p];j++){
			k=g[p][j];
			int time=stime(p,k,f[p])+d[p][k];
			if (time<0) continue;
			if (f[k]==-1 || time<f[k]){
				f[k]=time;
				h[k]=p;
			}
		}
	}
	if (f[en]==-1) return 0;
	printf("%d\n",f[en]);
	pr(en);
	printf("\n");
	return 1;
}

int main(){
	int i,j,k;
	scanf("%d %d",&ss,&ee);
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++){
		scanf("%s %d %d %d",s1,r+i,&T[i][0],&T[i][1]);
		if (s1[0]=='B') col[i]=0;else col[i]=1;
	}
	memset(gn,0,sizeof(gn));
	memset(d,0,sizeof(d));
	for (;m>0;m--){
		scanf("%d %d %d",&i,&j,&k);
		g[i][gn[i]++]=j;
		g[j][gn[j]++]=i;
		d[i][j]=d[j][i]=k;
	}
	if (!Dij(ss,ee)) printf("0\n");
	return 0;
}
