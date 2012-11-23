#include <stdio.h>
#include <string.h>
#define maxn 16010
int st[maxn],aim[maxn<<1],link[maxn<<1],ln;
int f[maxn],g[maxn],tag[maxn];
int a[maxn],an;
int ans,anst;
int n;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=1;i<n;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		in_edge(k,j);
	}
	memset(tag,0,sizeof(tag));
	an=1;a[0]=1;
	tag[1]=1;
	for (k=0;k<an;k++)
		for (i=st[a[k]];i!=-1;i=link[i])
			if (!tag[aim[i]]) tag[aim[i]]=1,a[an++]=aim[i];
	for (k=an-1;k>=0;k--){
		g[a[k]]=1;f[a[k]]=0;
		tag[a[k]]=0;
		for (i=st[a[k]];i!=-1;i=link[i])
			if (!tag[aim[i]]){
				g[a[k]]+=g[aim[i]];
				if (g[aim[i]]>f[a[k]]) f[a[k]]=g[aim[i]];
			}
	}
	ans=1000000;
	for (i=1;i<=n;i++){
		if (n-g[i]>f[i]) f[i]=n-g[i];
		if (f[i]<ans){
			ans=f[i];
			anst=1;
		}else
		if (f[i]==ans) anst++;
	}
	printf("%d %d\n",ans,anst);
	for (i=1;i<=n;i++)
		if (f[i]==ans) printf("%d ",i);
	printf("\n");
	return 0;
}
