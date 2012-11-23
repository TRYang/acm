#include <stdio.h>
#include <string.h>
int pr[100000],pn;
int check(int x){
	for (int i=2;i*i<=x;i++)
		if (x%i==0) return 0;
	return 1;
}
int a[1000000],an;
int f(int x){
	an=0;
	for (int i=0;i<pn;i++)
		if (x%pr[i]==0){
			a[an++]=pr[i];
			while (x%pr[i]==0) x/=pr[i];
		}
	if (x>1) a[an++]=x;
	for (int i=0;i<an-1;i++) a[an-1]-=a[i];
	return a[an-1];
}
int main(){
	pn=0;
	for (int i=2;i<=2000;i++)
		if (check(i)) pr[pn++]=i;
	int a,b;
	scanf("%d%d",&a,&b);
	puts(f(a)>f(b)?"a":"b");
	return 0;
}
