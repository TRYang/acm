#include <stdio.h>
#include <string.h>
#define maxn 1010
#define maxm 5010
int tag[maxm],x1[maxm],x2[maxm],y1[maxm],y2[maxm];
int next[maxn][maxn];
int a[maxn][maxn];
int n,m;
int ans;
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
int find(int x,int y){
	if (y>n) return y;
	if (a[x][y]==-1) return y;
	int tmp=find(x,next[x][y]);
	next[x][y]=tmp;
	return tmp;
}
int main(){
	int i,j,k;
	int tx1,tx2,ty1,ty2;
	char c;
	scanf("%d %d",&n,&m);
	for (i=0;i<m;i++){
		scanf("%d %d %d %d %c",&tx1,&ty1,&tx2,&ty2,&c);
		if (c=='b') tag[i]=1;else tag[i]=0;
		x1[i]=min(tx1,tx2);
		x2[i]=max(tx1,tx2);
		y1[i]=min(ty1,ty2);
		y2[i]=max(ty1,ty2);
	}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) next[i][j]=j+1;
	memset(a,-1,sizeof(a));
	for (k=m-1;k>=0;k--){
		for (i=x1[k];i<=x2[k];i++){
			j=y1[k];
			if (a[i][j]>-1) j=find(i,j);
			while (j<=y2[k]){
				a[i][j]=tag[k];
				next[i][j]=y2[k]+1;
				j++;
				if (a[i][j]>-1) j=find(i,j);
			}
		}
	}
	for (ans=0,i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (a[i][j]<1) ans++;
	printf("%d\n",ans);
	return 0;
}
