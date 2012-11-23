#include <stdio.h>
#include <string.h>
#define maxn 10010
char s[maxn];
int n;
void pr(){
	int i,j,k=0,t1=0,t2=0;
	for (i=n-1;i>=0;i--){
		if (s[i]==')') k++,t1++;
		if (s[i]=='('){
			k--;
			t2++;
			if (k>0){
				for (j=0;j<i;j++) printf("%c",s[j]);
				printf(")(");
				for (j=1;j<t2;j++) printf("(");
				for (j=1;j<t1;j++) printf(")");
				printf("\n");
				return;
			}
		}
	}
	printf("No solution\n");
}
int main(){
	scanf("%s",&s);
	n=strlen(s);
	pr();
	return 0;
}
