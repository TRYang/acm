#include <stdio.h>
int pr[4000],pn;
int tn,n;

int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}

int main(){
	int i,j,k;
	pn=0;
	for (i=2;i*i<=1000000000;i++)
		if (check(i)) pr[pn++]=i;
	for (scanf("%d",&tn);tn>0;tn--){
		scanf("%d",&n);
		/*if (n<2){
			printf("No ");
			continue;
		}*/
		k=0;
		for (i=0;i<pn && n>1 && k<=2;i++){
			while (n%pr[i]==0){
				n/=pr[i];
				k++;
				if (k>2) break;
			}
		}
		if (n>1) k++;
		if (k==2) printf("Yes\n");else printf("No\n");
	}
	return 0;
}
