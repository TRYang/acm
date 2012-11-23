#include <stdio.h>
#include <string.h>
#define maxn 1010
int a[maxn];
int s[maxn<<1];
int tag[maxn];
int q[maxn];
int n;
int check(){
	int i,j,k;
	int head=1,tail=0;
	memset(tag,0,sizeof(tag));
	for (i=n<<1;i>0;i--){
		for (j=1;j<=n;j++)
			if (!tag[j] && a[j]==0) break;
		if (j==n+1){
			if (head>tail) return 0;
			j=q[head++];
			s[i]=-j;
			for (k=j+1;k<=n;k++)
				if (!tag[k]) a[k]--;
		}else{
			s[i]=j;
			tag[j]=1;
			q[++tail]=j;
			for (k=1;k<j;k++)
				if (!tag[k]) a[k]--;
		}
	}
	return 1;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",a+i);
	if (check()){
		printf("YES\n");
		for (i=1;i<=n<<1;i++) printf("%d ",s[i]);
		printf("\n");
	}else printf("NO\n");
	return 0;
}
