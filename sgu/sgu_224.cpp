#include <stdio.h>
int t[25];
int n,m,ans;

void dfs(int x,int p,int ty,int ta,int tb){
	if (p==0){
		ans++;
		return;
	}
	if (n-x<p) return;
	dfs(x+1,p,ty,ta,tb);
	for (int i=0;i<n;i++)
		if ((ty&t[i])==0 && (ta&t[i+x])==0 && (tb&t[x+n-i-1])==0)
			dfs(x+1,p-1,ty|t[i],ta|t[i+x],tb|t[x+n-i-1]);
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	if (m>n){
		printf("0\n");
	}else{
		t[0]=1;
		for (i=1;i<25;i++) t[i]=t[i-1]<<1;
		ans=0;
		dfs(0,m,0,0,0);
		printf("%d\n",ans);
	}
	return 0;
}
