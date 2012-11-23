#include <stdio.h>
long long a,b,c,x1,x2,y1,y2;
long long x0,y0;
long long ans;
long long L,R;

long long gcd(long long a,long long b){
	return b==0 ? a : gcd(b,a%b);
}

long long ex_gcd(long long a,long long b,long long &x,long long &y){
	if (b==0){
		x=1;y=0;
		return a;
	}
	long long g=ex_gcd(b,a%b,x,y),tx=x;
	x=y;
	y=tx-(a/b)*y;
	return g;
}

long long max(long long x,long long y){return x>y?x:y;}

long long min(long long x,long long y){return x<y?x:y;}

long long upper(long long x,long long y){
	if (x>0){
		return x%y==0 ? x/y : x/y+1;
	}else{
		return x/y;
	}
}

long long lower(long long x,long long y){
	if (x>=0){
		return x/y;
	}else{
		return x%y==0 ? x/y : x/y-1;
	}
}

void check(long long l,long long r,long long w){
	if (w<0){
		long long tmp;
		tmp=-l;l=-r;r=tmp;
		w=-w;
	}
	L=max(L,upper(l,w));
	R=min(R,lower(r,w));
}

int main(){
	int i,j,k;
	scanf("%I64d %I64d %I64d",&a,&b,&c);
	scanf("%I64d %I64d",&x1,&x2);
	scanf("%I64d %I64d",&y1,&y2);
	ans=0;
	if (a==0 && b==0){
		if (c==0) ans=(x2-x1+1)*(y2-y1+1);
	}else
	if (a==0){
		if (c%b==0 && c/b>=y1 && c/b<=y2) ans=x2-x1+1;
	}else
	if (b==0){
		if (c%a==0 && c/a>=x1 && c/a<=x2) ans=y2-y1+1;
	}else{
		long long g=gcd(a,b),p;
		c=-c;
		if (c%g==0){
			p=c/g;
			ex_gcd(a,b,x0,y0);
			x0*=p;
			y0*=p;
			L=-1000000000;
			R=1000000000;
			check(x1-x0,x2-x0,b/g);
			check(y1-y0,y2-y0,-a/g);
			ans=max(ans,R-L+1);
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
