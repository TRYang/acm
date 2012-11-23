#include <stdio.h>
#include <string.h>
#define maxn 1010
#define kk 1000000
long long s[3000];
int sn;
int a[maxn];
int n,tot;
int tn;

int cal(int x){
	int res=0;
	for (;x>0;x/=10) res+=x%10;
	return res;
}

int f(int x){
	return x<10 ? x : f(cal(x));
}

int main(){
	int i,j,k;
	for (scanf("%d",&tn);tn>0;tn--){
		scanf("%d",&n);
		for (i=0;i<n;i++) scanf("%d",a+i);
		memset(s,0,sizeof(s));
		sn=1;s[0]=0;
		for (i=n-1;i>=0;i--){
			for (s[0]++,j=0;j<sn && s[j]>=kk;j++){
				s[j+1]+=s[j]/kk;
				s[j]%=kk;
			}
			if (s[sn]>0) sn++;
			for (j=0;j<sn;j++) s[j]*=a[i];
			for (j=0;j<sn;j++)
				if (s[j]>=kk){
					s[j+1]+=s[j]/kk;
					s[j]%=kk;
				}
			while (s[sn]>0) sn++;
		}
		tot=0;
		for (i=0;i<sn;i++) tot+=cal(s[i]);
		printf("%d\n",f(tot));
	}
	return 0;
}
