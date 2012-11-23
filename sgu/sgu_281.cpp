#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#define maxn 50010

using namespace std;

string Name[maxn];
string list[maxn];
int pr[maxn];
int rank1[maxn],rank2[maxn];
int rank[maxn];
int n;
int main(){
	int i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++){
		char s[50];
		scanf("%s",s);
		list[i].clear();
		for (j=0;j<strlen(s);j++) list[i].push_back(s[j]);
		Name[i]=list[i];
	}
	sort(Name,Name+n);
	for (i=0;i<n;i++) rank1[i]=lower_bound(Name,Name+n,list[i])-Name;
	for (i=0;i<n;i++) rank[rank1[i]]=i;
	for (i=0;i<n;i++){
		char s[50];
		scanf("%s",s);
		list[i].clear();
		for (j=0;j<strlen(s);j++) list[i].push_back(s[j]);
		rank2[i]=lower_bound(Name,Name+n,list[i])-Name;
	}
	k=-1;
	j=0;
	for (i=0;i<n;i++){
		if (rank[rank2[i]]>k) k=rank[rank2[i]];
		pr[j++]=rank2[i];
		if (k==i){
			sort(pr,pr+j);
			for (int l=0;l<j;l++) printf("%s\n",Name[pr[l]].c_str());
			j=0;
		}
	}
	return 0;
}
