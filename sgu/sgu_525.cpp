#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 20010
int st[maxn],aim[maxm],link[maxm],ln;
int e[maxm][2];
/*int id[maxn],scnt,time,low[maxn];
int stack[maxn],stn;*/
int g[maxn][maxn];
int a[maxn],an,tag[maxn];
int d[maxm];
int n,m;
int ans,ansp;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
/*void dfs(int x){
	int min,i;
	min=low[x]=time++;
	stack[++stn]=x;
	for (i=st[x];i!=-1;i=link[i])
		if (low[aim[i]]==-1){
			dfs(aim[i]);
			if (low[aim[i]]<min) min=low[aim[i]];
		}else
		if (low[aim[i]]<min) min=low[aim[i]];
	if (min<low[x]){
		low[x]=min;
		return;
	}
	do{
		i=stack[stn--];
		id[i]=scnt;
		low[i]=n<<1;
	}while (i!=x);
	scnt++;
}*/
void bfs(int x){
	int i,p;
	memset(tag,0,sizeof(tag));
	an=1;a[0]=x;tag[x]=1;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i])
			if (!tag[aim[i]]){
				tag[aim[i]]=1;
				a[an++]=aim[i];
			}
	for (i=0;i<an;i++) g[x][a[i]]=1;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		e[i][0]=j;
		e[i][1]=k;
	}
	if (m==0){
		printf("1\n0\n");
		return 0;
	}
	/*memset(id,-1,sizeof(id));
	memset(low,-1,sizeof(low));
	scnt=time=0;
	for (i=1;i<=n;i++)
		if (low[i]==-1){
			stn=0;
			dfs(i);
		}
	for (i=1;i<=n;i++) printf("%d ",id[i]);*/
	memset(g,0,sizeof(g));
	for (i=1;i<=n;i++) bfs(i);
	/*for (i=1;i<=n;i++){
		for (j=1;j<=n;j++) printf("%d ",g[i][j]);printf("\n");
	}*/
	ans=ansp=0;
	for (i=0;i<m;i++){
		d[i]=0;
		for (j=1;j<=n;j++)
			if (g[e[i][0]][j] && g[j][e[i][1]]) d[i]++;
		if (d[i]>ans){
			ans=d[i];
			ansp=1;
		}else
		if (d[i]==ans) ansp++;
	}
	printf("%d\n%d\n",ans,ansp);
	for (i=0;i<m;i++)
		if (d[i]==ans) printf("%d ",i+1);
	printf("\n");
	return 0;
}
