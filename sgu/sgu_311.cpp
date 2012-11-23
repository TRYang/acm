#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

typedef long long LL;

LL tot[maxn<<2],tp[maxn<<2];//segment tree
int dt[maxn<<2];
int type[maxn],c[maxn];
LL t[maxn];
int x[maxn],xn;
int n,m;
char s[100];
void push_down(int p){
	dt[p<<1]=1;
	dt[(p<<1)+1]=1;
	tot[p]=tp[p]=dt[p]=0;
}
void push_up(int p){
	tot[p]=tp[p]=0;
	if (!dt[p<<1]){
		tot[p]+=tot[p<<1];
		tp[p]+=tp[p<<1];
	}
	if (!dt[(p<<1)+1]){
		tot[p]+=tot[(p<<1)+1];
		tp[p]+=tp[(p<<1)+1];
	}
}
void Ins(int p,int tl,int tr,int k,int v){
	if (tl==tr){
		if (dt[p]){
			dt[p]=0;
			tot[p]=tp[p]=0;
		}
		tot[p]+=v;
		tp[p]+=(LL)x[tl-1]*v;
		return;
	}
	if (dt[p]) push_down(p);
	int m=(tl+tr)>>1;
	if (k<=m) Ins(p<<1,tl,m,k,v);else Ins((p<<1)+1,m+1,tr,k,v);
	push_up(p);
}
void Del(int p,int tl,int tr,int ct){
	if (tl==tr){
		tot[p]-=ct;
		tp[p]-=(LL)ct*(LL)x[tl-1];
		return;
	}
	if (dt[p]) push_down(p);
	if (tot[p]==ct){
		dt[p]=1;
		return;
	}
	int m=(tl+tr)>>1;
	if (dt[p<<1]) tot[p<<1]=tp[p<<1]=0;
	if (tot[p<<1]>=ct) Del(p<<1,tl,m,ct);else{
		Del((p<<1)+1,m+1,tr,ct-tot[p<<1]);
		dt[p<<1]=1;
	}
	push_up(p);
}
LL query(int p,int tl,int tr,int ct){
	if (dt[p]){
		if (tl<tr) push_down(p);
		tot[p]=tp[p]=0;
	}
	if (tot[p]<ct) return -1;
	if (tot[p]==ct) return tp[p];
	if (ct==0) return 0;
	if (tl==tr) return (LL)ct*(LL)x[tl-1];
	int m=(tl+tr)>>1;
	if (dt[p<<1]) tot[p<<1]=tp[p<<1]=0;
	LL res;
	return tot[p<<1]>=ct ? query(p<<1,tl,m,ct) : query((p<<1)+1,m+1,tr,ct-tot[p<<1]) + tp[p<<1];
}
int main(){
	int i,j,k;
	m=0;
	while (gets(s)){
		if (s[0]=='A') type[m]=0;else type[m]=1;
		int len=strlen(s);
		if (len==0) break;
		for (i=0;i<len && s[i]!=' ';i++);
		c[m]=0;
		for (i++;i<len && s[i]!=' ';i++) c[m]=c[m]*10+s[i]-'0';
		t[m]=0;
		for (i++;i<len && s[i]!=' ';i++) t[m]=t[m]*10+s[i]-'0';
		m++;
	}
	xn=0;
	for (i=0;i<m;i++)
		if (!type[i]) x[xn++]=t[i];
	sort(x,x+xn);
	xn=unique(x,x+xn)-x;
	for (i=0;i<m;i++)
		if (type[i]){
			LL s=query(1,1,xn,c[i]);
//			printf("%lld\n",s);
			if (s>-1 && s<=t[i]){
				printf("HAPPY\n");
				Del(1,1,xn,c[i]);
			}else printf("UNHAPPY\n");
		}else{
			t[i]=upper_bound(x,x+xn,t[i])-x;
			Ins(1,1,xn,t[i],c[i]);
		}
	return 0;
}
