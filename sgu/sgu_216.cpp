#include <stdio.h>
#include <string.h>
#define maxn 10010
int st[maxn],aim[maxn<<1],link[maxn<<1],ln;
int father[maxn],tot[maxn];
int root[maxn],f[maxn];
int tag[maxn];
int n,m;
int tn;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int Find(int x){return father[x]= father[x]==x?x:Find(father[x]);}
void dfs(int x){
	int i,j,k=-1;
	tag[x]=1;
	tot[x]=1;
	for (i=st[x];i!=-1;i=link[i])
		if (!tag[aim[i]]){
			dfs(aim[i]);
			if (tot[aim[i]]<m){
				if (k==-1){
					k=aim[i];
				}else{
					father[aim[i]]=k;
					tot[k]+=tot[aim[i]];
					if (tot[k]>=m){
						f[k]=++tn;
						root[tn]=x;
						k=-1;
					}
				}
			}
		}
	if (k>-1){
		father[k]=x;
		tot[x]+=tot[k];
	}
	if (tot[x]>=m){
		f[x]=++tn;
		root[tn]=x;
	}
}
int Go(int x){
	int i,k;
	tag[x]=1;
	for (i=st[x];i!=-1;i=link[i])
		if (!tag[aim[i]]){
			if (Find(aim[i])==1){
				k=Go(aim[i]);
				if (k>-1) return k;
			}else{
				return aim[i];
			}
		}
	return -1;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=1;i<n;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		in_edge(k,j);
	}
	memset(tag,0,sizeof(tag));
	memset(root,-1,sizeof(root));
	for (i=1;i<=n;i++) father[i]=i;
	tn=0;
	dfs(1);
	if (tot[1]<m){
		memset(tag,0,sizeof(tag));
		k=Go(1);
		father[1]=k;
	}
	printf("%d\n",tn);
	for (i=1;i<=n;i++) printf("%d ",f[Find(i)]);
	printf("\n");
	for (i=1;i<=tn;i++) printf("%d ",root[i]);
	printf("\n");
	return 0;
}
