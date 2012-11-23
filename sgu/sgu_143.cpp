#include <stdio.h>
#include <string.h>
#define maxn 16010
int st[maxn],aim[maxn<<1],link[maxn<<1],ln;
int v[maxn],f[maxn],tag[maxn];
int a[maxn],an;
int n;
int ans;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",v+i);
	ln=0;
	memset(st,-1,sizeof(st));
	for (i=1;i<n;i++){
		scanf("%d %d",&j,&k);
		in_edge(j-1,k-1);
		in_edge(k-1,j-1);
	}
	memset(tag,0,sizeof(tag));
	an=1;a[0]=0;tag[0]=1;
	for (k=0;k<an;k++)
		for (i=st[a[k]];i!=-1;i=link[i])
			if (!tag[aim[i]]) tag[aim[i]]=1,a[an++]=aim[i];
	ans=-(1<<20);
	for (k=an-1;k>=0;k--){
		int p=a[k];
		tag[p]=0;
		f[p]=v[p];
		for (i=st[p];i!=-1;i=link[i])
			if (!tag[aim[i]]) f[p]+=f[aim[i]];
		if (f[p]>ans) ans=f[p];
		if (f[p]<0) f[p]=0;
	}
	printf("%d\n",ans);
	return 0;
}
