#include <stdio.h>
#include <string.h>
#define maxn 3010
#define kk 10000
char s[maxn];
int a[maxn],an;
int b[maxn<<4],bn;
int f[maxn<<4][2];
int m;
int ans;
int MOD(int m){
	int k=0;
	for (int i=an-1;i>=0;i--){
		k=k*kk+a[i];
		a[i]=k/m;
		k%=m;
	}
	return k;
}
int min(int x,int y){return x<y?x:y;}
int main(){
	int i,j,k;
	scanf("%s",s);
	scanf("%d",&m);
	if (m==1){
		printf("%s\n",s);
		return 0;
	}
	int len=strlen(s);
	an=0;k=1;
	for (i=len-1;i>=0;i--){
		if (k==kk){
			an++;
			k=1;
		}
		a[an]+=(s[i]-'0')*k;
		k*=10;
	}
	an++;
	bn=0;
	while (an>0){
		b[bn++]=MOD(m);
		while (an>0 && a[an-1]==0) an--;
	}
	f[bn][0]=0;
	f[bn][1]=1;
	for (i=bn-1;i>=0;i--){
		f[i][0]=min(f[i+1][0]+b[i],f[i+1][1]+m-b[i]);
		f[i][1]=min(f[i+1][0]+b[i]+1,f[i+1][1]+m-b[i]-1);
	}
	printf("%d\n",f[0][0]);
	return 0;
}
