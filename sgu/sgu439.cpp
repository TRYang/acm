#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 2000010
#define P 127

using namespace std;

char s[maxn],t[maxn];
int Z[maxn<<1];
int lcp[maxn];
unsigned long long h[maxn],hv[maxn>>1],POW[maxn];
int n,m;
int find_minimum_presentation(char *s,int n){
	if (n==1) return 0;
	int i=0,j=1,k=0;
	while (1){
		while (k<n && s[i+k]==s[j+k]) ++k;
		if (k==n) break;
		if (s[i+k]<s[j+k]){
			if (j<i) j=i+1;else j+=k+1;
		}else{
			if (i<j) i=j+1;else i+=k+1;
		}
		k=0;
		if (i>=n || j>=n) break;
	}
	return min(i,j);
}
void Prepare(char *s,int n){
	int p=0;
	Z[0]=0;
	for (int i=1;i<n;i++){
		int len;
		if (p==0 || p+Z[p]-1<i) len=0;else len=min(Z[i-p],p+Z[p]-i+1);
		while (i+len<n && s[i+len]==s[len]) ++len;
		Z[i]=len;
		if (i+Z[i]>p+Z[p]) p=i;
	}
//	for (int i=0;i<n;i++) printf("%d ",Z[i]);puts("");
}
void Make_lcp(char *s,int n,char *t,int m){
	int p=-1;
	for (int i=0;i<n;i++){
		int len;
		if (p==-1 || p+lcp[p]-1<i) len=0;else len=min(Z[i-p],p+lcp[p]-i+1);
		while (i+len<n && len<m && s[i+len]==t[len]) ++len;
		lcp[i]=len;
		if (p==-1 || i+lcp[i]>p+lcp[p]) p=i;
	}
//	for (int i=0;i<n;i++) printf("%c",s[i]);puts("");
//	for (int i=0;i<n;i++) printf("%d ",lcp[i]);puts("");
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	scanf("%s",t);
	for (int i=0;i<n;i++) s[n+i]=s[i];
	for (int i=0;i<m;i++) t[m+i]=t[i];
	int p=find_minimum_presentation(t,m);
	for (int i=0;i<m;i++) t[i]=t[p+i];
	for (int i=0;i<m;i++) printf("%c",t[i]);puts("");
	Prepare(t,m);
	Make_lcp(s,n<<1,t,m);
	POW[0]=1;
	for (int i=1;i<n<<1;i++) POW[i]=POW[i-1]*P;
	h[0]=0;
	for (int i=0;i<n<<1;i++) h[i+1]=h[i]*P+s[i];
	hv[0]=0;
	for (int i=0;i<m;i++) hv[i+1]=hv[i]*P+t[i];
	int ans=-1;
	for (int i=0;i<n;i++){
		int flag=(lcp[i]>=m-1);
		if (!flag){
			unsigned long long t1=h[i+m]-h[i+lcp[i]+1]*POW[m-1-lcp[i]];
			unsigned long long t2=hv[m]-hv[lcp[i]+1]*POW[m-1-lcp[i]];
			if (t1==t2) flag=1;
		}
		if (flag)
			if (ans==-1 || min(i,n-i)<min(ans,n-ans)) ans=i;
	}
	for (int i=0;i<n;i++) s[i]=s[ans+i];
	for (int i=0;i<n;i++) printf("%c",s[i]);puts("");
	return 0;
}
