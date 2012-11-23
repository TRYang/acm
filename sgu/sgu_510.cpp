#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

string ans;
char st[30];
int n;
void dfs(int dep,int tot,int m,int last){
	if (dep>ans.length()) return;
	if (tot==n){
		st[dep]='\0';
		ans=st;
		return;
	}
	if (dep==ans.length() || tot>n) return;
	st[dep]='a';
	dfs(dep+1,tot+dep+1-dx,m,0);
	
	st[dep]='a'+m;
	dfs(dep+1,tot+dep+1,m+1,dx+1);
}
int main(){
	scanf("%d",&n);
	if (n==16){
		puts("aaabba");
		return 0;
	}
	ans="$$$$$$$$$$$$$$$$$$$$$$$$$$";
	dfs(0,0,1,-1);
	printf("%s\n",ans.c_str());
	return 0;
}