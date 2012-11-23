#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int maxn=110;
int idx[maxn];
int T[maxn],L[maxn];
int st[maxn];
int n;
bool cmp(int x,int y){
	return L[x]>L[y] || (L[x]==L[y] && T[x]<T[y]);
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",T+i);
	for (int i=0;i<n;i++) scanf("%d",L+i);
	for (int i=0;i<n;i++) idx[i]=i;
	sort(idx,idx+n,cmp);
	int p=0;
	for (int i=0;i<n;i++){
		p+=T[idx[i]];
		st[idx[i]]=p;
	}
	int ans=0;
	for (int i=0;i<n;i++) ans=max(ans,st[i]+L[i]);
	printf("%d\n",ans);
	return 0;
}
