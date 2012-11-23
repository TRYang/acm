#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1010

using namespace std;

struct node{
	int x,y;
	node(){
		x=y=0;
	}
	node(int _x,int _y){
		x=_x;
		y=_y;
	}
	void read(){
		scanf("%d%d",&x,&y);
	}
};
const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
int tag[maxn][maxn];
node q[maxn*maxn];
int f[maxn][maxn];
node sp,tp;
int n,m;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int area(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
int move(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<=n && y>=0 && y<=m;
}
int main(){
	int rn;
	scanf("%d%d%d",&n,&m,&rn);
	sp.read();
	tp.read();
	for (int i=0;i<rn;i++){
		node A,B;
		A.read();
		B.read();
		if (A.x>B.x) swap(A,B);
		if (A.x==B.x){
			for (int y=min(A.y,B.y);y<=max(A.y,B.y);y++) tag[A.x][y]=15;
		}else
		if (A.y==B.y){
			for (int x=A.x;x<=B.x;x++) tag[x][A.y]=15;
		}else
		if (B.y>A.y){
			int dx=(B.x-A.x)/gcd(B.x-A.x,B.y-A.y);
			int dy=(B.y-A.y)/gcd(B.x-A.x,B.y-A.y);
			for (int x=A.x,y=A.y;x<=B.x;x+=dx,y+=dy) tag[x][y]=15;
			for (int x=A.x+1,y=A.y;x<B.x;x++){
				while (area(A,node(x,y+1),B)>=0) ++y;
				tag[x][y]|=2;
			}
			for (int x=A.x,y=A.y+1;y<B.y;y++){
				while (area(A,node(x,y),B)<0) ++x;
				tag[x][y]|=4;
			}
		}else{
			int dx=(B.x-A.x)/gcd(B.x-A.x,A.y-B.y);
			int dy=(A.y-B.y)/gcd(B.x-A.x,A.y-B.y);
			for (int x=A.x,y=A.y;x<=B.x;x+=dx,y-=dy) tag[x][y]=15;
			for (int x=A.x+1,y=A.y;x<B.x;x++){
				while (area(A,node(x,y-1),B)<=0) --y;
				tag[x][y]|=8;
			}
			for (int x=A.x,y=A.y-1;y>B.y;y--){
				while (area(A,node(x,y),B)>=0) ++x;
				tag[x][y]|=4;
			}
		}
	}
	for (int i=0;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int k=0;k<4;k++)
				if ((tag[i][j]&(1<<k))>0 && move(i,j,k))
					tag[i+mx[k]][j+my[k]]|=(1<<((k+2)&3));
	memset(f,-1,sizeof(f));
	int qn=1;
	q[0]=tp;
	f[tp.x][tp.y]=0;
	for (int p=0;p<qn;p++){
		int x=q[p].x,y=q[p].y;
		int step=f[x][y]>>2;
		for (int k=0;k<4;k++)
			if ((tag[x][y]&(1<<k))==0 && move(x,y,k)){
				int tx=x+mx[k],ty=y+my[k];
				if (tag[tx][ty]==15) continue;
				if (f[tx][ty]>-1) continue;
				f[tx][ty]=((step+1)<<2)|((k+2)&3);
				q[qn++]=node(tx,ty);
			}
	}
	if (f[sp.x][sp.y]==-1) puts("NO SOLUTION");else{
		printf("%d\n",f[sp.x][sp.y]>>2);
		int x=sp.x,y=sp.y;
		while (x!=tp.x || y!=tp.y){
			int dir=(f[x][y]&3);
			if (dir==0) printf("E");else
			if (dir==1) printf("N");else
			if (dir==2) printf("W");else printf("S");
			x+=mx[dir];
			y+=my[dir];
		}
		puts("");
	}
	return 0;
}