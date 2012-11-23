#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long long ll;

ll f[19][170][1010];
ll g[19][170][1010];
ll pow[20];
int a[20],b[20],an,bn;
int m;
pair<ll,ll> merge(pair<ll,ll> a,pair<ll,ll> b){
	pair<ll,ll> c;
	c.first=a.first+b.first;
	c.second=b.second;
	return c;
}
pair<ll,ll> calc(int tl,int tr,int N,int tot,int v){
	if (tl==0 && tr==0) return make_pair(f[N][tot][v],g[N][tot][v]);
	if (N==1){
		int st=(tl==0?0:a[N-1]);
		int en=(tr==0?9:b[N-1]);
		int rv=0;
		for (int i=st;i<=en;i++){
			v+=tot+i;
			if (v>=m){
				++rv;
				v=0;
			}
		}
		return make_pair(rv,v);
	}
	if (tr==0){
		int st=a[N-1],en=10;
		pair<ll,ll> ret=calc(1,0,N-1,tot+st,v),tmp;
		for (int i=st+1;i<en;i++){
			tmp=calc(0,0,N-1,tot+i,ret.second);
			ret=merge(ret,tmp);
		}
		return ret;
	}else
	if (tl==0){
		int st=0,en=b[N-1];
		if (st==en) return calc(0,1,N-1,tot,v);
		pair<ll,ll> ret=calc(0,0,N-1,tot,v),tmp;
		for (int i=1;i<en;i++){
			tmp=calc(0,0,N-1,tot+i,ret.second);
			ret=merge(ret,tmp);
		}
		tmp=calc(0,1,N-1,tot+en,ret.second);
		ret=merge(ret,tmp);
		return ret;
	}else{
		int st=a[N-1],en=b[N-1];
		if (st==en) return calc(1,1,N-1,tot+st,v);
		pair<ll,ll> ret=calc(1,0,N-1,tot+st,v),tmp;
		for (int i=st+1;i<en;i++){
			tmp=calc(0,0,N-1,tot+i,ret.second);
			ret=merge(ret,tmp);
		}
		tmp=calc(0,1,N-1,tot+en,ret.second);
		ret=merge(ret,tmp);
		return ret;
	}
}
int main(){
	ll l,r;
	scanf("%I64d%I64d%d",&l,&r,&m);
	pow[0]=1;
	for (int i=1;i<20;i++) pow[i]=pow[i-1]*10;
	for (int j=1;j<=17*9;j++)
		for (int k=0;k<m;k++){
			f[1][j][k]=0;
			int v=k;
			for (int i=0;i<10;i++){
				v+=j+i;
				if (v>=m){
					++f[1][j][k];
					v=0;
				}
			}
			g[1][j][k]=v;
		}
	for (int i=2;i<=18;i++)
		for (int j=1;j<=(18-i)*9;j++)
			for (int k=0;k<m;k++){
				int v=k;
				for (int c=0;c<10;c++){
					f[i][j][k]+=f[i-1][j+c][v];
					v=g[i-1][j+c][v];
				}
				g[i][j][k]=v;
			}
	an=bn=0;
	while (l){
		a[an++]=l%10;
		l/=10;
	}
	while (r){
		b[bn++]=r%10;
		r/=10;
	}
	pair<ll,ll> ans=calc(1,1,max(an,bn),0,0);
	ll ANS=ans.first;
//	if (ans.second) ++ANS;
	printf("%I64d\n",ANS);
	return 0;
}
