#include <stdio.h>
#include <string.h>
#define maxn 210
#define maxm 30010
int st[maxn],aim[maxm<<1],link[maxm<<1],ln;
int col[maxn],a[maxn];
int n,m;
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int bfs(int x){
	int i,p,an;
	an=1;a[0]=x;
	col[x]=0;
	for (p=0;p<an;p++)
		for (i=st[a[p]];i!=-1;i=link[i])
			if (col[aim[i]]==-1){
				col[aim[i]]=col[a[p]]^1;
				a[an++]=aim[i];
			}else
			if (col[aim[i]]==col[a[p]]) return 0;
	return 1;
}
int check(){
	memset(col,-1,sizeof(col));
	for (int i=1;i<=n;i++)
		if (col[i]==-1)
			if (!bfs(i)) return 0;
	return 1;
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		in_edge(k,j);
	}
	if (check()){
		printf("yes\n");
		for (k=0,i=1;i<=n;i++)
			if (!col[i]) k++;
		printf("%d\n",k);
		for (i=1;i<=n;i++)
			if (!col[i]) printf("%d ",i);
		printf("\n");
	}else printf("no\n");
	return 0;
}
