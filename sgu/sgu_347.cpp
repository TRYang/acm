#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#define maxn 110

using namespace std;

string a[maxn];
int n;
bool cmp(string x,string y){
	return x+y<y+x;
}
int main(){
	char s[1010];
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%s",s);
		a[i]=s;
	}
	sort(a,a+n,cmp);
	for (int i=0;i<n;i++) printf("%s",a[i].c_str());
	puts("");
	return 0;
}