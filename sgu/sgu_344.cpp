#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1010

using namespace std;

const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
char g[maxn][maxn];
pair<int,int> q[maxn*maxn];
int qn;
int n,m;
int move(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<n && y>=0 && y<m;
}
int check(int x,int y){
	if (g[x][y]=='X') return 0;
	int tot=0;
	for (int k=0;k<4;k++)
		if (move(x,y,k) && g[x+mx[k]][y+my[k]]=='X') ++tot;
	return tot>=2;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",g[i]);
	qn=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (g[i][j]=='.' && check(i,j)){
				g[i][j]='X';
				q[qn++]=make_pair(i,j);
			}
	for (int p=0;p<qn;p++){
		int x=q[p].first,y=q[p].second;
		for (int k=0;k<4;k++)
			if (move(x,y,k) && check(x+mx[k],y+my[k])){
				g[x+mx[k]][y+my[k]]='X';
				q[qn++]=make_pair(x+mx[k],y+my[k]);
			}
	}
	int ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++) ans+=g[i][j]=='X';
	printf("%d\n",ans);
	return 0;
}