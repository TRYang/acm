#include <stdio.h>
#include <string.h>
#define maxn 110

typedef long long lint;

int a[maxn][maxn];
int n;
lint t[63];
lint ans;
int main(){
	int i,j,k,l;
	lint tmp;
	scanf("%d",&n);
	t[0]=1;
	for (i=1;i<63;i++) t[i]=t[i-1]+t[i-1];
	memset(a,0,sizeof(a));
	for (i=0;i<n;i++){
		scanf("%I64d",&tmp);
		for (j=62;j>=0;j--)
			if ((tmp&t[j])>0) a[62-j][i]=1;
	}
	ans=0;
	for (i=0;i<63;i++){
		for (k=0;k<n && a[i][k]==0;k++);
		if (k==n){
			if (a[i][k]) ans+=t[62-i];
		}else{
			ans+=t[62-i];
			a[i][n]^=1;
			for (j=i+1;j<63;j++)
				if (a[j][k]>0){
					for (l=k;l<=n;l++) a[j][l]^=a[i][l];
				}
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
