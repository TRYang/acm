#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 16

using namespace std;

const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
int tag[maxn][maxn];
int a[maxn][maxn];
int dis[maxn*maxn];
pair<int,int> best_from[maxn*maxn];
int dis2[maxn*maxn];
int f[maxn][maxn];
int h[maxn][maxn];
int q[maxn*maxn][2];
pair<int,int> g[maxn][maxn];
int b[maxn];
int n,m;
int N;
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>=0 && x<n && y>=0 && y<m;
}
void bfs(int sx,int sy,int num){
	int qn=1;
	q[0][0]=sx;
	q[0][1]=sy;
	tag[sx][sy]=num;
	for (int p=0;p<qn;p++){
		int x=q[p][0],y=q[p][1];
		for (int i=0;i<4;i++)
			if (check(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				if (a[tx][ty]==0) continue;
				if (tag[tx][ty]>-1) continue;
				tag[tx][ty]=num;
				q[qn][0]=tx;
				q[qn++][1]=ty;
			}
	}
}
void pre(){
	int qn=0;
	memset(f,-1,sizeof(f));
	for (int i=0;i<m;i++){
		if (tag[0][i]>-1){
			dis[tag[0][i]]=0;
		}else{
			q[qn][0]=0;
			q[qn++][1]=i;
			f[0][i]=1;
		}
		if (tag[n-1][i]>-1){
			dis[tag[n-1][i]]=0;
		}else{
			q[qn][0]=n-1;
			q[qn++][1]=i;
			f[n-1][i]=1;
		}
	}
	for (int i=1;i<n-1;i++){
		if (tag[i][0]>-1){
			dis[tag[i][0]]=0;
		}else{
			q[qn][0]=i;
			q[qn++][1]=0;
			f[i][0]=1;
		}
		if (tag[i][m-1]>-1){
			dis[tag[i][m-1]]=0;
		}else{
			q[qn][0]=i;
			q[qn++][1]=m-1;
			f[i][m-1]=1;
		}
	}
	for (int p=0;p<qn;p++){
		int x=q[p][0],y=q[p][1];
		for (int i=0;i<4;i++)
			if (check(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				if (a[tx][ty]){
					int c=tag[tx][ty];
					if (dis[c]==-1 || f[x][y]<dis[c]){
						dis[c]=f[x][y];
						best_from[c]=make_pair(x,y);
					}
				}else{
					if (f[tx][ty]==-1){
						f[tx][ty]=f[x][y]+1;
						q[qn][0]=tx;
						q[qn++][1]=ty;
						g[tx][ty]=make_pair(x,y);
					}
				}
			}
	}
}
pair<int,int> r[maxn][maxn];
pair<int,int> bf[maxn*maxn];
void floodfill(int sx,int sy){
	int qn=1;
	q[0][0]=sx;
	q[0][1]=sy;
	memset(h,-1,sizeof(h));
	h[sx][sy]=0;
	memset(dis2,-1,sizeof(dis2));
	r[sx][sy]=make_pair(-1,-1);
	for (int p=0;p<qn;p++){
		int x=q[p][0],y=q[p][1];
		for (int i=0;i<4;i++)
			if (check(x,y,i)){
				int tx=x+mx[i],ty=y+my[i];
				if (a[tx][ty]){
					int c=tag[tx][ty];
					if (dis2[c]==-1 || h[x][y]<dis2[c]){
						dis2[c]=h[x][y];
						bf[c]=make_pair(x,y);
					}
				}else{
					if (h[tx][ty]==-1){
						h[tx][ty]=h[x][y]+1;
						q[qn][0]=tx;
						q[qn++][1]=ty;
						r[tx][ty]=make_pair(x,y);
					}
				}
			}
	}
}
void init(){
	memset(b,0,sizeof(b));
}
void Find(pair<int,int> cur){
	for (int i=f[cur.first][cur.second];i>0;i--){
		b[cur.first]|=(1<<(cur.second));
		cur=g[cur.first][cur.second];
	}
}
void Find2(int p){
	pair<int,int> cur=bf[p];
	while (cur.first>-1){
		b[cur.first]|=(1<<(cur.second));
		cur=r[cur.first][cur.second];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		char s[maxn];
		scanf("%s",s);
		for (int j=0;j<m;j++)
			if (s[j]=='.') a[i][j]=0;else a[i][j]=1;
	}
	memset(tag,-1,sizeof(tag));
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (a[i][j] && tag[i][j]==-1){
				bfs(i,j,N);
				++N;
			}
	memset(dis,-1,sizeof(dis));
	pre();
	int ans=-1;
	for (int i=0;i<N;i++)
		for (int j=i+1;j<N;j++)
			if (dis[i]>-1 && dis[j]>-1)
			if (ans==-1 || dis[i]+dis[j]<ans){
				ans=dis[i]+dis[j];
				init();
				Find(best_from[i]);
				Find(best_from[j]);
			}
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (!a[i][j]){
				if (f[i][j]==-1) continue;
				floodfill(i,j);
				for (int c=0;c<N;c++)
					for (int d=c+1;d<N;d++)
						if (dis2[c]>-1 && dis2[d]>-1)
							if (dis2[c]+dis2[d]+f[i][j]<ans){
								ans=dis2[c]+dis2[d]+f[i][j];
								init();
								Find(make_pair(i,j));
								Find2(c);
								Find2(d);
							}
			}
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			if (a[i][j]) printf("X");else
			if ((b[i]&(1<<j))>0) printf("*");else printf(".");
		puts("");
	}
	return 0;
}
