#include <stdio.h>
#include <string.h>
#define maxn 510
int a[maxn][maxn];
int tag[maxn],link[maxn];
int n;

int dfs(int x,int bound){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=1;i<=n;i++)
		if (a[x][i]<=bound)
			if (link[i]==-1 || dfs(link[i],bound)){
				link[i]=x;
				return 1;
			}
	return 0;
}

int check(int limit){
	int i;
	memset(link,-1,sizeof(link));
	memset(tag,0,sizeof(tag));
	for (i=1;i<=n;i++)
		if (dfs(i,limit)){
			memset(tag,0,sizeof(tag));
		}else return 0;
	return 1;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	int l,r,m;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
			if (i==1 && j==1) l=r=a[i][j];else{
				if (a[i][j]<l) l=a[i][j];
				if (a[i][j]>r) r=a[i][j];
			}
		}
	while (l<=r){
		m=(l+r)/2;
		if (check(m)) r=m-1;else l=m+1;
	}
	printf("%d\n",r+1);
	k=check(r+1);
	for (i=1;i<=n;i++) printf("%d %d\n",link[i],i);
	return 0;
}
