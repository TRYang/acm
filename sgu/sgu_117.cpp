#include <stdio.h>
int n,m,K,ans,p;
int f(int x){
	if (x==1) return p%K;
	if ((x&1)==1) return (f(x-1)*p)%K;else{
		int tmp=f(x>>1);
		return (tmp*tmp)%K;
	}
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&K);
	for (i=ans=0;i<n;i++){
		scanf("%d",&p);
		if (f(m)==0) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
