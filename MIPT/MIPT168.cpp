#include <stdio.h>
#include <string.h>
#include <string>
#define maxn 1000010
#define maxq 2000010

using namespace std;

const string pat="<>(){}[]";
int st[maxn],aim[maxq],nxt[maxq],id[maxq],ln;
bool ans[maxq],tag[maxn];
char s[maxn];
int stack[maxn],stn;
int stack2[maxn],stn2;
int n;
int qn;
void in_edge(int x,int y,int z){
	aim[ln]=y;
	nxt[ln]=st[x];
	id[ln]=z;
	st[x]=ln++;
}
int main(){
	gets(s);
	n=strlen(s);
	for (int i=0;i<n;i++) s[i]=pat.find(s[i]);
	scanf("%d",&qn);
	memset(st,-1,sizeof(st));
	ln=0;
	char c=getchar();
	while (c!='\n') c=getchar();
	for (int i=0;i<qn;i++){
		int st=0,en=0;
		while (1){
			c=getchar();
			if (c>='0' && c<='9'){
				st=c-'0';
				break;
			}
		}
		while (1){
			c=getchar();
			if (c<'0' || c>'9') break;
			st=st*10+c-'0';
		}
		while (1){
			c=getchar();
			if (c>='0' && c<='9'){
				en=c-'0';
				break;
			}
		}
		while (1){
			c=getchar();
			if (c<'0' || c>'9') break;
			en=en*10+c-'0';
		}
		while (c!='\n') c=getchar();
		--st,--en;
		if (s[en]%2==0) ans[i]=false;else in_edge(en,st,i);
	}
	stn=stn2=0;
	stack[0]=-1;
	for (int i=0;i<n;i++){
		int p=s[i];
		if ((p&1)==0){
			stack[++stn]=i;
			stack2[++stn2]=i;
		}else{
			if (stn==0 || s[stack[stn]]!=(p^1)){
				stn=stn2=0;
				stack[0]=i;
				for (int j=st[i];j!=-1;j=nxt[j]) ans[id[j]]=false;
			}else{
				int pos=stack[stn--];
				tag[pos]=true;
				while (stn2 && stack2[stn2]>pos) tag[stack2[stn2--]]=false;
				
				for (int j=st[i];j!=-1;j=nxt[j])
					if (aim[j]<=stack[stn] || !tag[aim[j]]) ans[id[j]]=false;else ans[id[j]]=true;
			}
		}
	}
	for (int i=0;i<qn;i++) puts(ans[i]?"Y":"N");
	return 0;
}