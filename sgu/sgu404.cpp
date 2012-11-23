#include <stdio.h>
#include <string.h>
char s[110][110];
int n,m;
int main(){
	scanf("%d%d",&m,&n);
	for (int i=0;i<n;i++) scanf("%s",s[i]);
	printf("%s\n",s[(m-1)%n]);
	return 0;
}
