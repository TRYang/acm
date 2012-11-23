#include <stdio.h>
#include <string.h>
#define maxn 1010
int x[maxn],ans[maxn];
int tot;
int n,m,y;
int labs(int x){return x>0?x:-x;}
int f(int i){
	return labs(m*x[i]-y*(ans[i]+1))-labs(m*x[i]-y*ans[i]);
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&y);
	for (i=0;i<n;i++) scanf("%d",x+i);
	for (i=0;i<n;i++) ans[i]=(m*x[i])/y;
	tot=0;
	for (i=0;i<n;i++) tot+=ans[i];
	while (tot<m){
		k=-1;
		for (i=0;i<n;i++)
			if (k==-1 || f(i)<f(k)) k=i;
		ans[k]++;
		tot++;
	}
	for (i=0;i<n;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
