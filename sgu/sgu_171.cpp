#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxm 110
#define maxn 16010

using namespace std;

int need[maxm],q[maxm],f[maxm],c[maxm];
int p[maxn],w[maxn],b[maxn],ans[maxn];
int n,m;
bool cmp1(int x,int y){
	return q[x]<q[y];
}
bool cmp2(int x,int y){
	return (w[x]>w[y]) || (w[x]==w[y] && p[x]<p[y]);
}
int ask(int x){
	int l=0,r=m-1,mid,res=-1;
	while (l<=r){
		mid=(l+r)>>1;
		if (q[c[mid]]<x){
			l=mid+1;
			res=mid;
		}else r=mid-1;
	}
	return res;
}
int find(int x){return f[x]= f[x]==x ? x : find(f[x]);}
int main(){
	int i,j,k;
	scanf("%d",&m);
	for (n=i=0;i<m;i++){
		scanf("%d",need+i);
		n+=need[i];
		c[i]=i;
	}
	for (i=0;i<m;i++) scanf("%d",q+i);
	sort(c,c+m,cmp1);
	for (i=0;i<n;i++) scanf("%d",p+i);
	for (i=0;i<n;i++) scanf("%d",w+i);	
	for (i=0;i<n;i++) b[i]=i;
	sort(b,b+n,cmp2);
	for (i=0;i<m;i++) f[i]=i;
	memset(ans,-1,sizeof(ans));
	for (i=0;i<n;i++){
		k=ask(p[b[i]]);
		if (k>-1){
			j=find(k);
			if (need[c[j]]>0){
				ans[b[i]]=c[j];
				need[c[j]]--;
				if (need[c[j]]==0) f[j]=find(j-1);
			}
		}
	}
	k=0;
	while (k<m && need[k]==0) k++;
	for (i=0;i<n;i++)
		if (ans[i]==-1){
			ans[i]=k;
			need[k]--;
			while (k<m && need[k]==0) k++;
		}
	for (i=0;i<n;i++) printf("%d ",ans[i]+1);printf("\n");
	return 0;
}
