#include <stdio.h>
#define maxn 200
int n,m,ans;
int f(int x,int y){
	int res=1,i;
	for (i=0;i<y;i++) res*=x;
	return res;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	ans=0;
	for (i=0;i<n;i++){
		scanf("%d",&k);
		if (m==2 || k>0) ans+=f(k,m);
	}
	printf("%d\n",ans);
	return 0;
}
