#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#define maxn 2010
#define P 41

using namespace std;

typedef unsigned long long LLU;

LLU POW[maxn];
LLU h[2][maxn],dh[2][maxn];
char s[2][maxn];
int n,m;
void Make(int p){
	int len=strlen(s[p]);
	h[p][0]=0;
	for (int i=0;i<len;i++){
		h[p][i+1]=h[p][i]*P+s[p][i]-'a';
	}
	dh[p][len]=0;
	for (int i=len-1;i>=0;i--){
		dh[p][i]=dh[p][i+1]*P+s[p][i]-'a';
	}
}
set<LLU> st;
int stp,enp;
int check(int l){
	if (l>n || l>m) return 0;
	st.clear();
	for (int i=0;i+l<=n;i++){
		LLU v1=h[0][i+l]-h[0][i]*POW[l];
		LLU v2=dh[0][i]-dh[0][i+l]*POW[l];
		if (v1==v2) st.insert(v1);
	}
	for (int i=0;i+l<=m;i++){
		LLU v1=h[1][i+l]-h[1][i]*POW[l];
		LLU v2=dh[1][i]-dh[1][i+l]*POW[l];
		if (v1==v2 && st.find(v1)!=st.end()){
			stp=i;
			enp=i+l;
			return 1;
		}
	}
	return 0;
}
int main(){
	POW[0]=1;
	for (int i=1;i<maxn;i++) POW[i]=POW[i-1]*P;
	scanf("%s%s",s[0],s[1]);
	Make(0);
	Make(1);
	n=strlen(s[0]);
	m=strlen(s[1]);
	int L,R,mid;
	int ans=0;
	L=0;R=min(n,m)/2;
	while (L<=R){
		mid=(L+R)>>1;
		if (check(mid<<1)){
			L=mid+1;
			ans=(mid<<1);
		}else R=mid-1;
	}
	L=0;R=min(n,m)/2;
	while (L<=R){
		mid=(L+R)>>1;
		if (check((mid<<1)+1)){
			L=mid+1;
			ans=max(ans,(mid<<1)+1);
		}else R=mid-1;
	}
//	printf("%d\n",ans);
	check(ans);
	for (int i=stp;i<enp;i++) printf("%c",s[1][i]);
	puts("");
	return 0;
}
