#include <stdio.h>
#include <string.h>
#include <string>
#define maxn 1000010
const std::string pat="<>(){}[]";
char s[maxn];
int stack[maxn],stn;
int Count[maxn];
int n;
long long ans;
int main(){
	gets(s);
	n=strlen(s);
	for (int i=0;i<n;i++) s[i]=pat.find(s[i]);
	stn=0;
	stack[0]=-1;
	Count[0]=0;
	ans=0;
	for (int i=0;i<n;i++){
		int p=s[i];
		if ((p&1)==0){
			stack[++stn]=i;
			Count[stn]=0;
		}else{
			if (stn==0 || s[stack[stn]]!=(p^1)){
				stn=0;
				stack[0]=i;
				Count[0]=0;
			}else{
				--stn;
				++Count[stn];
				// printf("%d %d (%d)\n",stack[stn]+1,i,Count[stn]);
				ans+=Count[stn];
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}