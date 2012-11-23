#include <stdio.h>
#define maxn 20
int t[25];
int s[1<<maxn];
int n,m;

int G(int x,int N){
	int i,k=0,res=0;
	for (i=N-1;i>=0;i--)
		if (x>=t[i]){
			if (!k){
				res|=t[i];
				k=1;
			}
			x-=t[i];
		}else{
			if (k){
				res|=t[i];
				k=0;
			}
		}
	return res;
}

int main(){
	int i,j,k;
	t[0]=1;
	for (i=1;i<25;i++) t[i]=t[i-1]<<1;
	scanf("%d %d",&n,&m);
	for (i=0;i<t[m];i++){
		s[i]=G(i,m)<<n;
		printf("%d ",s[i]);
	}
	printf("\n");
	for (i=1;i<t[n];i++){
		k=G(i,n);
		for (j=0;j<t[m];j++) printf("%d ",s[j]|k);
		printf("\n");
	}
	return 0;
}
