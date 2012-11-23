#include <stdio.h>
#include <string.h>
#define maxn 10010
int st[maxn],aim[maxn<<1],nxt[maxn<<1],ln;
int father[maxn];
int tag[maxn];
int n;
int Find(int x){return father[x]= father[x]==x?x:Find(father[x]);}
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int f[maxn],g[maxn],h[maxn];
int tot[maxn];
int q[maxn];
int bfs(int sp){
	int qn=1;
	tag[sp]=1;
	q[0]=sp;
	for (int p=0;p<qn;p++)
		for (int i=st[q[p]];i!=-1;i=nxt[i])
			if (!tag[aim[i]]){
				tag[aim[i]]=1;
				q[qn++]=aim[i];
			}
	for (int p=qn-1;p>=0;p--){
		int k=q[p];
		tag[k]=0;
		f[k]=g[k]=0;
		tot[k]=0;
		for (int i=st[k];i!=-1;i=nxt[i])
			if (!tag[aim[i]]){
				if (f[aim[i]]+1>2) tot[k]++;
				if (f[aim[i]]+1>f[k]){
					g[k]=f[k];
					f[k]=f[aim[i]]+1;
					h[k]=aim[i];
				}else
				if (f[aim[i]]+1>g[k]){
					g[k]=f[aim[i]]+1;
				}
			}
	}
	for (int p=0;p<qn;p++){
		int k=q[p];
		tag[k]=1;
		if (tot[k]>2) return 0;
		for (int i=st[k];i!=-1;i=nxt[i])
			if (!tag[aim[i]]){
				int u=aim[i];
				if (h[k]==u){
					if (g[k]+1>f[u]){
						g[u]=f[u];
						f[u]=g[k]+1;
						h[u]=k;
					}else
					if (g[k]+1>g[u]){
						g[u]=g[k]+1;
					}
					if (g[k]+1>2) tot[u]++;
				}else{
					if (f[k]+1>f[u]){
						g[u]=f[u];
						f[u]=f[k]+1;
						h[u]=k;
					}else
					if (f[k]+1>g[u]){
						g[u]=f[k]+1;
					}
					if (f[k]+1>2) tot[u]++;
				}
			}
	}
	return 1;
}
int check(){
	memset(st,-1,sizeof(st));
	ln=0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) father[i]=i;
	while (1){
		int u,v;
		scanf("%d%d",&u,&v);
		if (!u && !v) break;
		if (Find(u)==Find(v)) return 0;
		father[Find(u)]=Find(v);
		in_edge(u,v);
		in_edge(v,u);
	}
	memset(tag,0,sizeof(tag));
	for (int i=1;i<=n;i++)
		if (!tag[i] && !bfs(i)) return 0;
	return 1;
}
int main(){
	puts(check()?"KILLED":"ESCAPED");
	return 0;
}