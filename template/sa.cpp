#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int sa[maxn],rank[maxn],height[maxn];
int c[maxn],wx[maxn],wy[maxn],wv[maxn];
int st[20][maxn];
int LOG[maxn];

inline int cmp(int *r,int x,int y,int l){
	return r[x]==r[y] && r[x+l]==r[y+l];
}
void Make_SA(int n,int m){
	int *x=wx,*y=wy;
	for (int i=0;i<m;i++) c[i]=0;
	for (int i=0;i<n;i++) c[x[i]=s[i]]++;
	for (int i=1;i<m;i++) c[i]+=c[i-1];
	for (int i=n-1;i>=0;i--) sa[--c[s[i]]]=i;
	for (int len=1,p;len<n;len<<=1,m=p){
		p=0;
		for (int i=n-len;i<n;i++) y[p++]=i;
		for (int i=0;i<n;i++)
			if (sa[i]>=len) y[p++]=sa[i]-len;
		for (int i=0;i<n;i++) wv[i]=x[y[i]];
		for (int i=0;i<m;i++) c[i]=0;
		for (int i=0;i<n;i++) c[wv[i]]++;
		for (int i=1;i<m;i++) c[i]+=c[i-1];
		for (int i=n-1;i>=0;i--) sa[--c[wv[i]]]=y[i];
		swap(x,y);
		p=1;x[sa[0]]=0;
		for (int i=1;i<n;i++)
			x[sa[i]]= cmp(y,sa[i-1],sa[i],len) ? p-1 : p++;
	}
	for (int i=0;i<n;i++) rank[sa[i]]=i;
	//calculate height
	for (int i=0,k=0;i<n;i++)
		if (rank[i]>0){
			for (int j=sa[rank[i]-1];i+k<n && j+k<n && s[i+k]==s[j+k];k++);
			height[rank[i]]=k;
			if (k>0) k--;
		}else height[0]=0;
}
//prepare for rmq
void Make_st(int n){
	LOG[1]=0;
	for (int i=2,k=1;i<=n;i++){
		if ((1<<(k+1))<=i) k++;
		LOG[i]=k;
	}
	for (int i=0;i<n;i++) st[0][i]=height[i];
	for (int j=1;j<=LOG[n];j++)
		for (int i=0;i<n;i++)
			if (i+(1<<(j-1))<n) 
				st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
			else
				st[j][i]=n<<1;
}
inline int qst(int x,int y){
	if (x>y) return -1;
	int k=LOG[y-x+1];
	return min(st[k][x],st[k][y-(1<<k)+1]);
}
//return the longest common part of the suffix x and the suffix y
inline int lcp(int x,int y){
	if (rank[x]>rank[y]) swap(x,y);
	return qst(rank[x]+1,rank[y]);
}
