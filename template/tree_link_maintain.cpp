#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 50010
#define bln 200

using namespace std;

int mod;
struct block{
	int len;
	int list[bln+1];
	int v[bln+1],mv[bln+1];
	int tsum;
	block *nxt;
	block(){
		len=0;mv[0]=1;
		tsum=0;nxt=NULL;
	}
	void pr(){
		puts("-----------");
		for (int i=1;i<=len;i++) printf("%d ",list[i]);puts("");
		puts("-----------");
	}
};
block *llink[maxn];								//存结点属于的块
int st[maxn],aim[maxn<<1],nxt[maxn<<1],ln;		//边表
int plink[maxn];								//节点在块中的位置
int belong[maxn],size[maxn],lt[maxn];			//树的根,大小
int tp[maxn][17];								//从每个节点向上走2^i步到达的节点
int w[maxn];									//节点的权
int level[maxn];								//节点的深度
int n,m,logn;
int ans,ansv;
int value;

void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}

void updata(block *x){				//将块的信息处理一次
	sort(x->v+1,x->v+x->len+1);
	x->mv[0]=1;
	for (int i=1;i<=x->len;i++) x->mv[i]=(x->mv[i-1]*x->v[i])%mod;
}

void ins(block *cur,int x){			//在块cur后加入一个元素x
	if (cur->len==bln){
		block *tmp=new block();
		cur->nxt=tmp;
		updata(cur);
		cur=tmp;
	}
	cur->len++;
	cur->list[cur->len]=x;
	cur->v[cur->len]=w[x];
	plink[x]=cur->len;
	llink[x]=cur;
}

void init(){						//预处理
	logn=1;
	while ((1<<logn)<=n) logn++;
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=1;i<=n;i++){
		for (int j=0;j<logn;j++) tp[i][j]=-1;
		belong[i]=i;
		size[i]=1;
		lt[i]=level[i]=0;
		llink[i]=new block();
		ins(llink[i],i);
		llink[i]->mv[1]=w[i]%mod;
	}
}

void dfs(int fx,int x){				//dfs遍历一棵树
	belong[x]=belong[fx];
	level[x]=level[fx]+1;
	//预处理tp
	tp[x][0]=fx;
	for (int i=1;i<logn;i++)
		if (tp[x][i-1]!=-1) tp[x][i]=tp[tp[x][i-1]][i-1];else tp[x][i]=-1;
	if (plink[x]==1) delete llink[x];
	size[x]=1;
	int tz=-1,p=-1;
	for (int i=st[x];i!=-1;i=nxt[i])
		if (aim[i]!=fx){
			dfs(x,aim[i]);
			size[x]+=size[aim[i]];
			if (size[aim[i]]>tz){
				tz=size[aim[i]];
				p=aim[i];
			}
		}
	lt[x]=0;
	if (p==-1){
		llink[x]=new block();
		ins(llink[x],x);
	}else{
		lt[x]=p;
		for (int i=st[x];i!=-1;i=nxt[i])
			if (aim[i]!=fx && aim[i]!=p) updata(llink[aim[i]]);
		ins(llink[p],x);
	}
}

void split(block *x,int p){			//将一个块从第p个位置切成两个块
	if (p==1) return;
	block *cur=new block();
	for (int i=p;i<=x->len;i++){
		int k=x->list[i];
		size[k]+=x->tsum;
		ins(cur,k);
	}
	x->len=p-1;
	for (int i=1;i<p;i++) x->v[i]=w[x->list[i]];
	cur->nxt=x->nxt;
	x->nxt=NULL;
	updata(x);
	updata(cur);
}

inline int SZ(int x){
	return x==0?0:size[x]+llink[x]->tsum;
}

void Combine(block *x,block *y){
	x->nxt=y->nxt;
	for (int i=1;i<=y->len;i++) ins(x,y->list[i]);
	updata(x);
}

void to_top(int x,int t){			//将x为根的树向上更新,重新划分
	while (1){
		if (tp[x][0]==-1) return;
		int fx=tp[x][0];
		if (SZ(x)>SZ(lt[fx])){		//将轻边改成重边
			lt[fx]=x;
			split(llink[fx],plink[fx]);
			llink[x]->nxt=llink[fx];
		}
		block *tmp=llink[fx];
		tmp->tsum+=t;
		while (tmp->nxt!=NULL){
			tmp=tmp->nxt;
			tmp->tsum+=t;
		}
		x=tmp->list[tmp->len];
	}
}

void change(int p,int x){			//将第p个点的权改为x
	for (int i=1;i<=llink[p]->len;i++)
		if (llink[p]->v[i]==w[p]){
			llink[p]->v[i]=x;
			break;
		}
	updata(llink[p]);
	w[p]=x;
}

int lca(int x,int y){				//求x,y的lca
	if (level[x]<level[y]) swap(x,y);
	for (int i=logn-1;i>=0;i--)
		if (level[x]-(1<<i)>=level[y]) x=tp[x][i];
	if (x==y) return x;
	for (int i=logn-1;i>=0;i--)
		if (tp[x][i]!=tp[y][i]){
			x=tp[x][i];
			y=tp[y][i];
		}
	return tp[x][0];
}

inline void check(int x){
	if (x<=value){
		ans++;
		ansv=(ansv*x)%mod;
	}
}

int Find(block *x){
	int ret=0;
	if (x->v[1]>value) return 0;
	int L=1,R=x->len,mid;
	while (L<=R){
		mid=(L+R)>>1;
		if (x->v[mid]<=value){
			L=mid+1;
			ret=mid;
		}else R=mid-1;
	}
	return ret;
}

void go(int x,int y){
	while (1){
		if (llink[x]==llink[y]){
			while (x!=y){			check(w[x]);x=tp[x][0];		}
			return;
		}else{
			if (plink[x]==1){
				int p=Find(llink[x]);
				ans+=p;
				ansv=(ansv*llink[x]->mv[p])%mod;
			}else{
				for (int i=plink[x];i<=llink[x]->len;i++) check(w[llink[x]->list[i]]);
			}
			int dx=llink[x]->list[llink[x]->len];
			x=tp[dx][0];
		}
	}
}

void work(int x,int y){
	ans=0;ansv=1;
	if (belong[x]!=belong[y]) return;
	int z=lca(x,y);
	go(x,z);go(y,z);
	check(w[z]);
}

int main(){
	while (scanf("%d%d%d",&n,&m,&mod)!=EOF){
		for (int i=1;i<=n;i++) scanf("%d",w+i);
		init();
		for (int t=0;t<m;t++){
			int type;
			scanf("%d",&type);
			if (type==1){
				int x,y;
				scanf("%d%d",&x,&y);
				if (belong[x]==belong[y]) continue;
				if (SZ(belong[x])<SZ(belong[y])) swap(x,y);	//启发式合并
				in_edge(x,y);
				in_edge(y,x);
				dfs(x,y);
				updata(llink[y]);
				to_top(y,size[y]);
			}else
			if (type==2){
				int x,v;
				scanf("%d%d",&x,&v);
				change(x,v);
			}else{
				int x,y;
				scanf("%d%d%d",&x,&y,&value);
				work(x,y);
				if (ans==0){puts("0");}else{printf("%d %d\n",ans,ansv);}
			}
		}
		for (int i=1;i<=n;i++)
			if (plink[i]==1) delete llink[i];
	}
	return 0;
}