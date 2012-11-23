#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 50010
int st[maxn],aim[maxm],nxt[maxm],w[maxm],ln;
int danger[maxn];
int low[maxn],Time;
int stack[maxn],stn;
int tot[maxn],id[maxn],scnt;
int q[maxn];
int n,m;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	nxt[ln]=st[x];
	w[ln]=z;
	st[x]=ln++;
}
void dfs(int x){
	int mint;
	stack[++stn]=x;
	mint=low[x]=++Time;
	for (int i=st[x];i!=-1;i=nxt[i]){
		if (w[i]>0) continue;
		if (low[aim[i]]==-1) dfs(aim[i]);
		if (low[aim[i]]<mint) mint=low[aim[i]];
	}
	if (mint==low[x]){
		tot[scnt]=0;
		int i;
		do{
			i=stack[stn--];
			low[i]=n<<3;
			id[i]=scnt;
			tot[scnt]++;
		}while (i!=x);
		++scnt;
	}else low[x]=mint;
}
int main(){
	scanf("%d%d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		if (u==v){
			if (w==0) danger[u]=1;
			continue;
		}
		in_edge(u,v,w);
	}
	memset(low,-1,sizeof(low));
	Time=scnt=stn=0;
	for (int i=1;i<=n;i++)
		if (low[i]==-1) dfs(i);
	for (int i=1;i<=n;i++)
		if (tot[id[i]]>1) danger[i]=1;
	int qn=0;
	for (int i=1;i<=n;i++)
		if (danger[i]) q[qn++]=i;
	for (int p=0;p<qn;p++){
		int u=q[p];
		for (int i=st[u];i!=-1;i=nxt[i])
			if (!danger[aim[i]]){
				danger[aim[i]]=1;
				q[qn++]=aim[i];
			}
	}
	for (int i=1;i<=n;i++) puts(danger[i]?"0":"1");
	return 0;
}