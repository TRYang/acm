#include <stdio.h>
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++) putchar((i+j)%3==2?'#':'0');
		puts("");
	}
	return 0;
}