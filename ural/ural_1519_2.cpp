#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 15
#define hashsize 8107
#define maxcnt 20000

using namespace std;

typedef long long LL;

struct hashtable{
	int st[hashsize],nxt[maxcnt],hn;
	int value[maxcnt],pos[maxcnt];
	void clear(){
		hn=0;
		memset(st,-1,sizeof(st));
	}
	int find(int x){
		int v=x%hashsize;
		for (int i=st[v];i!=-1;i=nxt[i])
			if (value[i]==x) return pos[i];
		return -1;
	}
	void insert(LL mask,int P){
		int v=mask%hashsize;
		value[hn]=mask;
		pos[hn]=P;
		nxt[hn]=st[v];
		st[v]=hn++;
	}
} hash[2];
pair<int,LL> q[2][maxcnt];
int qn[2];
char board[maxn][maxn];
int n,m;
inline int two(int x){return 1<<x;}
inline int Bit(int p){return 3<<(p<<1);}
inline int getBit(int mask,int p){return (mask>>(p<<1))&3;}
inline int rv(int mask,int p){return mask&((two(m+1<<1)-1)^(3<<(p<<1)));}
inline int ins(int mask,int v,int p){return mask|(v<<(p<<1));}
inline int chl(int mask,int p){
	for (int i=p,stn=0,k;i<=m;i++){
		k=getBit(mask,i);
		if (k==1) stn++;
		if (k==2) stn--;
		if (stn==-1) return ins(rv(mask,i),1,i);
	}
}
inline int chr(int mask,int p){
	for (int i=p,stn=0,k;i>=0;i--){
		k=getBit(mask,i);
		if (k==2) stn++;
		if (k==1) stn--;
		if (stn==-1) return ins(rv(mask,i),2,i);
	}
}
void insert(int p,int mask,LL v){
	int dp=hash[p].find(mask);
	if (dp==-1){
		hash[p].insert(mask,qn[p]);
		q[p][qn[p]++]=make_pair(mask,v);
	}else q[p][dp].second+=v;
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
	for (int i=0;i<n && left;i++){
		
		for (int j=0;j<m && left;j++){
			left-=(board[i][j]=='.');
			next=now^1;
			hash[next].clear();
			qn[next]=0;
			// printf("---------------(%d,%d)-----------\n",i,j);
			for (int p=0;p<qn[now];p++){
				int st=q[now][p].first;
				LL v=q[now][p].second;
				if (j==0){
					if (getBit(st,m)) continue;
					st<<=2;
				}
				// for (int c=0;c<=m;c++) printf("%d ",getBit(st,c));puts("");
				if (board[i][j]=='.'){
					int c1=getBit(st,j),c2=getBit(st,j+1);
					if (c1>0 && c2>0){
						int tst=rv(rv(st,j),j+1);
						if (c1==1 && c2==2){
							if (left==0) insert(next,tst,v);
						}else
						if (c1==2 && c2==1){
							insert(next,tst,v);
						}else
						if (c1==1 && c2==1){
							insert(next,chl(tst,j+2),v);
						}else{
							insert(next,chr(tst,j-1),v);
						}
					}else
					if (c1>0 || c2>0){
						insert(next,st,v);
						if (c1>0)
							insert(next,ins(rv(st,j),c1,j+1),v);
						else
							insert(next,ins(rv(st,j+1),c2,j),v);
					}else{
						insert(next,ins(ins(st,1,j),2,j+1),v);
					}
				}else{
					if (getBit(st,j)>0 || getBit(st,j+1)>0) continue;
					insert(next,st,v);
				}
			}
			now=next;
		}
	}
	LL ans=0;
	for (int p=0;p<qn[now];p++)
		if (q[now][p].first==0) ans=q[now][p].second;
	printf("%lld\n",ans);
	return 0;
}