#include <stdio.h>
#include <string.h>
#define maxn 30010
char s[maxn],d;
int stack[maxn],stn;
int n,m;
int check(){
	stn=0;
	int i,k;
	for (i=n-1;i>=0;i--){
		k=s[i]-'A';
		if (k==(((n-i)&1)^1)^m){
			if (stn<2) return 0;
			if (stack[stn]==k || stack[stn-1]!=k) return 0;
			stack[--stn]=k;
		}else{
			stack[++stn]=k^1;
		}
	}
	return stn==1 && stack[1]==m;
}
int main(){
	int i,j,k;
	scanf("%s",&d);
	m=d-'A';
	scanf("%s",&s);
	n=strlen(s);
	if (check()) printf("YES\n");else printf("NO\n");
	return 0;
}
