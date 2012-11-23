#include <stdio.h>
int a[16],c[4],n;
int main(){
	int i,j,k;
	n=0;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++) scanf("%d",c+j);
		if (i%2==1){
			for (j=3;j>=0;j--)
				if (c[j]>0) a[n++]=c[j];
		}else{
			for (j=0;j<4;j++)
				if (c[j]>0) a[n++]=c[j];
		}
	}
	k=0;
	for (i=1;i<n;i++)
		for (j=0;j<i;j++)
			if (a[j]>a[i]) k++;
	if (k%2==1) printf("YES\n");else printf("NO\n");
	return 0;
}
