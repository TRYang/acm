#include <stdio.h>
#include <string.h>
#define maxn 30
int p[maxn],v[maxn],a[maxn];
int n,t;
int meet(int x,int y){
	if (v[x]<0){
		int tmp=x;x=y;y=tmp;
	}
	if (p[y]>p[x]){
		if (p[x]+v[x]>=p[y]+v[y]) return 1;else return 0;
	}else{
		if (1000-p[x]+p[y]<=v[x]-v[y]) return 1;else return 0;
	}
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&t);
	for (i=0;i<n;i++) scanf("%d",p+i);
	for (i=0;i<n;i++) scanf("%d",v+i);
	memset(a,0,sizeof(a));
	for (;t>0;t--){
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
				if (i!=j && v[i]*v[j]<0)
					if (meet(i,j)) a[i]++;
		for (i=0;i<n;i++) p[i]=(p[i]+v[i]+1000)%1000;
	}
	for (i=0;i<n;i++) printf("%d ",a[i]);printf("\n");
	return 0;
}
