#include <stdio.h>
#include <string.h>
#define maxn 1010
const int mx[4]={0,1,0,-1};
const int my[4]={1,0,-1,0};
int q[maxn*maxn],qn;
int qt[maxn*maxn];
int tag[maxn][maxn];
int ans[30000];
int n,m,pn,t;
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return (x>0 && x<=n && y>0 && y<=m && !tag[x][y]);
}
int main(){
	int i,j,k;
	scanf("%d %d %d %d",&n,&m,&pn,&t);
	memset(tag,0,sizeof(tag));
	memset(ans,0,sizeof(ans));
	qn=0;
	for (i=0;i<pn;i++){
		scanf("%d %d",&j,&k);
		qt[qn]=0;
		q[qn++]=(j<<10)|k;
		tag[j][k]=i+1;
		ans[i+1]++;
	}
	for (int p=0;p<qn;p++){
		if (qt[p]==t) break;
		int x=q[p]>>10,y=(q[p]&((1<<10)-1));
		for (i=0;i<4;i++)
			if (check(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				tag[tx][ty]=tag[x][y];
				ans[tag[x][y]]++;
				qt[qn]=qt[p]+1;
				q[qn++]=(tx<<10)|ty;
			}
	}
	for (i=1;i<=pn;i++) printf("%d\n",ans[i]);
	return 0;
}
