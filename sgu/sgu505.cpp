#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 200010

using namespace std;

struct trie{
	int tn;
	int nxt[maxn][26];
	int tot[maxn];
	int pos[maxn];
	void init(){
		tn=1;
		memset(nxt,0,sizeof(nxt));
		memset(tot,0,sizeof(tot));
	}
	void insert(char *s,int len){
		int k=0;
		for (int i=0;i<len;k=nxt[k][s[i++]-'a']){
			int c=s[i]-'a';
			if (nxt[k][c]==0) nxt[k][c]=tn++;
		}
	}
	void finish(){
		for (int i=tn-1;i>=0;i--){
			tot[i]=1;
			for (int j=0;j<26;j++)
				if (nxt[i][j]) tot[i]+=tot[nxt[i][j]];
		}
		pos[0]=0;
		for (int i=0;i<tn;i++){
			int sum=pos[i]+1;
			for (int j=0;j<26;j++)
				if (nxt[i][j]){
					pos[nxt[i][j]]=sum;
					sum+=tot[nxt[i][j]];
				}
		}
	}
	int get(char *s,int len){
		int k=0;
		for (int i=0;i<len;k=nxt[k][s[i++]-'a']);
		return pos[k];
	}
	pair<int,int> find(char *s,int len){
		int k=0;
		for (int i=0;i<len;k=nxt[k][s[i++]-'a']){
			int c=s[i]-'a';
			if (nxt[k][c]==0) return make_pair(-1,-1);
		}
		return make_pair(pos[k],pos[k]+tot[k]-1);
	}
} prefix,suffix;

struct node{
	int x,y;
	friend bool operator < (const node &a,const node &b){
		return a.x<b.x;
	}
} a[maxn];

struct query{
	int x,sy,ty,id;
	int value;
	query(){}
	query(int _x,pair<int,int> yy,int _id,int v){
		x=_x;
		id=_id;
		sy=yy.first;
		ty=yy.second;
		value=v;
	}
	friend bool operator < (const query &a,const query &b){
		return a.x<b.x;
	}
} q[maxn<<1];
int ta[maxn];
int ans[maxn];
char s[maxn];
int stp[maxn];
int n,m;
int N;
int qn;
void ins(int p){
	for (;p<=N;p+=(p&(p^(p-1)))) ta[p]++;
}
int ask(int p){
	int ret=0;
	for (;p;p-=(p&(p^(p-1)))) ret+=ta[p];
	return ret;
}
inline int get_range(int l,int r){
	return ask(r)-ask(l-1);
}
int main(){
	char buf[maxn];
	scanf("%d",&n);
	prefix.init();
	suffix.init();
	for (int i=0,tot=0;i<n;i++){
		scanf("%s",buf);
		int len=strlen(buf);

		stp[i]=tot;
		for (int j=0;j<len;j++) s[tot+j]=buf[j];
		tot+=len;

		prefix.insert(buf,len);
		reverse(buf,buf+len);
		suffix.insert(buf,len);
		
		if (i==n-1) stp[i+1]=tot;
	}
	prefix.finish();
	suffix.finish();
	for (int i=0;i<n;i++){
		a[i].x=prefix.get(s+stp[i],stp[i+1]-stp[i]);
		reverse(s+stp[i],s+stp[i+1]);
		a[i].y=suffix.get(s+stp[i],stp[i+1]-stp[i]);
	}
	scanf("%d",&m);
	qn=0;
	for (int i=0;i<m;i++){
		scanf("%s",buf);
		int len=strlen(buf);
		pair<int,int> x=prefix.find(buf,len);

		scanf("%s",buf);
		len=strlen(buf);
		reverse(buf,buf+len);
		pair<int,int> y=suffix.find(buf,len);

		if (x.first==-1 || y.first==-1) continue;
		q[qn++]=query(x.first-1,y,i,-1);
		q[qn++]=query(x.second,y,i,1);
	}
	sort(a,a+n);
	sort(q,q+qn);
	memset(ta,0,sizeof(ta));
	N=suffix.tn;
	int tp=0;
	for (int i=0;i<qn;i++){
		while (tp<n && a[tp].x<=q[i].x){
			ins(a[tp].y);
			++tp;
		}
		int k=q[i].id;
		ans[k]+=q[i].value*get_range(q[i].sy,q[i].ty);
	}
	for (int i=0;i<m;i++) printf("%d\n",ans[i]);
	return 0;
}
