#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxm 5010

using namespace std;

struct node{
	int s,p,v;
} a[maxm];
int h[64];
int n,m;
int ans;
bool cmp1(node x,node y){return x.s<y.s;}
bool cmp2(node x,node y){return x.p<y.p;}
int main(){
	int i,j,k,tmp,tot;
	scanf("%d %d",&n,&m);
	for (i=0;i<m;i++){
		scanf("%d",&a[i].s);
		a[i].p=i;
	}
	sort(a,a+m,cmp1);
	memset(h,0,sizeof(h));
	for (ans=j=k=0,i=1;i<=n;i++){
		if (h[k]==0){
			ans++;
			while (j<m && a[j].s==ans){
				a[j].v=i;
				j++;
			}
		}
		h[k]=0;
		tmp=i;tot=0;
		while (tmp>0){
			tot+=tmp%10;
			tmp/=10;
		}
		h[(k+tot)&63]=1;
		k=(k+1)&63;
	}
	sort(a,a+m,cmp2);
	printf("%d\n",ans);
	for (i=0;i<m;i++) printf("%d ",a[i].v);printf("\n");
	return 0;
}
