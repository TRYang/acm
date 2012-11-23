#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int a[110],p[110];
int b[10010][2],bn;
int n,m;
bool cmp(int x,int y){
	return a[x]>a[y];
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	for (i=m=0;i<n;i++) m+=a[i];
	printf("%d\n",m>>1);
	bn=m>>1;
	for (i=0;i<n;i++) p[i]=i;
	sort(p,p+n,cmp);
	memset(b,-1,sizeof(b));
	for (i=k=0;i<bn;i++){
		if (a[p[k]]==1){
			b[i][0]=p[k+1];
			b[i][1]=p[k];
			a[p[k]]--;
			k++;
			a[p[k]]--;
		}else{
			b[i][0]=p[k];
			a[p[k]]--;
		}
	}
	for (i=k=0;i<bn;i++)
		if (b[i][1]==-1){
			while (k<n && a[p[k]]==0) k++;
			a[p[k]]--;
			b[i][1]=p[k];
		}
	for (i=0;i<bn;i++) printf("%d %d\n",b[i][0]+1,b[i][1]+1);
	return 0;
}
