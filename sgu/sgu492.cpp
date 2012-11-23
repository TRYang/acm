#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 20

using namespace std;

typedef long long LL;

LL POW[maxn];
LL f[maxn][10];
LL m;
int check(LL x){
	int a[20];
	int an=0;
	while (x) a[an++]=x%10,x/=10;
	for (int i=0;i<an-1;i++)
		if (a[i]==3 && a[i+1]==1) return 1;
	return 0;
}
LL calc(LL x){
	LL ret=x;
	int a[20],an=0;
	while (x) a[an++]=x%10,x/=10;
	int flag=0,last=0;
	for (int i=an-1;i>=0;i--){
		for (int j=0;j<a[i];j++)
			if (flag){
				ret-=POW[i];
			}else{
				if (last==1 && j==3){
					ret-=POW[i];
				}else{
					ret-=f[i][j];
				}
			}
		if (last==1 && a[i]==3) flag=1;
		last=a[i];
	}
	return ret;
}
int main(){
	int tn;
	POW[0]=1;
	for (int i=1;i<maxn;i++) POW[i]=POW[i-1]*10;
	for (int i=0;i<10;i++) f[0][i]=0;
	for (int i=1;i<maxn;i++)
		for (int j=0;j<10;j++){
			f[i][j]=0;
			for (int k=0;k<10;k++){
				if (j==1 && k==3) f[i][j]+=POW[i-1];else
					f[i][j]+=f[i-1][k];
			}
		}
	LL ans;
	for (scanf("%d",&tn);tn;tn--){
		scanf("%I64d",&m);
		LL L=1,R=f[19][0],mid;
		while (L<=R){
			mid=L+((R-L)>>1);
			LL tot=calc(mid);
			if (tot==m && !check(mid)){
				ans=mid;
				break;
			}
			if (tot>m) R=mid-1;else L=mid+1;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
