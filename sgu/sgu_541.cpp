#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

int st1[maxn],aim1[maxn<<1],nxt1[maxn<<1],ln1;
int st[maxn],aim[maxn<<1],nxt[maxn<<1],ln;
int d[maxn];
int deg[maxn],nd[maxn];
int q[maxn],qn;
int tag[maxn<<1],vis[maxn];
int belong[maxn];
int n,m;
int sp,tp;
int vs;
void in_edge1(int x,int y){
	d[x]++;
	aim1[ln1]=y;
	nxt1[ln1]=st1[x];
	st1[x]=ln1++;
}
void in_edge(int x,int y){
	// printf("%d %d\n",x,y);
	deg[y]++;
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
	
	aim[ln]=x;
	nxt[ln]=st[y];
	st[y]=ln++;
}
void go(int x,int fx){
	// printf("%d %d:\n",x,fx);
	while (d[x]<4){
		belong[x]=fx;
		for (int i=st1[x];i!=-1;i=nxt1[i])
			if (!tag[i]){
				tag[i]=tag[i^1]=1;
				in_edge(x,aim1[i]);
				x=aim1[i];
				break;
			}
	}
	if (!vis[x]){
		vis[x]=1;
		q[qn++]=x;
	}
}
int f[maxn][3][3];
int h[3][3];
int ans;
#define check(x,y) (x==0 || y==0 || x!=y)
void calc(int x){
	if (x==tp){
		int root=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1){
				root=belong[aim[i]];
				break;
			}
		int p1=-1,p2=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]==root)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		for (int k=0;k<3;k++)
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++)
					if (f[p1][i][k]>-1 && f[p2][j][k]>-1){
						for (int c=0;c<3;c++)
							if (check(i,c) && check(j,c))
								f[x][c][c]=max(f[x][c][c],f[p1][i][k]+f[p2][j][k]-f[root][k][k]+(c>0));
					}
		for (int i=0;i<3;i++)
			for (int j=0;j<3;j++) h[i][j]=f[x][i][j];
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]!=root){
				root=belong[aim[i]];
				break;
			}
		p1=-1;p2=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]==root)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		for (int c=0;c<3;c++)
			if (f[x][c][c]>-1){
				int delta=-1;
				for (int k=0;k<3;k++)
					for (int i=0;i<3;i++)
						for (int j=0;j<3;j++)
							if (f[p1][i][k]>-1 && f[p2][j][k]>-1 && check(i,c) && check(j,c))
								delta=max(delta,f[p1][i][k]+f[p2][j][k]-f[root][k][k]);
				if (delta>-1){
					f[x][c][c]+=delta;
					f[x][c][c]-=(vs>0);
				}else f[x][c][c]=-1;
			}
	}else
	if (vis[x]){
		int p1=-1,p2=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		int root=belong[p1];
		for (int k=0;k<3;k++)
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++)
					if (f[p1][i][k]>-1 && f[p2][j][k]>-1){
						for (int c=0;c<3;c++)
							if (check(i,c) && check(j,c))
								f[x][c][c]=max(f[x][c][c],f[p1][i][k]+f[p2][j][k]-f[root][k][k]+(c>0));
					}
	}else{
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1){
				int v=aim[i];
				for (int j=0;j<3;j++)
					for (int k=0;k<3;k++)
						if (f[v][j][k]>-1){
							for (int c=0;c<3;c++)
								if (check(j,c))
									f[x][c][k]=max(f[x][c][k],f[v][j][k]+(c>0));
						}
			}
	}
}
void gao(int x){
	for (int i=st[x];i!=-1;i=nxt[i]){
		if (i&1) continue;
		int v=aim[i];
		nd[v]++;
		if (deg[v]==nd[v]){
			calc(v);
			q[qn++]=v;
		}
	}
}
int mark[maxn];
void pre_find(int x,int c,int z){
	if (vis[x]) return;
	while (!vis[x]){
		mark[x]=c;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1){
				int v=aim[i];
				for (int j=0;j<3;j++)
					if (f[v][j][z]>-1 && check(j,c) && f[v][j][z]+(c>0)==f[x][c][z]){
						x=v;
						c=j;
						break;
					}
			}
	}
}
void Find(int x,int y){
	mark[x]=y;
	if (x==tp){
		int p1=-1,p2=-1;
		int root=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1){
				root=belong[aim[i]];
				break;
			}
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]==root)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		int flag=0;
		for (int k=0;k<3 && !flag;k++)
			for (int i=0;i<3 && !flag;i++)
				for (int j=0;j<3 && !flag;j++)
					if (f[p1][i][k]>-1 && f[p2][j][k]>-1 && check(i,y) && check(j,y))
						if (f[p1][i][k]+f[p2][j][k]-f[root][k][k]+(y>0)==h[y][y]){
							Find(root,k);
							pre_find(p1,i,k);
							pre_find(p2,j,k);
							flag=1;
							break;
						}
						
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]!=root){
				root=belong[aim[i]];
				break;
			}
		p1=-1;p2=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if ((i&1)>0 && belong[aim[i]]==root)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		for (int k=0;k<3;k++)
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++)
					if (f[p1][i][k]>-1 && f[p2][j][k]>-1 && check(i,y) && check(j,y))
						if (f[p1][i][k]+f[p2][j][k]-f[root][k][k]+h[y][y]-(vs>0)==f[tp][y][y]){
							Find(root,k);
							pre_find(p1,i,k);
							pre_find(p2,j,k);
							return;
						}
	}else{
		int p1=-1,p2=-1;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (i&1)
				if (p1==-1) p1=aim[i];else p2=aim[i];
		int root=belong[p1];
		for (int k=0;k<3;k++)
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++)
					if (f[p1][i][k]>-1 && f[p2][j][k]>-1 && check(i,y) && check(j,y))
						if (f[p1][i][k]+f[p2][j][k]-f[root][k][k]+(y>0)==f[x][y][y]){
							Find(root,k);
							pre_find(p1,i,k);
							pre_find(p2,j,k);
							return;
						}
	}
}
void pr(int x){
	int tot=0;
	for (int i=1;i<=n;i++)
		if (mark[i]==x) ++tot;
	printf("%d",tot);
	for (int i=1;i<=n;i++)
		if (mark[i]==x) printf(" %d",i);
	puts("");
}
void build(){
	qn=1;
	q[0]=sp;
	memset(vis,0,sizeof(vis));
	memset(tag,0,sizeof(tag));
	vis[sp]=1;
	memset(st,-1,sizeof(st));
	ln=0;
	for (int p=0;p<qn;p++){
		belong[q[p]]=q[p];
		for (int i=st1[q[p]];i!=-1;i=nxt1[i])
			if (!tag[i]){
				tag[i]=tag[i^1]=1;
				in_edge(q[p],aim1[i]);
				go(aim1[i],q[p]);
			}
	}
	tp=q[qn-1];
	ans=0;
	for (vs=0;vs<3;vs++){
		memset(f,-1,sizeof(f));
		memset(nd,0,sizeof(nd));
		qn=1;
		q[0]=sp;
		f[sp][vs][vs]=(vs>0);
		for (int p=0;p<qn;p++) gao(q[p]);
		int tmp=-1;
		for (int i=0;i<3;i++) tmp=max(tmp,f[tp][i][i]);
		if (tmp>ans){
			ans=tmp;
			memset(mark,0,sizeof(mark));
			mark[0]=vs;
			for (int i=0;i<3;i++)
				if (f[tp][i][i]==tmp){
					Find(tp,i);
					break;
				}
		}
	}
	pr(1);
	pr(2);
}
int main(){
	scanf("%d%d",&n,&m);
	memset(st1,-1,sizeof(st1));
	ln1=0;
	for (int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		in_edge1(u,v);
		in_edge1(v,u);
	}
	for (int i=1;i<=n;i++)
		if (d[i]==4){
			sp=i;
			break;
		}
	build();
	return 0;
}