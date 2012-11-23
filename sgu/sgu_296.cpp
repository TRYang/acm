#include <stdio.h>
#include <string.h>
#define maxn 1010
int stack[maxn],stn;
char s[maxn];
int n,m;
int main(){
	scanf("%s%d",s,&m);
	n=strlen(s);
	stn=0;
	for (int i=0;i<n;i++){
		int k=s[i]-'0';
		while (stn && stack[stn]<k && stn+n-i>n-m) --stn;
		if (stn<n-m) stack[++stn]=k;
	}
	for (int i=1;i<=stn;i++) printf("%d",stack[i]);
	puts("");
	return 0;
}
