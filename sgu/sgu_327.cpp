#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <iostream>
#define maxn 15

using namespace std;

string a[maxn],b[maxn];
int f[1<<maxn][maxn<<1];
short g[1<<maxn][maxn<<1];
int lcp[maxn<<1][maxn<<1];
int tag[maxn];
int n;
int tmask;
string ans_str;
void init(int x,int y){
	int l1=a[x].length(),l2=a[y].length();
	for (int i=1;i<=min(l1,l2);i++){
		if (a[x].substr(l1-i)==a[y].substr(0,i)){
			lcp[x][y]=i;
//			break;
		}
	}
	for (int i=1;i<=min(l1,l2);i++){
		if (a[x].substr(l1-i)==b[y].substr(0,i)){
			lcp[x][y+n]=i;
//			break;
		}
	}
	for (int i=1;i<=min(l1,l2);i++){
		if (b[x].substr(l1-i)==a[y].substr(0,i)){
			lcp[x+n][y]=i;
//			break;
		}
	}
	for (int i=1;i<=min(l1,l2);i++){
		if (b[x].substr(l1-i)==b[y].substr(0,i)){
			lcp[x+n][y+n]=i;
//			break;
		}
	}
}
void update(int mask,int p,int value,int fp){
	if (f[mask][p]==0 || value<f[mask][p]){
		f[mask][p]=value;
		g[mask][p]=fp;
	}
}
int calc(int p,int &type){
	string s;
	if (p<n) s=a[p];else s=b[p-n];
	int len=s.length();
	for (int i=len/2;i>0;i--){
		int tag=1;
		if (i*2+1<=len){
			tag=1;
			for (int j=0;j<i;j++)
				if (s[len-1-i-j-1]!=s[len-1-i+j+1]) tag=0;
			if (tag){
				type=1;
				return i;
			}
		}
		tag=1;
		for (int j=0;j<i;j++)
			if (s[len-i-1-j]!=s[len-i+j]) tag=0;
		if (tag){
			type=0;
			return i;
		}
	}
	type=1;
	return 0;
}
void Find(int mask,int p,int l){
	if (mask==tmask) return;
	string s=(p<n?a[p]:b[p-n]);
	int len=s.length();
	for (int i=len-1-l;i>=0;i--) ans_str+=s[i];
	int k=g[mask][p];
	Find(mask^(1<<(p%n)),k,lcp[k][p]);
}
int main(){
	cin>>n;
	for (int i=0;i<n;i++) cin>>a[i];
	for (int i=0;i<n;i++){
		b[i]="";
		int len=a[i].length();
		for (int j=len-1;j>=0;j--) b[i]+=a[i][j];
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			if (a[j].find(a[i])!=string::npos){
				if (a[j].length()>a[i].length() || j<i) tag[i]=1;
			}
			if (a[j].find(b[i])!=string::npos){
				if (a[j].length()>b[i].length() || j<i) tag[i]=1;
			}
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) init(i,j);
	tmask=0;
	for (int i=0;i<n;i++)
		if (tag[i]) tmask+=(1<<i);
	memset(f,0,sizeof(f));
	for (int i=0;i<n;i++)
		if (!tag[i]){
			f[tmask|(1<<i)][i]=a[i].length();
			g[tmask|(1<<i)][i]=i;
			f[tmask|(1<<i)][i+n]=b[i].length();
			g[tmask|(1<<i)][i+n]=i+n;
		}
	for (int mask=0;mask<(1<<n);mask++)
		for (int i=0;i<(n<<1);i++)
			if (f[mask][i]>0){
				for (int j=0;j<n;j++)
					if ((mask&(1<<j))==0){
						update(mask|(1<<j),j,f[mask][i]+a[j].length()-lcp[i][j],i);
						update(mask|(1<<j),j+n,f[mask][i]+b[j].length()-lcp[i][j+n],i);
					}
			}
	int ans=0,ansx=0;
	int type;
	for (int i=0;i<(n<<1);i++)
		if (f[(1<<n)-1][i]>0){
			int tmp=(f[(1<<n)-1][i]-calc(i,type))*2-type;
			if (ans==0 || tmp<ans){
				ans=tmp;
				ansx=i;
			}
		}
	ans_str="";
	Find((1<<n)-1,ansx,calc(ansx,type));
	for (int i=ans_str.length()-1;i>=type;i--) printf("%c",ans_str[i]);
	printf("%s\n",ans_str.c_str());
	return 0;
}
