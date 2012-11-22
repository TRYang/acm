#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 5010

using namespace std;

struct node{
	int x,y;
	void read(){
		scanf("%d%d",&x,&y);
	}
	friend bool operator == (const node &x,const node &y){
		return x.x==y.x && x.y==y.y;
	}
} a[maxn][2];
int len[maxn];
int n;
int dot(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
}
int check(int p,int q){
//	if (len[p]==0 || len[q]==0) return 0;
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			if (a[p][i]==a[q][j] && dot(a[p][i],a[p][i^1],a[q][j^1])==0) return 1;
	return 0;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		a[i][0].read();
		a[i][1].read();
		len[i]=(a[i][0].x-a[i][1].x)*(a[i][0].x-a[i][1].x);
		len[i]+=(a[i][0].y-a[i][1].y)*(a[i][0].y-a[i][1].y);
	}
	int ans=0;
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (check(i,j)){
				++ans;
//				printf("%d %d\n",i+1,j+1);
			}
	printf("%d\n",ans);
	return 0;
}
