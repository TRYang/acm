#include <stdio.h>
#define maxn 500010
char s[maxn];
int h[1<<20];
int n,m;
int find(int l){
	int i,j,k=0;
	for (i=0;i<l-1;i++) k=(k<<1)|s[i];
	for (i=l-1;i<n;i++){
		k=((k<<1)|s[i])&((1<<l)-1);
		h[k]=l;
	}
	for (i=0;i<1<<l;i++)
		if (h[i]!=l) return i;
	return -1;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	scanf("%s",s);
	for (i=0;i<n;i++) s[i]=s[i]-'a';
	for (m=1;k=find(m),k==-1;m++);
	printf("%d\n",m);
	for (i=1;i<=m;i++)
		if ((k&(1<<(m-i)))>0) printf("b");else printf("a");
	printf("\n");
	return 0;
}
