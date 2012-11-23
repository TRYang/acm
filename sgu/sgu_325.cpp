#include <stdio.h>
#include <string.h>
#define maxn 1000010
char s[maxn];
int pre[maxn];
int a[maxn],tag[maxn];
int t[maxn];
int c[26],pos[26];
int n;
long long ans;

void ins(int p){
	for (;p<=n;p+=(p&(p^(p-1)))) t[p]++;
}

int ask(int p){
	int res=0;
	for (;p>0;p-=(p&(p^(p-1)))) res+=t[p];
	return res;
}

int work(){
	int i,j,k,tp;
	memset(c,0,sizeof(c));
	memset(pos,-1,sizeof(pos));
	for (i=0;i<n;i++){
		tag[i]=0;
		a[i]=s[i]-'A';
		c[a[i]]++;
		if (pos[a[i]]>-1){
			pre[i]=pos[a[i]];
		}else pre[i]=-1;
		pos[a[i]]=i;
	}
	for (i=k=0;i<26;i++)
		if ((c[i]&1)>0){
			if (k || (n&1)==0) return 0;
			k=1;
		}
	ans=0;
	for (i=tp=0;i<n;i++)
		if (!tag[i]){
			if (i==pos[a[i]]){
				ans+=(n>>1)-tp;
				continue;
			}
			tp++;
			k=pos[a[i]];
			pos[a[i]]=pre[pos[a[i]]];
			ans+=(n-k-1)-ask(n-k-1);
			ins(n-k);
			tag[k]=tag[i]=1;
		}
	return 1;
}

int main(){
	int i,j,k;
	scanf("%s",s);
	n=strlen(s);
	if (work()) printf("%I64d\n",ans);else printf("-1\n");
	return 0;
}
