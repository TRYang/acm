#include <stdio.h>
#include <string.h>
#define maxn 310
const int mx[]={0,1,1,1,0,-1,-1,-1};
const int my[]={1,1,0,-1,-1,-1,0,1};
int f[maxn][maxn][2];
int q[maxn*maxn*3],qn;
int map[maxn][maxn];
int n,m;
int stx,sty;
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<n && y>=0 && y<n && map[x][y]!=1;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		char s[maxn];
		scanf("%s",s);
		for (int j=0;j<n;j++)
			if (s[j]=='Q'){
				map[i][j]=0;
				stx=i;
				sty=j;
			}else
			if (s[j]=='.') map[i][j]=0;else
			if (s[j]=='W') map[i][j]=1;else
			if (s[j]=='B') map[i][j]=2;
	}
	int qn=1;
	q[0]=(stx<<9)|(sty);
	if (m==0){
		printf("1\n");
		return 0;
	}
	memset(f,-1,sizeof(f));
	f[stx][sty][0]=0;
	for (int p=0;p<qn;p++){
		int x=((q[p]>>9)&511),y=(q[p]&511),s=(q[p]>>18);
		if (f[x][y][s]>m) break;
		for (int k=0;k<8;k++){
			int tx=x,ty=y;
			for (int i=1;i<n;i++){
				tx+=mx[k];
				ty+=my[k];
				if (tx<0 || tx>=n || ty<0 || ty>=n) break;
				if (map[tx][ty]==1) break;
				if (f[tx][ty][s^1]<=0){
					f[tx][ty][s^1]=f[x][y][s]+1;
					q[qn++]=((s^1)<<18)|(tx<<9)|ty;
				}
				if (f[tx][ty][s^1]<=f[x][y][s]) break;
				if (map[tx][ty]==2) break;
			}
		}
		if (map[x][y]==2){
			for (int k=0;k<8;k++)
				if (check(x,y,k) && check(x,y,(k+4)%8)){
					int tx=x+mx[k],ty=y+my[k];
					if (f[tx][ty][s]<=0){
						f[tx][ty][s]=f[x][y][s]+2;
						q[qn++]=((s^1)<<18)|(tx<<9)|ty;
					}
				}
		}
	}
	int ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (f[i][j][m%2]>0 && f[i][j][m%2]<=m) ++ans;
	printf("%d\n",ans);
	return 0;
}
