#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
typedef long long LL;
LL f[70][1<<16];
int Bit[1<<16];
int n,m,dm;
int cal(int x){
	int res=0;
	while (x>0){
		res+=(x&1);
		x>>=1;
	}
	return res;
}
int main(){
	int i,j,k;
	scanf("%d %d %d",&n,&m,&dm);
	for (i=0;i<1<<m;i++) Bit[i]=cal(i);
	memset(f,0,sizeof(f));
	int M=(1<<m)-1;
	f[0][M]=1;
	for (i=0;i<n;i++)
		for (j=0;j<1<<m;j++)
			if (f[i][j]>0){
				if (Bit[k=((j<<1)&M)]>=dm) f[i+1][k]+=f[i][j];
				if (Bit[k=(((j<<1)&M)+1)]>=dm) f[i+1][k]+=f[i][j];
			}
	LL ans=0;
	for (i=0;i<=M;i++) ans+=f[n][i];
	cout<<ans<<endl;
	return 0;
}
