#include <stdio.h>
#include <string.h>
#define maxl 5000
#define kk 10000
int a[maxl],an;
int b[maxl],bn;
int n,m;
int Cal(int *c,int k,int s){
	int i,j,n;
	memset(c,0,sizeof(c));
	n=1;c[0]=1;
	for (i=0;i<s;i++){
		for (j=0;j<n;j++) c[j]*=k;
		for (j=0;j<n;j++)
			if (c[j]>=kk){
				c[j+1]+=c[j]/kk;
				c[j]%=kk;
			}
		while (c[n]>0) n++;
	}
	return n;
}
int cmp(){
	if (an>bn) return 1;
	if (an<bn) return 0;
	for (int i=an-1;i>=0;i--){
		if (a[i]>b[i]) return 1;
		if (a[i]<b[i]) return 0;
	}
	return -1;
}
void pr(int n,int *r){
	printf("%d",r[n-1]);
	for (int i=n-2;i>=0;i--){
		if (r[i]<1000) printf("0");
		if (r[i]<100) printf("0");
		if (r[i]<10) printf("0");
		printf("%d",r[i]);
	}
	printf("\n");
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	an=Cal(a,n,m);
	bn=Cal(b,m,n);
	k=cmp();
	if (k==-1){
		printf("0\n");
	}else
	if (k>0){
		k=0;
		for (i=0;i<an;i++){
			a[i]-=k;
			k=0;
			if (a[i]>=b[i]) a[i]-=b[i];else{
				k=1;
				a[i]+=kk-b[i];
			}
		}
		while (an>0 && a[an-1]==0) an--;
		pr(an,a);
	}else{
		k=0;
		for (i=0;i<bn;i++){
			b[i]-=k;
			k=0;
			if (b[i]>=a[i]) b[i]-=a[i];else{
				k=1;
				b[i]+=kk-a[i];
			}
		}
		while (bn>0 && b[bn-1]==0) bn--;
		printf("-");
		pr(bn,b);
	}
	return 0;
}
