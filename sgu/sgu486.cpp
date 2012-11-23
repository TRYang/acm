#include <stdio.h>
#include <string.h>
char s[5],t[5];
int main(){
	scanf("%s%s",s,t);
	int c=0,d=0;
	for (int i=0;i<4;i++)
		if (s[i]==t[i]) c++;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			if (i!=j && s[i]==t[j]) d++;
	printf("%d %d\n",c,d);
	return 0;
}
