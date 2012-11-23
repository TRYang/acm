#include <stdio.h>
#include <string.h>
#define maxn 410
int st[maxn],aim[maxn*maxn],link[maxn*maxn],ln;
int tag[maxn],from[maxn];
int n,m;
int tot;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int dfs(int x){
	if (tag[x]) return 0;
	tag[x]=1;
	for (int i=st[x];i!=-1;i=link[i])
		if (from[aim[i]]==-1 || dfs(from[aim[i]])){
			from[aim[i]]=x;
			return 1;
		}
	return 0;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<n;i++){
		for (scanf("%d",&k);k>0;k--){
			scanf("%d",&j);
			j--;
			in_edge(i,j);
			in_edge(i,m+j);
		}
	}
	memset(from,-1,sizeof(from));
	tot=0;
	for (i=0;i<n;i++){
		memset(tag,0,sizeof(tag));
		tot+=dfs(i);
	}
	if (tot==m<<1){
		printf("YES\n");
		for (i=0;i<m;i++) printf("2 %d %d\n",from[i]+1,from[m+i]+1);
	}else printf("NO\n");
	return 0;
}
