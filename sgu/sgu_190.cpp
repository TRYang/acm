#include <stdio.h>
#include <string.h>
#define maxn 41
int a[maxn][maxn];
int st[maxn*maxn],aim[maxn*maxn*2],link[maxn*maxn*2],ln;
int from[maxn*maxn],tag[maxn*maxn];
int bn,b[maxn*maxn],cn,c[maxn*maxn];
int n,m;
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
int check(){
	if ((n*n-m)%2==1) return 0;
	int i,j,k=0;
	memset(from,-1,sizeof(from));
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if ((i+j)%2==0 && !a[i][j]){
				memset(tag,0,sizeof(tag));
				if (dfs(i*n+j)) k++;
			}
	return k*2+m==n*n;
}
int main(){
	int i,j,k;
	memset(a,0,sizeof(a));
	for (scanf("%d %d",&n,&m),i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		a[j-1][k-1]=1;
	}
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			if ((i+j)%2==0 && !a[i][j]){
				if (i>0 && !a[i-1][j]) in_edge(i*n+j,(i-1)*n+j);
				if (j>0 && !a[i][j-1]) in_edge(i*n+j,i*n+j-1);
				if (j<n-1 && !a[i][j+1]) in_edge(i*n+j,i*n+j+1);
				if (i<n-1 && !a[i+1][j]) in_edge(i*n+j,(i+1)*n+j);
			}
	if (check()){
		printf("Yes\n");
		bn=cn=0;
		for (i=0;i<n;i++)
			for (j=0;j<n;j++)
				if ((i+j)%2==1 && from[i*n+j]>-1){
					if (from[i*n+j]==i*n+j-1) c[cn++]=from[i*n+j];
					if (from[i*n+j]==(i-1)*n+j) b[bn++]=from[i*n+j];
					if (from[i*n+j]==i*n+j+1) c[cn++]=i*n+j;
					if (from[i*n+j]==(i+1)*n+j) b[bn++]=i*n+j;
				}
		printf("%d\n",bn);
		for (i=0;i<bn;i++) printf("%d %d\n",(b[i]/n)+1,(b[i]%n)+1);
		printf("%d\n",cn);
		for (i=0;i<cn;i++) printf("%d %d\n",(c[i]/n)+1,(c[i]%n)+1);
	}else printf("No\n");
	return 0;
}
