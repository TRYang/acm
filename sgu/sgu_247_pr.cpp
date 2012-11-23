#include <stdio.h>
#include <string.h>
#include <algorithm>
#define kk 10000
#define maxn 2001

using namespace std;

struct bignum{
	int l,v[1000];
	friend bignum operator + (const bignum &x,const bignum &y){
		bignum res;
		res.l=max(x.l,y.l);
		memset(res.v,0,sizeof(res.v));
		int i;
		for (i=0;i<res.l;i++) res.v[i]=x.v[i]+y.v[i];
		for (i=0;i<res.l;i++)
			if (res.v[i]>=kk) res.v[i+1]++,res.v[i]-=kk;
		if (res.v[res.l]>0) res.l++;
		return res;
	}
	friend bignum operator - (const bignum &x,const bignum &y){
		bignum res;
		res.l=x.l;
		memset(res.v,0,sizeof(res.v));
		int i,k=0;
		for (i=0;i<res.l;i++){
			if (x.v[i]-k>=y.v[i]){
				res.v[i]=x.v[i]-k-y.v[i];
				k=0;
			}else{
				res.v[i]=x.v[i]-k+kk-y.v[i];
				k=1;
			}
		}
		while (res.l>1 && res.v[res.l-1]==0) res.l--;
		return res;
	}
	friend bignum operator * (const bignum &x,const bignum &y){
		bignum res;
		res.l=x.l+y.l;
		memset(res.v,0,sizeof(res.v));
		int i,j,k;
		for (i=0;i<x.l;i++){
			k=0;
			for (j=0;j<y.l;j++){
				res.v[i+j]+=k+x.v[i]*y.v[j];
				k=res.v[i+j]/kk;
				res.v[i+j]%=kk;
			}
			if (k>0) res.v[i+y.l]+=k;
		}
		while (res.l>1 && res.v[res.l-1]==0) res.l--;
		return res;
	}
	void pr(){
		printf("%d",v[l-1]);
		for (int i=l-2;i>=0;i--){
			if (v[i]<1000) printf("0");
			if (v[i]<100) printf("0");
			if (v[i]<10) printf("0");
			printf("%d",v[i]);
		}
	}
};
int tn;
int n;
bignum ch(int x){
	bignum res;
	res.l=1;
	memset(res.v,0,sizeof(res.v));
	res.v[0]=x;
	return res;
}
bignum Div(bignum x,int p){
	int i,j,k=0;
	for (i=x.l-1;i>=0;i--){
		j=x.v[i]+k*kk;
		x.v[i]=j/p;
		k=j%p;
	}
	while (x.l>1 && x.v[x.l-1]==0) x.l--;
	return x;
}
bignum C(int n,int m){
	bignum res=ch(1);
	for (int i=n;i>n-m;i--) res=res*ch(i);
	for (int i=2;i<=m;i++) res=Div(res,i);
	return res;
}
int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}
int main(){
	int i,j,k;
	freopen("sub.cpp","w",stdout);
	k=0;
	for (i=3;i<1000;i++)
		if (check(i)){
			k++;
			bignum tmp=Div(C(i<<1,i)-ch(2),i)+ch(2);
			printf("\"");
			tmp.pr();
			printf("\",");
			printf("\n");
		}
	printf("\n");
	printf("%d\n",k);
	fclose(stdout);
	return 0;
}
