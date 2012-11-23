#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int a[10],b[10];
int n,m;
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	for (i=1;i<=n;i++) a[i]=100;
	for (;m>0;m--){
		scanf("%d %d",&j,&k);
		if (a[j]>0){
			if (a[k]>0) b[j]+=3;
			a[k]-=8;
		}
	}
	for (i=1;i<=n;i++)
		if (a[i]>0) b[i]+=a[i]>>1;
	for (i=1;i<=n;i++) printf("%d %d\n",a[i],b[i]);
	return 0;
}
