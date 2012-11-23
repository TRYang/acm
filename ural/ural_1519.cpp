#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 15
#define hashsize 10131
#define maxcnt 30000

using namespace std;

typedef long long LL;

struct hashtable{
	int st[hashsize],nxt[maxcnt],hn;
	LL num[maxcnt];
	int pos[maxcnt];
	void clear(){
		hn=0;
		memset(st,-1,sizeof(st));
	}
	int find(LL x){
		LL v=x%hashsize;
		for (int i=st[v];i!=-1;i=nxt[i])
			if (num[i]==x) return pos[i];
		return -1;
	}
	void insert(LL x,int P){
		LL v=x%hashsize;
		num[hn]=x;
		pos[hn]=P;
		nxt[hn]=st[v];
		st[v]=hn++;
	}
} hash[2];
struct node{
	LL st,v;
};
char board[maxn][maxn];
node q[2][maxcnt];
int qn[2];
int b[maxn],c[maxn];
int n,m;
LL Encode(int *a){
	LL ret=0;
	for (int i=0;i<=m;i++) ret=ret*(m+1)+a[i];
	return ret;
}
void Decode(int *a,LL x){
	for (int i=m;i>=0;i--){
		a[i]=x%(m+1);
		x/=(m+1);
	}
}
void insert(int p,LL st,LL v){
	int dp=hash[p].find(st);
	if (dp==-1){
		hash[p].insert(st,qn[p]);
		dp=qn[p];
		q[p][qn[p]].st=st;
		q[p][qn[p]++].v=0;
	}
	q[p][dp].v+=v;
}
void merge(int *a,int x,int y){
	for (int i=0;i<=m;i++)
		if (a[i]==x) a[i]=y;
}
int tag[maxn];
void relabel(int *a){
	memset(tag,-1,sizeof(tag));
	int tot=0;
	for (int i=0;i<=m;i++)
		if (a[i]){
			if (tag[a[i]]==-1) tag[a[i]]=++tot;
			a[i]=tag[a[i]];
		}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",board[i]);
	int now=0,next,left=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) left+=(board[i][j]=='.');
	qn[0]=1;	q[0][0].st=0;q[0][0].v=1;
	for (int i=0;i<n && left;i++){
		next=now^1;
		qn[next]=0;
		hash[next].clear();
		for (int p=0;p<qn[now];p++){
			LL st=q[now][p].st,v=q[now][p].v;
			Decode(b,st);
			if (b[m]) continue;
			insert(next,st/(m+1),v);
		}
		now=next;
		
		for (int j=0;j<m && left;j++){
			next=now^1;
			qn[next]=0;
			hash[next].clear();
			if (board[i][j]=='.') left--;
			for (int p=0;p<qn[now];p++){
				LL st=q[now][p].st,v=q[now][p].v;
				
				Decode(b,st);
				if (board[i][j]=='*'){
					if (b[j]>0 || b[j+1]>0) continue;
					insert(next,st,v);
				}else{
					if (b[j]>0 && b[j+1]>0){//两个连通块
						if (b[j]!=b[j+1]){//合并不同的连通块
							merge(b,b[j],b[j+1]);
							b[j]=b[j+1]=0;
							relabel(b);
							insert(next,Encode(b),v);
						}else
						if (left==0){//最后一格可以封闭
							b[j]=b[j+1]=0;
							insert(next,Encode(b),v);
						}
					}else
					if (b[j]>0 || b[j+1]>0){//一个连通块
						insert(next,st,v);
						swap(b[j],b[j+1]);
						insert(next,Encode(b),v);
					}else{					//木有连通块
						b[j]=b[j+1]=m;
						relabel(b);
						insert(next,Encode(b),v);
					}
				}
			}
			now=next;
		}
	}
	LL ans=0;
	for (int p=0;p<qn[now];p++)
		if (q[now][p].st==0) ans=q[now][p].v;
	printf("%lld\n",ans);
	return 0;
}