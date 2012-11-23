#include <stdio.h>
#include <string.h>
#define maxn 150010
typedef long long LL;
char s[maxn];
int a[maxn]; 
int ans[maxn];
int n,m,pn;
int g;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int get(LL p){return a[p%n];}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	m%=n;
	g=gcd(n,m);
	pn=n/g;
	scanf("%s",s);
	for (i=0;i<n;i++) a[i]=s[i]-'0';
	memset(ans,-1,sizeof(ans));
	for (LL st=0;st<g;st++){
		int L=0,av,bv;
		i=0;j=1;
		while (i<pn && j<pn &&  L<pn){
			av=get(st+(LL)(i+L)*(LL)m);
			bv=get(st+(LL)(j+L)*(LL)m);
			if (av==bv) L++;else
			if (av>bv){
				j+=L+1;
				L=0;
			}else{
				i+=L+1;
				L=0;
			}
			if (i==j) j++;
		}
		if (i>=pn) i=j;
		k=0;
		int tmp;
		for (j=0;j<pn;j++){
			tmp=get(st+(LL)(i+j)*(LL)m);
			if (tmp>ans[j]) {k=1;break;}
			if (tmp<ans[j]) {k=0;break;}
		}
		if (k){
			for (j=0;j<pn;j++) ans[j]=get(st+(LL)(i+j)*(LL)m);
		}
	}
	for (j=0;j<g;j++)
		for (i=0;i<pn;i++) printf("%d",ans[i]);
	printf("\n");
	return 0;
}
