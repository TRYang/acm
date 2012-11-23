#include <stdio.h>
#include <math.h>
#include <algorithm>
#define maxn 10010

using namespace std;

int a[maxn],ans[maxn];
int p[maxn];
double det[maxn],tmp;
int n,tot,m;

bool cmp(int x,int y){
	return det[x]>det[y];
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	tot=0;
	for (i=0;i<n;i++){
		scanf("%d",a+i);
		tot+=a[i];
	}
	m=100;
	for (i=0;i<n;i++){
		p[i]=i;
		tmp=(double)a[i]/tot;
		tmp*=100;
		det[i]=tmp-floor(tmp);
		ans[i]=floor(tmp);
		m-=ans[i];
	}
	sort(p,p+n,cmp);
	for (i=0;m>0;i++){
		ans[p[i]]++;
		m--;
	}
	for (i=0;i<n;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
