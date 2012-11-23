#include <stdio.h>
#include <string.h>
#define maxn 1010
int a[maxn];
int b[10][2],bn;
int n,m;
int Find(int x){
	for (int i=x;i<n;i++)
		if (a[i]==2) return i;
	return n;
}
int Pre(int x){
	for (int i=x-1;i>=0;i--)
		if (a[i]==0) return i;
	return -1;
}
void Change(int x,int y){
	a[x]+=y;
	b[bn][0]=x;
	b[bn++][1]=a[x];
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	memset(a,0,sizeof(a));
	int p;
	for (scanf("%d",&m);m>0;m--){
		scanf("%d",&p);
		i=Find(p);
		j=Pre(i);
		bn=0;
		if (p>=j){
			if (i<n){
				Change(i+1,1);
				if (p==i) Change(p,-1);else{
					Change(i,-2);
					Change(p,1);
				}
			}else{
				Change(p,1);
			}
		}else
		if (a[p]==1){
			if (p<n-1){
				Change(p+1,1);
				Change(p,-1);
			}else{
				Change(p,1);
			}
		}else Change(p,1);
		printf("%d ",bn);
		for (i=0;i<bn;i++) printf("%d %d ",b[i][0],b[i][1]);
		printf("\n");
	}
	return 0;
}
