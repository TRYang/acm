#include <stdio.h>
#include <string.h>
int q[10000],qn,f[100];
int a[10],b,c,d;
int x,y;
int main(){
	for (int i=1;i<4;i++) scanf("%d",a+i);
	scanf("%d",&b);
	for (int i=4;i<7;i++) scanf("%d",a+i);
	scanf("%d",&c);
	for (int i=7;i<10;i++) scanf("%d",a+i);
	scanf("%d%d",&d,&a[0]);
	scanf("%d%d",&x,&y);
	qn=1;
	q[0]=x;
	memset(f,-1,sizeof(f));
	f[x]=0;
	for (int p=0;p<qn;p++){
		int u=q[p];
		for (int i=0;i<10;i++)
			if (a[i])
				if (f[i]==-1 || f[u]+1<f[i]){
					f[i]=f[u]+1;
					q[qn++]=i;
				}
		if (b)
			if (f[(u+1)%100]==-1 || f[u]+1<f[(u+1)%100]){
				f[(u+1)%100]=f[u]+1;
				q[qn++]=(u+1)%100;
			}
		if (c)
			if (f[(u+99)%100]==-1 || f[u]+1<f[(u+99)%100]){
				f[(u+99)%100]=f[u]+1;
				q[qn++]=(u+99)%100;
			}
		if (d){
			for (int i=1;i<10;i++)
				for (int j=0;j<10;j++)
					if (a[i] && a[j])
						if (f[i*10+j]==-1 || f[u]+3<f[i*10+j]){
							f[i*10+j]=f[u]+3;
							q[qn++]=i*10+j;
						}
		}
	}
	if (y<0 || y>99) puts("-1");else
	printf("%d\n",f[y]);
	return 0;
}
