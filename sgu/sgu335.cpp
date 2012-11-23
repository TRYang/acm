#include <stdio.h>
#include <string.h>
#include <algorithm>
#define inf 2000000000

using namespace std;

const int mx[]={1,0,-1,0};
const int my[]={0,1,0,-1};
int n,m;
int cx,cy;
int tx,ty;
char buf[10];
int calc1(){
	//thief move first
	int ret=0;
	if (cy<ty){
		ty=m-ty+1;
		cy=m-cy+1;
	}
	ret+=2*(ty-1);
	cy-=(ty-1);
	if (cy%2==0) ret+=2*(cy-1)-1;else ret+=2*(cy-2);
	return ret;
}
int calc2(){
	//cop move first
	int ret=0;
	if (abs(ty-cy)==1) return 1;
	if (cy<ty){
		ty=m-ty+1;
		cy=m-cy+1;
	}
	ret+=2*(ty-1);
	cy-=(ty-1);
	if (cy%2==1) ret+=2*cy-4;else ret+=2*cy-5;
	return ret;
}
int calc(int cx,int cy){
	int dx=abs(cx-tx),dy=abs(cy-ty);
	int mask=0;
	if (dx==dy){
		if (tx<cx){
			if (ty<cy) mask|=1;else mask|=2;
		}else{
			if (ty<cy) mask|=4;else mask|=8;
		}
	}else
	if (dx>dy){
		if (tx<cx) mask|=3;else mask|=12;
	}else{
		if (ty<cy) mask|=5;else mask|=10;
	}
	int ret=0;
	if ((mask&1)>0) ret=max(ret,2*(cx+cy-3));
	if ((mask&2)>0) ret=max(ret,2*(cx-1+m-cy-1));
	if ((mask&4)>0) ret=max(ret,2*(n-cx+cy-1-1));
	if ((mask&8)>0) ret=max(ret,2*(n-cx+m-cy-1));
	return ret;
}
int work(){
	if (buf[0]=='C'){
		if (n==1) return calc2();
		if (m==1){
			swap(n,m);
			swap(cx,cy);
			swap(tx,ty);
			return calc2();
		}
		if ((tx+ty)%2==(cx+cy)%2) return 0;
		if (abs(cx-tx)+abs(cy-ty)==1) return 1;
		int ret=2000000000;
		for (int i=0;i<4;i++){
			int x=cx+mx[i],y=cy+my[i];
			if (x<1 || x>n || y<1 || y>m) continue;
			ret=min(ret,calc(x,y)+1);
		}
		return ret;
	}else{
		if (n==1) return calc1();
		if (m==1){
			swap(n,m);
			swap(cx,cy);
			swap(tx,ty);
			return calc1();
		}
		if ((tx+ty)%2!=(cx+cy)%2) return 0;
		return calc(cx,cy);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&cx,&cy);
	scanf("%d%d",&tx,&ty);
	scanf("%s",buf);
	printf("%d\n",work());
	return 0;
}
