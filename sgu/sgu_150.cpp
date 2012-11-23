#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int X1,X2,Y1,Y2,n;
int g,L;

int gcd(int x,int y){
	return y==0 ? x : gcd(y,x%y);
}

int Gety(double y,int x,int k){
	return abs(x-X1)%L==0 ? Y1+k*((abs(Y1-Y2)/g)*(abs(x-X1)/L))-1 : floor(y+1e-8);
}

void work(int d){
	int i,j,x;
	double k=(double)(Y1-Y2)/(X1-X2),b=Y1-k*X1,y,ty=Y1;
	g=gcd(abs(X1-X2),abs(Y1-Y2));
	L=abs(X1-X2)/g;
	for (x=X1;x!=X2;x+=d){
		y=k*(x+d)+b;
		j= Y1>Y2 ? Gety(ty,x,-1)-floor(y+1e-8)+1 : Gety(y,x+d,1)-floor(ty+1e-8)+1;
		if (j>=n){
			int x0= d>0 ? x : x-1,y0= Y1>Y2 ? Gety(ty,x,-1) : floor(ty+1e-8);
			for (;n>1;n--) y0+= Y1>Y2 ? -1 : 1;
			printf("%d %d\n",x0,y0);
			return;
		}
		n-=j;
		ty=y;
	}
	printf("no solution\n");
}

int main(){
	int i,j,k;
	scanf("%d %d %d %d %d",&X1,&Y1,&X2,&Y2,&n);
	if (X1==X2 || Y1==Y2){
		printf("no solution\n");
	}else
	if (X1<X2) work(1);else work(-1);
	return 0;
}
