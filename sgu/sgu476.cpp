#include <stdio.h>
#include <string.h>
#define maxn 1010
typedef long long LL;
int a[maxn][3];
int tag[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) scanf("%d%d%d",&a[i][0],&a[i][1],&a[i][2]);
	memset(tag,-1,sizeof(tag));
	return 0;
}
