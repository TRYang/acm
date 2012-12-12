#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define maxn 500010
#define BASE 37

using namespace std;

typedef unsigned long long llu;

int pr[50000],pn;
char s[maxn];
llu h[maxn],pow[maxn];
int a[maxn],q[maxn],an;
int b[maxn];
int n;
int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}
llu cut(int st,int len){
	return h[st+len]-h[st]*pow[len];
}
void prepare(int x){
	an=0;
	for (int i=0;i<pn && pr[i]*pr[i]<=x;i++)
		if (x%pr[i]==0){
			a[an]=pr[i];
			q[an]=0;
			while (x%pr[i]==0){
				x/=pr[i];
				q[an]++;
			}
			++an;
		}
	if (x>1){
		a[an]=x;
		q[an++]=1;
	}
}
int check_per(int st,int len,int p){
	p=len/p;
	if (p==len) return 1;
	return cut(st,len-p)==cut(st+p,len-p);
}
int main(){
	for (int i=2;i*i<=500000;i++)
		if (check(i)) pr[pn++]=i;
	scanf("%d",&n);
	pow[0]=1;
	for (int i=1;i<=n;i++) pow[i]=pow[i-1]*BASE;
	scanf("%s",s);
	h[0]=0;
	for (int i=1;i<=n;i++) h[i]=h[i-1]*BASE+s[i-1]-'a'+3;
	int qn;
	for (scanf("%d",&qn);qn;qn--){
		int l,r;
		scanf("%d%d",&l,&r);
		--l,--r;
		int len=r-l+1;
		if (len==1){
			printf("1\n");
			continue;
		}
		prepare(len);
		int tx=1;
		for (int j=0;j<an;j++){
			int x=1;
			for (int i=1;i<=q[j];i++)
				if (check_per(l,len,x*a[j])){
					x*=a[j];
				}else break;
			tx*=x;
		}
		printf("%d\n",len/tx);
	}
	return 0;
}
