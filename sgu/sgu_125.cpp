#include <stdio.h>
#include <string.h>
#define maxn 5
int b[maxn][maxn],a[maxn][maxn];
int n;

int f(int x,int y){
	int k=0;
	if (a[x-1][y]>a[x][y]) k++;
	if (a[x+1][y]>a[x][y]) k++;
	if (a[x][y-1]>a[x][y]) k++;
	if (a[x][y+1]>a[x][y]) k++;
	return k==b[x][y];
}

int check(){
	int i,j;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (!f(i,j)) return 0;
	return 1;
}

int dfs1(int x,int y){
	int i,j;
	if (x==n+1){
		if (check()){
			for (i=1;i<=n;i++){
				for (j=1;j<=n;j++) printf("%d ",a[i][j]);
				printf("\n");
			}
			return 1;
		}else return 0;
	}
	for (i=0;i<10;i++){
		a[x][y]=i;
		if (y==n){
			if (dfs1(x+1,1)) return 1;
		}else{
			if (dfs1(x,y+1)) return 1;
		}
	}
	return 0;
}

int min(int x,int y){return x<y?x:y;}

int max(int x,int y){return x>y?x:y;}

int place(int x,int y,int dx,int dy,int tt){
	if (b[x][y]>2) return 0;
	int l=min(a[x+dx][y],a[x][y+dy]),r=max(a[x+dx][y],a[x][y+dy]);
	if (b[x][y]==2){
		if (l==0) return 0;
		a[x][y]=0;
		return 1;
	}else
	if (b[x][y]==1){
		if (l==r) return 0;
		if (tt==0) a[x][y]=r-1;else a[x][y]=l;
		return 1;
	}else{
		a[x][y]=9;
		return 1;
	}
}

int dfs3(int p){
	if (p==4){
		if (check()){
			int i,j;
			for (i=1;i<=n;i++){
				for (j=1;j<=n;j++) printf("%d ",a[i][j]);
				printf("\n");
			}
			return 1;
		}else return 0;
	}
	int x,y,i,kx,ky;
	if (p==0){
		x=1;y=1;
	}else
	if (p==1){
		x=1;y=3;
	}else
	if (p==2){
		x=3;y=1;
	}else{
		x=3;y=3;
	}
	if ((p&2)==0) kx=1;else kx=-1;
	if ((p&1)==0) ky=1;else ky=-1;
	for (i=0;i<2;i++)
		if (place(x,y,kx,ky,i))
			if (dfs3(p+1)) return 1;
	return 0;
}

int dfs2(int p){
	if (p==6){
		if (!f(2,2)) return 0;
		return dfs3(0);
	}
	int x,y,i;
	if (p==1){
		x=1;y=2;
	}else
	if (p==2){
		x=2;y=1;
	}else
	if (p==3){
		x=2;y=2;
	}else
	if (p==4){
		x=2;y=3;
	}else{
		x=3;y=2;
	}
	for (i=0;i<10;i++){
		a[x][y]=i;
		if (dfs2(p+1)) return 1;
	}
	return 0;
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) scanf("%d",&b[i][j]);
	for (i=0;i<=n+1;i++) a[i][0]=a[i][n+1]=-1;
	for (i=0;i<=n+1;i++) a[0][i]=a[n+1][i]=-1;
	if (n==1){
		if (b[1][1]>0) printf("NO SOLUTION\n");else printf("0\n");
	}else
	if (n==2){
		if (!dfs1(1,1)) printf("NO SOLUTION\n");
	}else{
		if (!dfs2(1)) printf("NO SOLUTION\n");
	}
	return 0;
}
