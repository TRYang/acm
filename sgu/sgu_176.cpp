#include <stdio.h>
#include <string.h>
#define maxn 210
#define maxm 100000
int edge[maxm][2],z[maxm],c[maxm];
int st[maxn],aim[maxm],link[maxm],ln;
int con[maxn][maxn];
int a[maxn],level[maxn],next[maxn],stack[maxn];
int source,remit;
int n,m,ans;
int maxflow,tot;

void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}

void bfs(){
	int i,p,an;
	memset(level,0,sizeof(level));
	an=1;a[0]=source;
	level[source]=1;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i])
			if (level[aim[i]]==0 && con[a[p]][aim[i]]){
				level[aim[i]]=level[a[p]]+1;
				a[an++]=aim[i];
			}
}

void dfs(){
	int i,k,stn,min,minp;
	stn=1;
	stack[1]=source;
	next[source]=st[source];
	while (stn>0){
		k=stack[stn];
		if (k==remit){
			min=100000000;
			for (i=1;i<stn;i++)
				if (con[stack[i]][stack[i+1]]<min) min=con[stack[i]][stack[i+1]];
			for (i=stn-1;i>0;i--){
				con[stack[i]][stack[i+1]]-=min;
				con[stack[i+1]][stack[i]]+=min;
				if (con[stack[i]][stack[i+1]]==0) minp=i;
			}
			maxflow+=min;
			stn=minp;
			continue;
		}
		for (i=next[k];i!=-1;i=link[i])
			if (level[aim[i]]==level[k]+1 && con[k][aim[i]]>0){
				next[k]=link[i];
				next[aim[i]]=st[aim[i]];
				stack[++stn]=aim[i];
				break;
			}
		if (i==-1){
			level[k]=n<<1;
			stn--;
		}
	}
}

int check(int x){
	int i,j,k;
	z[m]=x;
	memset(con,0,sizeof(con));
	tot=0;
	for (i=0;i<=m;i++)
		if (c[i]){
			con[source][edge[i][1]]+=z[i];
			con[edge[i][0]][remit]+=z[i];
			tot+=z[i];
		}else{
			con[edge[i][0]][edge[i][1]]=z[i];
		}
	maxflow=0;
	while (1){
		bfs();
		if (!level[remit]) break;
		dfs();
	}
	//if (x==3) printf("%d\n",maxflow);
	return maxflow==tot;
}

int main(){
	int i,j,k;
	int l=0,r=1000000,mid;
	scanf("%d %d",&n,&m);
	ln=0;
	memset(st,-1,sizeof(st));
	source=n+1;
	remit=source+1;
	for (i=0;i<m;i++){
		scanf("%d %d %d %d",&edge[i][0],&edge[i][1],z+i,c+i);
		if (c[i]){
			in_edge(source,edge[i][1]);
			in_edge(edge[i][0],remit);
		}else{
			in_edge(edge[i][0],edge[i][1]);
			in_edge(edge[i][1],edge[i][0]);
		}
	}
	c[m]=0;
	edge[m][0]=n;
	edge[m][1]=1;
	in_edge(n,1);
	in_edge(1,n);
	ans=-1;
	while (l<=r){
		mid=(l+r)>>1;
		if (check(mid)){
			r=mid-1;
			ans=mid;
		}else l=mid+1;
	}
	if (ans==-1) printf("Impossible\n");else{
		check(ans);
		printf("%d\n",ans);
		for (i=0;i<m;i++){
			if (!c[i]) printf("%d",con[edge[i][1]][edge[i][0]]);else printf("%d",z[i]);
			if (i<m-1) printf(" ");else printf("\n");
		}
	}
	return 0;
}
