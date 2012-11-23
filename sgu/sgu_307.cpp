#include <stdio.h>
#include <string.h>
#define maxn 1210
int st[maxn],aim[maxn*maxn],link[maxn*maxn],ln;
int a[310][310],b[310][310];
int v[310][310],tv[310][310];
int id[maxn],scnt;
int stack[maxn],stn;
int low[maxn],Time;
int x[maxn],y[maxn];
int pv[maxn];
int N;
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
void dfs(int x){
	int min,i;
	min=low[x]=++Time;
	stack[++stn]=x;
	for (i=st[x];i!=-1;i=link[i])
		if (low[aim[i]]==-1){
			dfs(aim[i]);
			if (low[aim[i]]<min) min=low[aim[i]];
		}else
		if (low[aim[i]]<min) min=low[aim[i]];
	if (min<low[aim[i]]){
		low[aim[i]]=min;
		return;
	}
	do{
		i=stack[stn--];
		low[i]=N<<2;
		id[i]=scnt;
	}while (i!=x);
	scnt++;
}
int check(int kx){
	int i,j,k;
	memset(tv,0,sizeof(tv));
	for (i=2;i<=n;i++)
		for (j=2;j<=m;j++)
			if ((i+j)%2==0) tv[i][j]=tv[i-1][j]+b[i][j];else tv[i][j]=tv[i-1][j]-b[i][j];
	memset(v,0,sizeof(v));
	for (i=2;i<=n;i++)
		for (j=2;j<=m;j++) v[i][j]=v[i][j-1]+tv[i][j];
	ln=0;
	memset(st,-1,sizeof(st));
	N=0;
	for (i=2;i<=n;i++) x[i]=N++;
	for (j=2;j<=m;j++) y[j]=N++;
	for (i=2;i<=n;i++)
		for (j=2;j<=m;j++){
			int tot= (i+j)%2==0 ? -kx+v[i][j] : kx-v[i][j];
			int s1= i%2==0 ? -1 : 1;
			int s2= j%2==0 ? -1 : 1;
			//printf("%d \n",tot);
			k=0;
			for (int vi=0;vi<2;vi++)
				for (int vj=0;vj<2;vj++)
					if (tot+s1*vi+s2*vj<2 && tot+s1*vi+s2*vj>-1){
						k=1;
						if (tot+s1*vi+s2*(vj^1)>1 || tot+s1*vi+s2*(vj^1)<0) in_edge(vi*N+x[i],vj*N+y[i]);
						if (tot+s1*(vi^1)+s2*vj>1 || tot+s1*(vi^1)+s2*vj<0) in_edge(vj*N+y[i],vi*N+x[i]);
					}
			if (!k) return 0;
			for (int vi=0;vi<2;vi++){
				k=0;
				for (int vj=0;vj<2;vj++)
					if (tot+s1*vi+s2*vj<2 && tot+s1*vi+s2*vj>-1) k=1;
				if (!k) in_edge(vi*N+x[i],(vi^1)*N+x[i]);
			}
			for (int vj=0;vj<2;vj++){
				k=0;
				for (int vi=0;vi<2;vi++)
					if (tot+s1*vi+s2*vj<2 && tot+s1*vi+s2*vj>-1) k=1;
				if (!k) in_edge(vj*N+y[j],(vj^1)*N+y[j]);
			}
		}
	memset(low,-1,sizeof(low));
	Time=stn=scnt=0;
	for (i=0;i<N<<1;i++)
		if (low[i]==-1) dfs(i);
	for (i=0;i<N;i++)
		if (id[i]==id[N+i]) return 0;
	
	return 1;
}
int main(){
	int i,j,k;
	freopen("test.txt","r",stdin);
	scanf("%d %d",&n,&m);
	for (i=2;i<=n;i++){
		char s[maxn];
		scanf("%s",s);
		for (j=0;j<m-1;j++) b[i][j+2]=s[j]-'0';
	}
	for (k=0;k<2;k++)
		if (check(k)) break;
	if (k==2) printf("CORRUPT\n");
	return 0;
}
