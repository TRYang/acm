#include <stdio.h>
#include <string.h>
#define maxn 1010
int st[maxn],aim[maxn<<1],link[maxn<<1],ln;
int n,m;
int a[maxn],an;
int level[maxn];
int f[maxn][maxn];
void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
int main(){
	int i,j,k;
	freopen("test.txt","r",stdin);
	scanf("%d %d",&n,&m);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=0;i<m;i++){
		scanf("%d %d",&j,&k);
		in_edge(j,k);
		in_edge(k,j);
	}
	memset(level,-1,sizeof(level));
	level[1]=1;
	an=1;a[0]=1;
	m=1;
	for (k=0;k<an;k++)
		for (i=st[a[k]];i!=-1;i=link[i])
			if (level[aim[i]]==-1){
				level[aim[i]]=level[a[k]]+1;
				if (level[aim[i]]>m) m=level[aim[i]];
				a[an++]=aim[i];
			}
	for (j=m;j>0;j--){
		for (i=1;i<=n;i++)
			if (level[i]==j){
				if (j%2==0){
					f[i][j]=1;
					for (k=st[i];k!=-1;k=link[k])
						if (level[aim[k]]==level[i]+1) f[i][j]=min(f[i][j],f[aim[k]][j+1]);
				}else{
					f[i][j]=0;
					for (k=st[i];k!=-1;k=link[k])
						if (level[aim[k]]==level[i]+1) f[i][j]=max(f[i][j],f[aim[k]][j+1]);
				}
			}
	}
	if (!f[1][1]) printf("Nikolay\n");else printf("Vladimir\n");
	return 0;
}
