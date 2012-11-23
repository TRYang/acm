#include <stdio.h>
#include <algorithm>
#define maxn 110

using namespace std;

int l[maxn];
int n,m;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",l+i);
	for (k=m=0;k<n-1;m++){
		sort(l+k,l+n);
		if (l[k]==1){
			if (n-k<=3) k=n;else{
				l[k]+=l[n-1]+l[n-2];
				n-=2;
			}
		}else{
			if (n-k<=2) k=n;else{
				l[k]--;
				l[n-2]+=1+l[n-1];
				n--;
			}
		}
	}
	printf("%d\n",m);
	return 0;
}
