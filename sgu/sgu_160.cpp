#include <stdio.h>
#include <string.h>
#define maxn 10010
long long f[maxn][20],tt[61];
int a[maxn],tag[maxn];
int n,m,l,ans;
void pr(int x,int y){
	if (x==0){
		if (y!=1) tag[x]=1;
		return;
	}
	if ((f[x-1][y/60]&tt[y%60])>0) pr(x-1,y);else{
		for (int i=0;i<m;i++)
			if ((i*a[x])%m==y && (f[x-1][i/60]&tt[i%60])>0){
				pr(x-1,i);
				tag[x]=1;
				return;
			}
	}
}
int main(){
	int i,j,k,t;
	for (tt[0]=1,i=1;i<61;i++) tt[i]=tt[i-1]+tt[i-1];
	scanf("%d %d",&n,&m);
	for (i=0;i<n;i++) scanf("%d",a+i);
	memset(f,0,sizeof(f));
	f[0][0]=2;
	f[0][a[0]/60]|=tt[a[0]%60];
	l=(m-1)/60;
	for (i=1;i<n;i++)
		for (j=0;j<=l;j++){
			f[i][j]|=f[i-1][j];
			for (k=0;k<60;k++)
				if ((f[i-1][j]&tt[k])>0){
					t=((j*60+k)*a[i])%m;
					f[i][t/60]|=tt[t%60];
				}
		}
	for (i=m-1;i>=0;i--)
		if ((f[n-1][i/60]&tt[i%60])>0){
			ans=i;
			break;
		}
	printf("%d\n",ans);
	memset(tag,0,sizeof(tag));
	pr(n-1,ans);
	for (i=0;i<n;i++)
		if (tag[i]) printf("%d ",i+1);
	if (ans>1) printf("\n");
	return 0;
}
