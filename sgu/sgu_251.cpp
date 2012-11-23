#include <stdio.h>
#include <string.h>
int a[10];
int p[10];
double x[10],y[10];
int n;
int check(){
	x[p[3]]=x[p[2]]/2.0;
	y[p[3]]=2*(a[p[0]]+a[p[2]]+a[p[3]])/x[p[2]];
	y[p[1]]=2*(a[p[0]]+a[p[1]]+a[p[2]])/x[p[2]];
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) scanf("%d",a+i);
	if (n==3){
		printf("YES\n");
		printf("0.0000 0.0000\n");
		printf("0.0000 2.0000\n");
		printf("%d.0000 0.0000\n",a[0]+a[1]+a[2]);
	}else
	if (n==4){
		if (a[0]+a[1]==a[2]+a[3] || a[0]+a[2]==a[1]+a[3]){
			if (a[0]+a[1]==a[2]+a[3]){
				p[0]=0;p[1]=2;p[2]=1;p[3]=3;
			}else{
				p[0]=0;p[1]=1;p[2]=2;p[3]=3;
			}
			x[0]=y[0]=0;
			x[p[2]]=2;y[p[2]]=0;
			y[p[1]]=-(a[p[0]]+a[p[2]]+a[p[1]]);
			y[p[3]]=(a[p[0]]+a[p[2]]+a[p[3]]);
			double l=2.0*(a[p[0]]+a[p[1]]+a[p[3]])/(y[p[3]]-y[p[1]]);
			x[p[1]]=x[p[3]]=l;
			printf("YES\n");
			for (i=0;i<4;i++) printf("%.4f %.4f\n",x[i],y[i]);
		}else printf("NO\n");
	}else printf("NO\n");
	return 0;
}
