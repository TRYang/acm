#include <stdio.h>
#include <string.h>
#define maxn 110
#define kk 1000000
int a[maxn][maxn];
int b[maxn],bn;
int pr[maxn],pn;
int n,m;
int p;

int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}

void Out(int p){
	int i,j,k;
	memset(b,0,sizeof(b));
	bn=1;b[0]=1;
	for (i=0;i<p;i++){
		for (j=0;j<bn;j++) b[j]<<=1;
		for (j=0;j<bn;j++)
			if (b[j]>=kk) b[j+1]+=b[j]/kk,b[j]%=kk;
		if (b[bn]>0) bn++;
	}
	b[0]--;
	printf("%d",b[bn-1]);
	for (i=bn-2;i>=0;i--){
		if (b[i]<100000) printf("0");
		if (b[i]<10000) printf("0");
		if (b[i]<1000) printf("0");
		if (b[i]<100) printf("0");
		if (b[i]<10) printf("0");
		printf("%d",b[i]);
	}
	printf("\n");
}

void find(int x,int y){
	int i,j,k;
	for (i=x;i<n;i++)
		if (a[i][y]>0){
			for (j=y;j<=m;j++){
				k=a[i][j];a[i][j]=a[x][j];a[x][j]=k;
			}
			return;
		}
}

int main(){
	int i,j,k;
	for (pn=0,i=2;pn<100;i++)
		if (check(i)) pr[pn++]=i;
	scanf("%d %d",&n,&m);
	memset(a,0,sizeof(a));
	for (i=0;i<m;i++){
		scanf("%d",&k);
		for (j=0;j<pn && k>1;j++)
			while (k%pr[j]==0){
				a[j][i]^=1;
				k/=pr[j];
			}
	}
	p=0;
	int x=0;
	for (i=0;i<m && x<n;i++){
		find(x,i);
		if (a[x][i]){
			p++;
			for (j=x+1;j<n;j++)
				if (a[j][i])
					for (k=i;k<=m;k++) a[j][k]^=a[x][k];
			x++;
		}
	}
	Out(m-p);
	return 0;
}
