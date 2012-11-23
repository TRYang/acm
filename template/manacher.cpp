/*
	Z Algorithm
	O(n) find the longest palindrome substring
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 5000010

using namespace std;

typedef long long LL;

char s[maxn];
int Z[maxn],X[maxn];		//for the even and the odd
int rank[maxn];
int n;
LL ans;
int main(){
	scanf("%s",s);
	n=strlen(s);

	int p=-1,len;
	for (int i=0;i<n-1;i++){
		if (p==-1 || p+Z[p]<=i) len=0;else len=min(p+Z[p]-i,Z[2*p-i]);
		while (i-len>=0 && i+len<n-1 && s[i-len]==s[i+len+1]) len++;
		Z[i]=len;
		if (p==-1 || i+Z[i]>p+Z[p]) p=i;
	}
	
	X[0]=0;
	p=0;
	for (int i=1;i<n;i++){
		if (p+X[p]<i) len=0;else len=min(p+X[p]-i,X[2*p-i]);
		while (i-len>0 && i+len<n-1 && s[i-len-1]==s[i+len+1]) len++;
		X[i]=len;
		if (i+X[i]>p+X[p]) p=i;
	}
	
	int ans=0;
	for (int i=1;i<n;i++) ans=max(ans,Z[i]<<1);
	for (int i=0;i<n;i++) ans=max(ans,(X[i]<<1)+1);

	return 0;
}
