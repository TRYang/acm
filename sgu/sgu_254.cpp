#include <stdio.h>
#include <string.h>
int a[1000100],b[1000100];
int n,m,q;
int Next(int p){
	while (1){
		p++;
		if (p==m) p=0;
		if (a[p]<=b[p]) return p;
	}
}
int Pre(int p){
	while (1){
		p--;
		if (p==-1) p=m-1;
		if (a[p]<=b[p]) return p;
	}
}
int main(){
	int i,k,p,dp;
	scanf("%d %d",&n,&q);
	m=1;
	a[0]=1;b[0]=n;
	p=1;dp=0;
	k=0;
	for (i=1;i<=n;i++){
		if (p%2==1) k=0;else k=1;
		int tn=q-1;
		if (!k){
			while (tn>0){
				if (p==b[dp]){
					dp=Next(dp);
					p=a[dp];
				}else p++;
				tn--;
			}
		}else{
			while (tn>0){
				if (p==a[dp]){
					dp=Pre(dp);
					p=b[dp];
				}else p--;
				tn--;
			}
		}
		if (i==n) printf("%d\n",p);
		if (p==a[dp]) a[dp]++;else
		if (p==b[dp]) b[dp]--;else{
			
		}
	}
	return 0;
}
