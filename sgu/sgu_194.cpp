#include <stdio.h>
#include <string.h>
#define maxn 210
int st[maxn],aim[100000],link[100000],ln;
int l[maxn][maxn],u[maxn][maxn];
int edge[100000][2];
int con[maxn][maxn];
int stack[maxn],a[maxn],next[maxn],level[maxn];
int tot;
int n,m,source,remit;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
void bfs(){
	int i,p,an;
	memset(level,0,sizeof(level));
	level[source]=1;
	an=1;a[0]=source;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i])
			if (!level[aim[i]] && con[a[p]][aim[i]]>0) level[aim[i]]=level[a[p]]+1,a[an++]=aim[i];
}
void dfs(){
	int i,k,stn,min,minp;
	next[source]=st[source];
	stn=1;stack[1]=source;
	while (stn>0){
		k=stack[stn];
		if (k==remit){
			min=10000000;
			for (i=stn-1;i>0;i--)
				if (con[stack[i]][stack[i+1]]<min) min=con[stack[i]][stack[i+1]];
			for (i=stn-1;i>0;i--){
				con[stack[i]][stack[i+1]]-=min;
				con[stack[i+1]][stack[i]]+=min;
				if (con[stack[i]][stack[i+1]]==0) minp=i;
			}
			stn=minp;
			tot-=min;
			continue;
		}
		for (i=next[k];i!=-1;i=link[i])
			if (level[aim[i]]==level[k]+1 && con[k][aim[i]]>0){
				stack[++stn]=aim[i];
				next[aim[i]]=st[aim[i]];
				break;
			}
		if (i==-1) level[k]=n<<2,stn--;
	}
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	source=0;remit=n+1;
	ln=0;
	memset(st,-1,sizeof(st));
	memset(con,0,sizeof(con));
	for (i=1;i<=n;i++){
		in_edge(source,i);
		in_edge(i,remit);
	}
	tot=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		edge[i][0]=j;
		edge[i][1]=k;
		scanf("%d %d",&l[j][k],&u[j][k]);
		in_edge(j,k);
		in_edge(k,j);
		con[j][k]=u[j][k]-l[j][k];
		con[source][k]+=l[j][k];
		con[j][remit]+=l[j][k];
		tot+=l[j][k];
	}
	while (1){
		bfs();
		if (!level[remit]) break;
		dfs();
	}
	if (tot==0){
		printf("YES\n");
		for (i=0;i<m;i++) printf("%d\n",l[edge[i][0]][edge[i][1]]+con[edge[i][1]][edge[i][0]]);
	}else printf("NO\n");
	return 0;
}
