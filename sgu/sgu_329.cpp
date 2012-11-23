#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#define maxcnt 600000
#define hashsize 9701

using namespace std;

typedef long long LL;

struct hashtable{
	int st[hashsize];
	int aim[maxcnt],nxt[maxcnt],ln;
	int pos[maxcnt];
	int find(int value){
		int p=value%hashsize;
		for (int i=st[p];i!=-1;i=nxt[i])
			if (aim[i]==value) return pos[i];
		return -1;
	}
	void insert(int value,int P){
		int p=value%hashsize;
		aim[ln]=value;
		pos[ln]=P;
		nxt[ln]=st[p];
		st[p]=ln++;
	}
	void clear(){
		memset(st,-1,sizeof(st));
		ln=0;
	}
} h[2];
pair<int,LL> q[2][maxcnt];
map<int,LL> sr;
int qn[2];
int nc[5];
int n;
LL ans;
#define rv(x,p) (x&(((1<<(n<<1))-1)^(3<<(p<<1))))
void work(int mask){
	int tc[5];
	for (int i=0;i<4;i++) tc[i]=0;
	for (int i=0;i<n;i++){
		int st=(mask>>(i*3))&7,tt=0;
		while (st) tt+=(st&1),st>>=1;
		tc[tt]++;
	}
	for (int i=0;i<4;i++)
		if (tc[i]>nc[i]) return;
		else tc[i]=nc[i]-tc[i];
	int tmask=0;
	for (int i=n-1;i>=0;i--){
		int st=(mask>>(i*3))&3;
		tmask=(tmask<<2)|st;
	}
	for (int i=3;i>=0;i--) tmask=(tmask<<5)|tc[i];
	int sp=h[0].find(tmask);
	if (sp==-1){
		q[0][qn[0]]=make_pair(tmask,1);
		h[0].insert(tmask,qn[0]++);
	}else q[0][sp].second++;
}
void calc(){
	int tc[5];
	int now=0,next;
	for (int i=n-1;i>0;i--){
		next=(now^1);
		h[next].clear();
		qn[next]=0;
		for (int p=0;p<qn[now];p++){
			int smask=q[now][p].first;
			smask>>=21;
			smask&=(1<<(i<<1))-1;
			smask=(smask<<20)|(q[now][p].first&((1<<20)-1));
			int sp=h[next].find(smask);
			if (sp==-1){
				q[next][qn[next]]=make_pair(smask,q[now][p].second);
				h[next].insert(smask,qn[next]++);
			}else q[next][sp].second+=q[now][p].second;
		}
		now=next;
		for (int j=0;j<i;j++){
			next=(now^1);
			qn[next]=0;
			h[next].clear();
			for (int p=0;p<qn[now];p++){
				int smask=q[now][p].first;
				LL value=q[now][p].second;
				for (int k=0;k<4;k++) tc[k]=0;
				for (int k=0;k<4;k++) tc[k]=(smask>>(k*5))&31;
				smask>>=20;
				int ch1=(smask>>(j<<1))&1,ch2=(smask>>(j<<1))&2;
				ch2>>=1;
				for (int ch3=0;ch3<2;ch3++)
					if (tc[ch1+ch2+ch3]>0){
						tc[ch1+ch2+ch3]--;
						for (int ch4=0;ch4<2;ch4++)
							for (int ch5=0;ch5<2;ch5++)
								if (tc[ch3+ch4+ch5]>0){
									tc[ch3+ch4+ch5]--;
									int cmask=rv(smask,j);
									if (ch4) cmask|=(1<<(j<<1));
									if (ch5) cmask|=(1<<((j<<1)+1));
									for (int k=3;k>=0;k--) cmask=(cmask<<5)|tc[k];
									int sp=h[next].find(cmask);
									if (sp==-1){
										q[next][qn[next]]=make_pair(cmask,value);
										h[next].insert(cmask,qn[next]++);
									}else q[next][sp].second+=value;
									tc[ch3+ch4+ch5]++;
								}
						tc[ch1+ch2+ch3]++;
					}
			}
			now=next;
		}
	}
	for (int i=0;i<qn[now];i++) ans+=q[now][i].second;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<4;i++) scanf("%d",nc+i);
	ans=0;
	h[0].clear();
	qn[0]=0;
	for (int mask=0;mask<1<<(n*3);mask++) work(mask);
	calc();
	printf("%lld\n",ans);
	return 0;
}
