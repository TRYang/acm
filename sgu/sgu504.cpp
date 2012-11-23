#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 710

using namespace std;

char s[maxn][maxn];
int row[maxn][maxn],col[maxn][maxn];
int t1[maxn][maxn],t2[maxn][maxn];
int n,m;
int ans;
pair<int,int> c,d;
pair<int,int> tc,td;
void prepare1(){
	for (int x=0;x<n;x++){
		int p=-1;
		for (int y=0;y<m;y++){
			int len;
			if (p==-1 || p+row[x][p]<=y) len=1;else len=min(row[x][2*p-y],p+row[x][p]-y);
			while (y-len>=0 && y+len<m && s[x][y-len]==s[x][y+len]) ++len;
			row[x][y]=len;
			if (p==-1 || y+row[x][y]>p+row[x][p]) p=y;
		}
	}
	for (int y=0;y<m;y++){
		int p=-1;
		for (int x=0;x<n;x++){
			int len;
			if (p==-1 || p+col[p][y]<=x) len=1;else len=min(col[2*p-x][y],p+col[p][y]-x);
			while (x-len>=0 && x+len<n && s[x-len][y]==s[x+len][y]) ++len;
			col[x][y]=len;
			if (p==-1 || x+col[x][y]>p+col[p][y]) p=x;
		}
	}
//	for (int i=0;i<n;i++,puts(""))
//		for (int j=0;j<m;j++) printf("%d ",col[i][j]);
}
int check1(int N){
	for (int i=0;i<n;i++){
		t1[i][0]=(col[i][0]>=N);
		for (int j=1;j<m;j++) t1[i][j]=t1[i][j-1]+(col[i][j]>=N);
	}
	for (int j=0;j<m;j++){
		t2[0][j]=(row[0][j]>=N);
		for (int i=1;i<n;i++) t2[i][j]=t2[i-1][j]+(row[i][j]>=N);
	}
	for (int i=0;i+N<=n;i++)
		for (int j=0;j+N<=m;j++){
			if (i-N+1<0 || j-N+1<0) continue;
			int s=t1[i][j+N-1];
			if (j-N>=0) s-=t1[i][j-N];
			int t=t2[i+N-1][j];
			if (i-N>=0) t-=t2[i-N][j];
			if (s==2*N-1 && t==2*N-1){
				tc=make_pair(i-N+1,j-N+1);
				td=make_pair(i+N-1,j+N-1);
				return 1;
			}
		}
	return 0;
}
void prepare2(){
	for (int x=0;x<n;x++){
		int p=-1;
		for (int y=0;y<m-1;y++){
			int len;
			if (p==-1 || p+row[x][p]<=y) len=0;else len=min(row[x][2*p-y],p+row[x][p]-y);
			while (y-len>=0 && y+len+1<m && s[x][y-len]==s[x][y+len+1]) ++len;
			row[x][y]=len;
			if (p==-1 || y+row[x][y]>p+row[x][p]) p=y;
		}
	}
	for (int y=0;y<m;y++){
		int p=-1;
		for (int x=0;x<n-1;x++){
			int len;
			if (p==-1 || p+col[p][y]<=x) len=0;else len=min(col[2*p-x][y],p+col[p][y]-x);
			while (x-len>=0 && x+len+1<n && s[x-len][y]==s[x+len+1][y]) ++len;
			col[x][y]=len;
			if (p==-1 || x+col[x][y]>p+col[p][y]) p=x;
		}
	}
}
int check2(int N){
	for (int i=0;i<n-1;i++){
		t1[i][0]=(col[i][0]>=N);
		for (int j=1;j<m;j++) t1[i][j]=t1[i][j-1]+(col[i][j]>=N);
	}
	for (int j=0;j<m-1;j++){
		t2[0][j]=(row[0][j]>=N);
		for (int i=1;i<n;i++) t2[i][j]=t2[i-1][j]+(row[i][j]>=N);
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			if (i-N+1<0 || j-N+1<0) continue;
			if (i+N>=n || j+N>=m) break;
			int s=t1[i][j+N];
			if (j-N>=0) s-=t1[i][j-N];
			int t=t2[i+N][j];
			if (i-N>=0) t-=t2[i-N][j];
			if (s==2*N && t==2*N){
				tc=make_pair(i-N+1,j-N+1);
				td=make_pair(i+N,j+N);
				return 1;
			}
		}
	return 0;
}
int main(){
	ans=1;
	c=d=make_pair(0,0);
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",s[i]);
	prepare1();
	int L=1,R=(min(n,m)-1)/2,mid;
	while (L<=R){
		mid=(L+R)>>1;
		if (check1(mid+1)){
			L=mid+1;
			if (2*mid+1>ans){
				ans=2*mid+1;
				c=tc;
				d=td;
			}
		}else R=mid-1;
	}
	prepare2();
	L=1,R=(min(n,m)>>1);
	while (L<=R){
		mid=(L+R)>>1;
		if (check2(mid)){
			L=mid+1;
			if (2*mid>ans){
				ans=2*mid;
				c=tc;
				d=td;
			}
		}else R=mid-1;
	}
//	printf("%d\n",ans);
	printf("%d %d %d %d\n",c.first+1,c.second+1,d.first+1,d.second+1);
	return 0;
}
