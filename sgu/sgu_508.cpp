#include <stdio.h>
#include <string.h>
#define maxn 55
typedef long long LL;
LL c[maxn][maxn];
LL s[maxn];
int n,l1,l2,p;
LL sum;
int main(){
	scanf("%d%d%d%d",&n,&l1,&l2,&p);
	if (p==0){
		puts("0 0");
		return 0;
	}
	for (int i=0;i<=50;i++){
		c[i][0]=c[i][i]=1;
		for (int j=1;j<i;j++) c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	sum=0;
	for (int i=l1;i<=n-l2;i++){
		sum+=c[i][l1]*c[n-i][l2];
		s[i]=sum*100;
	}
	sum*=p;
	int ansx=-1,ansy=-1;
	for (int l=l1;l<=n-l2;l++)
		for (int r=l;r<=n-l2;r++){
			LL tot=s[r];
			if (l>l1) tot-=s[l-1];
			if (tot>=sum)
				if (ansx==-1 || r-l<ansy-ansx) ansx=l,ansy=r;
		}
	printf("%d %d\n",ansx,ansy);
	return 0;
}