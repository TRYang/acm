#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

struct node{
	int first,second,fp;
	void init(){
		first=second=0;
		fp=-1;
	}
	void insert(int value,int p){
		if (value>first){
			second=first;
			first=value;
			fp=p;
		}else
		if (value>second) second=value;
	}
} f[maxn];
int st1[maxn],aim1[maxn<<1],nxt1[maxn<<1],ln1;
int len1[maxn<<1],cost1[maxn<<1],id1[maxn<<1];

int st[maxn],aim[maxn<<1],nxt[maxn<<1],ln;
int len[maxn<<1],cost[maxn<<1],id[maxn<<1];
int n;
int maxlen;
void in_edge1(int x,int y,int l,int c,int d){
	aim1[ln1]=y;
	nxt1[ln1]=st1[x];
	len1[ln1]=l;
	cost1[ln1]=c;
	id1[ln1]=d;
	st1[x]=ln1++;
}
void in_edge(int x,int y,int l,int c,int d){
	aim[ln]=y;
	nxt[ln]=st[x];
	len[ln]=l;
	cost[ln]=c;
	id[ln]=d;
	st[x]=ln++;
}
int q[maxn];
int tag[maxn];
int ans,ansp[maxn];
int g[maxn];
int w[maxn],cw[maxn];
void dp(int u,int v){
	w[u]=2000000000;
	for (int i=st[u];i!=-1;i=nxt[i])
		if (aim[i]==v){
			w[u]=cost[i];
			cw[u]=id[i];
		}
	int qn=1;
	memset(tag,0,sizeof(tag));
	q[0]=u;
	tag[u]=1;
	if (v>-1) tag[v]=1;
	for (int p=0;p<qn;p++)
		for (int i=st[q[p]];i!=-1;i=nxt[i])
			if (!tag[aim[i]]){
				w[aim[i]]=cost[i];
				cw[aim[i]]=id[i];
				tag[aim[i]]=1;
				q[qn++]=aim[i];
			}
	for (int p=qn-1;p>=0;p--){
		int k=q[p];
		tag[k]=0;
		g[k]=0;
		for (int i=st[k];i!=-1;i=nxt[i])
			if (!tag[aim[i]]){
				int v=aim[i];
				g[k]+=g[v];
			}
		if (g[k]==0) g[k]=w[k];else g[k]=min(g[k],w[k]);
	}
	if (g[u]==0) return;
	int bbb=-1;
	if (v==-1){
		int maxg=-1;
		for (int i=st[u];i!=-1;i=nxt[i])
			if (g[aim[i]]>maxg){
				maxg=g[aim[i]];
				bbb=aim[i];
			}
		g[u]-=maxg;		
	}
	if (ans==-1 || g[u]<ans){
		ans=g[u];
		ansp[0]=0;
		qn=1;
		q[0]=u;
		for (int p=0;p<qn;p++){
			int k=q[p];
			if (g[k]==w[k]){
				ansp[++ansp[0]]=cw[k];
			}else{
				for (int i=st[k];i!=-1;i=nxt[i])
					if (!tag[aim[i]] && aim[i]!=bbb){
						tag[aim[i]]=1;
						q[qn++]=aim[i];
					}
			}
		}
	}
}
void work(){
	int qn=1;
	q[0]=1;
	tag[1]=1;
	for (int p=0;p<qn;p++)
		for (int i=st1[q[p]];i!=-1;i=nxt1[i])
			if (!tag[aim1[i]]) tag[aim1[i]]=1,q[qn++]=aim1[i];
	for (int p=qn-1;p>=0;p--){
		int k=q[p];
		tag[k]=0;
		f[k].init();
		for (int i=st1[k];i!=-1;i=nxt1[i])
			if (!tag[aim1[i]]){
				int v=aim1[i];
				f[k].insert(f[v].first+len1[i],v);
			}
	}
	for (int p=0;p<qn;p++){
		int k=q[p];
		tag[k]=1;
		for (int i=st1[k];i!=-1;i=nxt1[i])
			if (!tag[aim1[i]]){
				int v=aim1[i];
				if (f[k].fp==v)
					f[v].insert(f[k].second+len1[i],k);
				else
					f[v].insert(f[k].first+len1[i],k);
			}
	}
	maxlen=0;
	for (int i=1;i<=n;i++) maxlen=max(maxlen,f[i].first+f[i].second);
	memset(st,-1,sizeof(st));
	ln=0;
	int center=-1;
	int x=-1,y=-1;
/*	for (int i=1;i<=n;i++){
		printf("%d %d %d\n",f[i].first,f[i].fp,f[i].second);
	}*/
	for (int i=1;i<=n;i++){
		if ((maxlen&1)==0 && f[i].first==f[i].second && f[i].first==(maxlen>>1)) center=i;
		for (int j=st1[i];j!=-1;j=nxt1[j]){
			int v=aim1[j];
			int l=len1[j],l1=(f[i].fp==v?f[i].second:f[i].first),l2=(f[v].fp==i?f[v].second:f[v].first);
//			if (i==1 && v==2) printf("%d %d %d\n",l,l1,l2);
			if (l+l1+l2==maxlen){
				in_edge(i,v,len1[j],cost1[j],id1[j]);
				if (l1<((maxlen+1)>>1) && l2<((maxlen+1)>>1)){
					x=i;
					y=v;
				}
			}
		}
	}
	ans=-1;
	if (center==-1){
		dp(x,y);
		dp(y,x);
	}else dp(center,-1);
}
int main(){
	memset(st1,-1,sizeof(st1));
	ln1=0;
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v,t,pr;
		scanf("%d%d%d%d",&u,&v,&t,&pr);
		in_edge1(u,v,t,pr,i);
		in_edge1(v,u,t,pr,i);
	}
	work();
	printf("%d\n",ans);
	printf("%d\n",ansp[0]);
	for (int i=1;i<=ansp[0];i++){
		printf("%d",ansp[i]);
		if (i<ansp[0]) printf(" ");
	}
	puts("");
	return 0;
}
