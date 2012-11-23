//Z Algorithm
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1000010

using namespace std;

char s[maxn];
int Z[maxn];
int n;
void ZAlgorithm(char *s,int n){
	//string s and the length of s
	int p=0;
	Z[0]=0;
	for (int i=1;i<n;i++){
		int len;
		if (p+Z[p]<=i) len=0;else len=min(Z[i-p],p+Z[p]-i);
		while (i+len<n && s[i+len]==s[len]) len++;
		Z[i]=len;
		if (i+Z[i]>p+Z[p]) p=i;
	}
}
int main(){
	return 0;
}
