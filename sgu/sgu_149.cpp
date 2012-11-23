#include <stdio.h>
#include <string.h>
#define maxn 10010
int st[maxn],aim[maxn<<1],link[maxn<<1],len[maxn<<1],ln;
int a[maxn],tag[maxn];
int f[maxn],g[maxn],h[maxn];
int n;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	link[ln]=st[x];
	len[ln]=z;
	st[x]=ln++;
}
int main(){
	int i,j,k,l;
	memset(st,-1,sizeof(st));
	ln=0;
	scanf("%d",&n);
	for (i=1;i<n;i++){
		scanf("%d %d",&j,&k);
		in_edge(j-1,i,k);
		in_edge(i,j-1,k);
	}
	memset(tag,0,sizeof(tag));
	k=1;a[0]=0;tag[0]=1;
	for (j=0;j<k;j++)
		for (i=st[a[j]];i!=-1;i=link[i])
			if (!tag[aim[i]]){
				tag[aim[i]]=1;
				a[k++]=aim[i];
			}
	for (k=n-1;k>=0;k--){
		i=a[k];
		tag[i]=0;
		f[i]=g[i]=0;
		h[i]=-1;
		for (j=st[i];j!=-1;j=link[j])
			if (!tag[aim[j]])
				if (f[aim[j]]+len[j]>f[i]){
					g[i]=f[i];
					f[i]=f[aim[j]]+len[j];
					h[i]=aim[j];
				}else
				if (f[aim[j]]+len[j]>g[i]) g[i]=f[aim[j]]+len[j];
	}
	for (k=0;k<n;k++){
		i=a[k];
		tag[i]=1;
		for (j=st[i];j!=-1;j=link[j])
			if (!tag[aim[j]]){
				l= h[i]==aim[j] ? g[i]+len[j] : f[i]+len[j];
				if (l>f[aim[j]]){
					g[aim[j]]=f[aim[j]];
					f[aim[j]]=l;
					h[aim[j]]=i;
				}else
				if (l>g[aim[j]]) g[aim[j]]=l;
			}
	}
	for (i=0;i<n;i++) printf("%d\n",f[i]);
	return 0;
}
