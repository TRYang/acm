#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 10

using namespace std;

int h[1<<9],f[1<<10];
int p[maxn],pn;
int n,l;
int tn;
int s;
int Play(){
	if (n<=l) return f[n];
	memset(h,-1,sizeof(h));
	h[s]=l;
	int i,j,k;
	for (i=l+1;;i++){
		s<<=1;
		k=1;
		for (j=0;j<pn;j++)
			if ((s&(1<<p[j]))==0) k=0;
		s|=k^1;
		s&=(1<<l)-1;
		f[i]=k^1;
		if (i==n) return f[i];
		if (h[s]>-1){
			return f[h[s]+((n-i)%(i-h[s]))];
		}else h[s]=i;
	}
}
int main(){
	int i,j,k;
	for (scanf("%d",&tn);tn>0;tn--){
		pn=1;p[0]=1;
		scanf("%d %d",&n,&pn);
		for (i=1;i<=pn;i++) scanf("%d",p+i);
		pn++;
		sort(p,p+pn);
		l=p[pn-1];
		memset(h,-1,sizeof(h));
		s=0;
		for (i=2;i<=l;i++){
			k=1;
			s<<=1;
			for (j=0;j<pn;j++)
				if (i-p[j]>0 && (s&(1<<p[j]))==0) k=0;
			s|=k^1;
			f[i]=k^1;
		}
		if (Play()) printf("FIRST PLAYER MUST WIN\n");else printf("SECOND PLAYER MUST WIN\n");
	}
	return 0;
}
