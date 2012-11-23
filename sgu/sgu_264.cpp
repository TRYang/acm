#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#define maxn 810

using namespace std;

map<string,int> Name1,Name2;
string list1[maxn],list2[maxn];
int g[maxn][maxn];
int rank[maxn][maxn];
int match[maxn];
int a[maxn];
char s[30000];
int n,m;
int get_num(string s,int tag){
	if (tag){
		Name2.insert(make_pair(s,m));
		list2[m]=s;
		m++;
		return m-1;
	}else return Name2[s];
}
void Find(int x){
	while (1){
		a[x]++;
		int k=g[x][a[x]];
		if (match[k]==-1){
			match[k]=x;
			return;
		}else{
			if (rank[k][match[k]]>rank[k][x]){
				int tmp=match[k];
				match[k]=x;
				Find(tmp);
				return;
			}
		}
	}
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	Name1.clear();
	Name2.clear();
	m=0;
	gets(s);
	for (i=0;i<n;i++){
		gets(s);
		int len=strlen(s);
		string tmp;
		tmp.clear();
		k=0;
		for (j=0;j<=len;j++)
			if (j==len || s[j]==' '){
				if (k==0){
					list1[i]=tmp;
					Name1.insert(make_pair(tmp,i));
				}else{
					g[i][k-1]=get_num(tmp,i==0);
				}
				k++;
				tmp.clear();
			}else{
				tmp+=s[j];
			}
	}
	for (i=0;i<n;i++){
		gets(s);
		int len=strlen(s),p;
		string tmp;
		tmp.clear();
		k=0;
		for (j=0;j<=len;j++)
			if (j==len || s[j]==' '){
				if (k==0){
					p=Name2[tmp];
				}else{
					rank[p][Name1[tmp]]=k-1;
				}
				k++;
				tmp.clear();
			}else{
				tmp+=s[j];
			}
	}
	memset(match,-1,sizeof(match));
	for (i=0;i<n;i++){
		a[i]=-1;
		Find(i);
	}
	printf("YES\n");
	for (i=0;i<n;i++) printf("%s %s\n",list1[match[i]].c_str(),list2[i].c_str());
	return 0;
}
