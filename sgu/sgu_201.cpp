#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 30
#define kk 10000

struct bignum{
	int l,v[50];
	friend bignum operator + (const bignum &x,const bignum &y){
		bignum res;
		res.l=x.l;
		if (y.l>res.l) res.l=y.l;
		memset(res.v,0,sizeof(res.v));
		int i;
		for (i=0;i<res.l;i++) res.v[i]=x.v[i]+y.v[i];
		for (i=0;i<res.l;i++)
			if (res.v[i]>=kk) res.v[i+1]++,res.v[i]-=kk;
		if (res.v[res.l]>0) res.l++;
		return res;
	}
	void pr(){
		printf("%d",v[l-1]);
		for (int i=l-2;i>=0;i--){
			if (v[i]<1000) printf("0");
			if (v[i]<100) printf("0");
			if (v[i]<10) printf("0");
			printf("%d",v[i]);
		}
		printf("\n");
	}
};
char s[30];
int n,m;
int N;
int st;
int tn,t[maxn];
int g[maxn][maxm],d[maxn][maxm];
int tag[maxn];
int a[maxn][maxm];
bignum f[maxn][62];
int flag[maxn][62];
int q[2][maxn],qn[2],now,next,p;
bignum ans;

int dfs(int x,int y){
	if (tag[x]) return -1;
	tag[x]=1;
	int res= d[x][y]==0 ? g[x][y] : dfs(g[x][y],y);
	tag[x]=0;
	return res;
}

bignum ch(int x){
	bignum res;
	res.l=1;
	memset(res.v,0,sizeof(res.v));
	res.v[0]=x;
	return res;
}

void updata(int x,int y,bignum v){
	if (!flag[x][y]){
		flag[x][y]=1;
		q[next][qn[next]++]=x;
		f[x][y]=ch(0);
	}
	f[x][y]=f[x][y]+v;
}

int main(){
	int i,j,k;
	scanf("%s",s);
	m=strlen(s);
	scanf("%d",&n);
	scanf("%d %d",&st,&tn);
	for (i=0;i<tn;i++) scanf("%d",t+i);
	for (i=1;i<=n;i++)
		for (j=0;j<m;j++) scanf("%d",&g[i][j]);
	for (i=1;i<=n;i++)
		for (j=0;j<m;j++) scanf("%d",&d[i][j]);
	scanf("%d",&N);
	memset(tag,0,sizeof(tag));
	for (i=1;i<=n;i++)
		for (j=0;j<m;j++) a[i][j]=dfs(i,j);
	memset(flag,0,sizeof(flag));
	flag[st][0]=1;
	f[st][0]=ch(1);
	now=0;
	qn[0]=1;q[0][0]=st;
	for (k=0;k<N;k++){
		next=now^1;
		qn[next]=0;
		for (i=0;i<qn[now];i++){
			p=q[now][i];
			for (j=0;j<m;j++)
				if (a[p][j]>-1) updata(a[p][j],k+1,f[p][k]);
		}
		now=next;
	}
	ans=ch(0);
	for (i=0;i<tn;i++)
		if (flag[t[i]][N]) ans=ans+f[t[i]][N];
	ans.pr();
	return 0;
}
