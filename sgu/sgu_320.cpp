#include <stdio.h>
#include <string.h>
#define maxn 510
#define maxN 250010
#define maxm 1002010
const int mx[4]={1,0,-1,0};
const int my[4]={0,1,0,-1};
int st[maxN],aim[maxm],link[maxm],ln;
char s[maxn][maxn];
int a[maxn][maxn];
int tot[maxN];
int low[maxN],Time;
int stack[maxN],stn;
int q[maxN][2];
int n;
int cn,cm,K;
int ans;
inline int Move(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<cn && y>=0 && y<cm;
}
void floodfill(int sx,int sy){
	int i,p,qn=1;
	q[0][0]=sx;
	q[0][1]=sy;
	a[sx][sy]=n;
	for (p=0;p<qn;p++){
		int x=q[p][0],y=q[p][1];
		for (i=0;i<4;i++)
			if (Move(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				if (a[tx][ty]==-1 && s[tx][ty]==s[sx][sy]){
					a[tx][ty]=n;
					q[qn][0]=tx;
					q[qn++][1]=ty;
				}
			}
	}
	tot[n++]=qn;
}
inline void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
void dfs(int fx,int x){
	if (tot[x]>=K) ans+=tot[x];
	int mint,i,flag=0,p;
	mint=low[x]=++Time;
	stack[++stn]=x;
	for (i=st[x];i!=-1;i=link[i])
		if (aim[i]!=fx){
			if (!low[aim[i]]){
				dfs(x,aim[i]);
				if (low[aim[i]]>=low[x] && tot[x]>=K){
					do{
						p=stack[stn--];
						if (tot[p]<K) ans+=tot[p];
					}while (p!=aim[i]);
				}
			}
			if (low[aim[i]]<mint) mint=low[aim[i]];
		}
	if (mint<low[x]) low[x]=mint;
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&cn,&cm,&K);
	for (i=0;i<cn;i++) scanf("%s",s[i]);
	memset(a,-1,sizeof(a));
	n=0;
	for (i=0;i<cn;i++)
		for (j=0;j<cm;j++)
			if (a[i][j]==-1) floodfill(i,j);
	// for (i=0;i<cn;i++){
		// for (j=0;j<cm;j++) printf("%d ",a[i][j]);
		// printf("\n");
	// }
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<cn;i++)
		for (j=0;j<cm;j++){
			for (k=0;k<4;k++)
				if (Move(i,j,k)){
					int tx=i+mx[k],ty=j+my[k];
					if (a[tx][ty]!=a[i][j]) in_edge(a[i][j],a[tx][ty]);
				}
			if (i==0 || i==cn-1 || j==0 || j==cm-1){
				in_edge(n,a[i][j]);
				in_edge(a[i][j],n);
			}
		}
	Time=1;
	memset(low,0,sizeof(low));
	ans=0;
	low[n]=1;
	for (i=st[n];i!=-1;i=link[i])
		if (!low[aim[i]]){
			stn=0;
			dfs(n,aim[i]);
		}
	printf("%d\n",ans);
	return 0;
}