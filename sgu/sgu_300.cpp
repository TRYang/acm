#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 4010

using namespace std;

struct node{
	int x,y;
} s[maxn][2],tmp;
int t[maxn];
int n;
int ans;
int aabs(int x){return x>0?x:-x;}
int Len(int p){
	return s[p][0].x==s[p][1].x ? aabs(s[p][0].y-s[p][1].y) : aabs(s[p][0].x-s[p][1].x);
}
int tx,ty;
int cross(int p,int q){
	if ((s[p][0].x!=s[p][1].x)+(s[q][0].x!=s[q][1].x)!=1) return 0;
	int tmp;
	if (s[p][0].x!=s[p][1].x){
		tmp=p;
		p=q;
		q=tmp;
	}
	if (min(s[q][0].x,s[q][1].x)<=s[p][0].x && max(s[q][0].x,s[q][1].x)>=s[p][0].x
	&& min(s[p][0].y,s[p][1].y)<=s[q][0].y && max(s[p][0].y,s[p][1].y)>=s[q][0].y){
		tx=s[p][0].x;
		ty=s[q][0].y;
		return 1;		
	}else return 0;
}
int f(int x1,int y1,int x2,int y2){
	return x1==x2?aabs(y1-y2):aabs(x1-x2);
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	ans=0;
	for (i=0;i<n;i++){
		scanf("%d %d",&tmp.x,&tmp.y);
		s[i][0]=tmp;
		if (i>0) s[i-1][1]=tmp;
	}
	n--;
	t[0]=Len(0);
	for (i=1;i<n;i++) t[i]=t[i-1]+Len(i);
	ans=t[n-1];
	for (i=1;i<n;i++){
		for (j=i-3;j>=0;j--)
			if (cross(i,j)){
				k=t[i-1]-t[j]+f(s[i][0].x,s[i][0].y,tx,ty)+f(tx,ty,s[j][1].x,s[j][1].y);
				ans=min(ans,k);
			}
	}
	printf("%d\n",ans);
	return 0;
}
