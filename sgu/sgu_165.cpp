#include <stdio.h>
#include <math.h>
#define maxn 6010
double h[maxn],s;
int a[maxn],an;
int b[maxn],bn;
int c[maxn],cn;
int n;
int sign(double x){
	if (fabs(x)<1e-8) return 0;
	if (x>1e-8) return 1;else return -1;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%lf",h+i);
	printf("yes\n");
	an=bn=cn=0;
	for (i=0;i<n;i++){
		h[i]-=2.0;
		k=sign(h[i]);
		if (k==0) c[cn++]=i+1;else
		if (k==1) a[an++]=i;else b[bn++]=i;
	}
	s=0;
	while (an+bn>0){
		if (s>-1e-8){//s>=0
			s+=h[b[--bn]];
			c[cn++]=b[bn]+1;
		}else{
			s+=h[a[--an]];
			c[cn++]=a[an]+1;
		}
	}
	for (i=0;i<cn-1;i++) printf("%d ",c[i]);printf("%d\n",c[cn-1]);
	return 0;
}
