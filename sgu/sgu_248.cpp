#include <stdio.h>
#include <string.h>
#define maxn 1000010
int f[maxn];
int a[3];
int n,m;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	scanf("%d",&m);
	if (n==1){
		if (m%a[0]==0) printf("%d\n",m/a[0]);else printf("-1\n");
	}else
	if (n==2){
		int ans=-1;
		for (i=0;a[0]*i<=m;i++)
			if ((m-a[0]*i)%a[1]==0)
				if (ans==-1 || (m-a[0]*i)/a[1]+i<ans) ans=(m-a[0]*i)/a[1]+i;
		printf("%d\n",ans);
	}else{
		memset(f,-1,sizeof(f));
		f[0]=0;
		for (i=1;i<=m;i++){
			if (i>=a[0] && f[i-a[0]]>-1)
				if (f[i]==-1 || f[i-a[0]]+1<f[i]) f[i]=f[i-a[0]]+1;
			if (i>=a[1] && f[i-a[1]]>-1)
				if (f[i]==-1 || f[i-a[1]]+1<f[i]) f[i]=f[i-a[1]]+1;
			if (i>=a[2] && f[i-a[2]]>-1)
				if (f[i]==-1 || f[i-a[2]]+1<f[i]) f[i]=f[i-a[2]]+1;
		}
		printf("%d\n",f[m]);
	}
	return 0;
}
