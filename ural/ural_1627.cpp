#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10
#define mod 1000000000
#define hashsize 4001
#define maxcnt 20000

using namespace std;

struct hashtablt{
	int st[hashsize],hn;
	int nxt[maxcnt],value[maxcnt],pos[maxcnt];
	void clear(){
		hn=0;
		memset(st,-1,sizeof(st));
	}
	int find(int x){
		for (int i=st[x%hashsize];i!=-1;i=nxt[i])
			if (value[i]==x) return pos[i];
		return -1;
	}
	void insert(int x,int P){
		int v=x%hashsize;
		value[hn]=x;
		pos[hn]=P;
		nxt[hn]=st[v];
		st[v]=hn++;
	}
} hash[2];
pair<int,int> q[2][maxcnt];
int qn[2];
int a[maxn],num[maxn];
char board[maxn][maxn];
int n,m;
int Encode(int *a){
	int ret=0;
	for (int i=0;i<m;i++) ret=ret*(m+1)+a[i];
	return ret;
}
void Decode(int *a,int value){
	memset(num,0,sizeof(num));
	for (int i=m-1;i>=0;i--){
		num[a[i]=value%(m+1)]++;
		value/=m+1;
	}
}
int tag[maxn];
void Relabel(int *a){
	memset(tag,-1,sizeof(tag));
	for (int i=0,tot=0;i<m;i++)
		if (a[i]){
			if (tag[a[i]]==-1) tag[a[i]]=++tot;
			a[i]=tag[a[i]];
		}
}
void insert(int p,int st,int v){
	int dp=hash[p].find(st);
	if (dp==-1){
		hash[p].insert(st,qn[p]);
		q[p][qn[p]++]=make_pair(st,v);
	}else{
		q[p][dp].second+=v;
		q[p][dp].second%=mod;
	}
}
inline void merge(int *a,int x,int y){
	for (int i=0;i<m;i++)
		if (a[i]==y) a[i]=x;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",board[i]);
	int left=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) left+=(board[i][j]=='.');
	int now=0,next;
	qn[0]=1;
	q[0][0]=make_pair(0,1);
	for (int i=0;i<n && left;i++)
		for (int j=0;j<m && left;j++){
			next=now^1;
			qn[next]=0;
			hash[next].clear();
			left-=(board[i][j]=='.');
			for (int p=0;p<qn[now];p++){
				int st=q[now][p].first,v=q[now][p].second;
				if (board[i][j]=='.'){
					Decode(a,st);
					int b1=(j==0)?0:a[j-1],b2=a[j];
					if (b1 && b2 && b1!=b2){
						merge(a,b1,b2);
						Relabel(a);
						insert(next,Encode(a),v);
						Decode(a,st);
					}
					if (b1 && (!b2 || num[b2]>1)){
						a[j]=b1;
						Relabel(a);
						insert(next,Encode(a),v);
						Decode(a,st);
					}
					if (b2) insert(next,st,v);
					if (!b2 || num[b2]>1){
						a[j]=m+1;
						Relabel(a);
						insert(next,Encode(a),v);
					}
				}else{
					Decode(a,st);
					if (a[j]==0) insert(next,st,v);else
					if (num[a[j]]>1){
						a[j]=0;
						Relabel(a);
						insert(next,Encode(a),v);
					}
				}
			}
			now=next;
		}
	int ans=0;
	for (int p=0;p<qn[now];p++){
		int st=q[now][p].first;
		Decode(a,st);
		int tag=0;
		for (int i=0;i<m;i++)
			if (a[i]==1) tag=1;
		for (int i=0;i<m;i++)
			if (a[i]>1) tag=0;
		if (tag) ans=(ans+q[now][p].second)%mod;
	}
	printf("%d\n",ans);
	return 0;
}