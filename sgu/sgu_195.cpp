#include <stdio.h>
#include <string.h>
#define maxn 500010
int st[maxn],ln,aim[maxn],link[maxn];
int tag[maxn];
int f[maxn],g[maxn],h[maxn];
int a[maxn],an,p;
int n;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int max(int x,int y){return x>y?x:y;}
int main(){
	int i,j,k;
	while (scanf("%d",&n)!=EOF){
		ln=0;
		st[0]=tag[0]=-1;
		for (i=1;i<n;i++){
			st[i]=tag[i]=-1;
			scanf("%d",&k);
			in_edge(k-1,i);
		}
		for (i=n-1;i>=0;i--){
			f[i]=1;g[i]=0;
			for (k=0,j=st[i];j!=-1;j=link[j]){
				f[i]+=g[aim[j]];
				g[i]+=g[aim[j]];
				if (f[aim[j]]-g[aim[j]]>k){
					k=f[aim[j]]-g[aim[j]];
					h[i]=aim[j];
				}
			}
			g[i]+=k;
		}
		printf("%d000\n",g[0]);
		an=1;
		a[0]=0;
		for (p=0;p<an;p++){
			j=(a[p]&1);
			k=a[p]>>1;
			if (j) tag[k]=1;
			for (i=st[k];i!=-1;i=link[i])
				if (j){
					a[an++]=aim[i]<<1;
				}else{
					if (aim[i]==h[k]) a[an++]=(aim[i]<<1)+1;else a[an++]=aim[i]<<1;
				}
		}
		for (i=0;i<n;i++)
			if (tag[i]==1) printf("%d ",i+1);
		printf("\n");
	}
	return 0;
}
