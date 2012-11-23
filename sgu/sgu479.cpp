#include <stdio.h>
#include <string.h>
#define maxn 210
const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
int a[maxn][maxn];
int q[maxn*maxn][2];
int n,m;
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<n && y>=0 && y<m;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) scanf("%d",&a[i][j]);
	int qn=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (a[i][j]==1){
				q[qn][0]=i;
				q[qn++][1]=j;
			}
	int flag=1;
	for (int p=0;p<qn;p++){
		int x=q[p][0],y=q[p][1];
		a[x][y]=0;
		for (int i=0;i<4;i++)
			if (check(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				if (a[tx][ty]==0) continue;
				--a[tx][ty];
				if (a[tx][ty]==0) flag=0;
				if (a[tx][ty]==1){
					q[qn][0]=tx;
					q[qn++][1]=ty;
				}
			}
	}
	if (qn<n*m) flag=0;
	if (flag){
		for (int i=qn-1;i>=0;i--) printf("%d %d\n",q[i][0]+1,q[i][1]+1);
	}else puts("No solution");
	return 0;
}
