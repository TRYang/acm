#include <stdio.h>
#define maxn 10010
struct node{
	int x,y;
};
int n;
node seg[maxn][2];
node p0,p1;
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
int sgn(long long x){
	if (x==0) return x;
	return x>0?1:-1;
}
int area(node p0,node p1,node p2){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
int cross(int p){
	if (min(p0.x,p1.x)>=max(seg[p][0].x,seg[p][1].x)) return 0;
	if (min(p0.y,p1.y)>=max(seg[p][0].y,seg[p][1].y)) return 0;
	int k1=sgn(area(p0,seg[p][0],p1))*sgn(area(p0,seg[p][1],p1));
	int k2=sgn(area(seg[p][0],seg[p][1],p0))*sgn(area(seg[p][0],seg[p][1],p1));
	return k1<0 && k2<0;
}
int check(){
	int i,j,k=0;
	for (i=0;i<n;i++){
		if (min(seg[i][0].x,seg[i][1].x)<=p0.x && p0.x<=max(seg[i][0].x,seg[i][1].x))
			if (min(seg[i][0].y,seg[i][1].y)<=p0.y && p0.y<=max(seg[i][0].y,seg[i][1].y)) return -1;
		k+=cross(i);
	}
	return k%2;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d %d %d %d",&seg[i][0].x,&seg[i][0].y,&seg[i][1].x,&seg[i][1].y);
	scanf("%d %d",&p0.x,&p0.y);
	p1.x=p0.x+28762;
	p1.y=p0.y+7;
	k=check();
	if (k==-1) printf("BORDER\n");else
	if (k==0) printf("OUTSIDE\n");else printf("INSIDE\n");
	return 0;
}
