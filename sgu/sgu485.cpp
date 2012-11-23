#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#define maxn 100
#define hashsize 100017
#define maxq 5000000

using namespace std;

struct hashtable{
	int st[hashsize];
	int ax[maxq],am[maxq],ap[maxq],nxt[maxq],ln;
	void clear(){
		memset(st,-1,sizeof(st));
		ln=0;
	}
	void insert(int x,int mask,int pos){
		int p=((mask<<5)|x)%hashsize;
		ax[ln]=x;
		am[ln]=mask;
		ap[ln]=pos;
		nxt[ln]=st[p];
		st[p]=ln++;
	}
	int find(int x,int mask){
		int p=((mask<<5)|x)%hashsize;
		for (int i=st[p];i!=-1;i=nxt[i])
			if (ax[i]==x && am[i]==mask) return ap[i];
		return -1;
	}
} h[2];
struct node{
	int x,mask,value;
	node(){}
	node(int _x,int _m,int _v){
		x=_x;
		mask=_m;
		value=_v;
	}
};
node q[2][maxq];
int qn[2];
int a[maxn];
int n;
int now,next;
int ans;
int px;
bool cmp(int x,int y){
	return x>y;
}
void check(int p,int mask,int value){
//	printf("(p=%d, mask=%d, value=%d)\n",p,mask,value);
	int tag[maxn];
	memset(tag,0,sizeof(tag));
	for (int i=0;i<n;i++)
		if ((mask&(1<<i))>0) tag[p-1-i]=1;
	int x=2*n-p;
	for (int i=0,j=p;i<2*n;i++)
		if (tag[i]){
			value+=(a[i]-a[3*n-x])*a[j];
			++j;
			--x;
		}
	if (value>ans) ans=value;
}
void update(int left,int x,int mask,int value){
	if (n>20 && value+left*(a[0]-a[2*n])*a[1]/2<=ans) return;
	int p=h[next].find(x,mask);
	if (p==-1){
		if (qn[next]==maxq){
			if (rand()%3==0) return;
			int d=rand()%maxq;
			if (value<q[next][d].value-1000000) return;
			q[next][d]=node(x,mask,value);
		}else{
			h[next].insert(x,mask,qn[next]);
			q[next][qn[next]++]=node(x,mask,value);
		}
	}else{
		q[next][p].value=max(q[next][p].value,value);
	}
}
int work1(){
	int ret=0;
	for (int i=0;i<n;i+=2) ret+=(a[i]-a[2*n+i])*a[i+1];
	return ret;
}
int work2(){
	int ret=0;
	for (int i=0;i<n;i++) ret+=(a[i]-a[2*n+i])*a[n+i];
	return ret;
}
int main(){
	int tn;
	scanf("%d%d",&tn,&n);
	for (int cp=1;cp<=tn;cp++){
		for (int i=0;i<3*n;i++) scanf("%d",a+i);
		sort(a,a+3*n,cmp);
		reverse(a+2*n,a+3*n);
//		for (int i=0;i<3*n;i++) printf("%d ",a[i]);puts("");
		now=0;
		h[0].clear();
		h[0].insert(0,0,0);
		qn[0]=1;
		q[0][0]=node(0,0,0);
		ans=max(work1(),work2());
		px=(ans/n);
		for (int i=0;i<n;i++){
			next=(now^1);
			qn[next]=0;
			h[next].clear();
//			printf("i=%d:\n",i);
			for (int p=0;p<qn[now];p++){
				int x=q[now][p].x,mask=q[now][p].mask;
				int value=q[now][p].value;
//				printf("(x=%d, mask=%d, value=%d)\n",x,mask,value);
				if (x==n){
					check(i,mask,value);
				}else{
					int left=(x-(i-x)+(2*n-i))/2;
					if (x<n) update(left,x+1,(mask<<1)|1,value);
					if (i-x<x){
						int d=-1;
						for (int k=n-1;k>=0;k--)
							if (i-k>=0 && (mask&(1<<k))>0){
								d=k;
								break;
							}
						update(left-1,x,(mask^(1<<d))<<1,value+(a[i-1-d]-a[2*n+i-x])*a[i]);
					}
				}
			}
			now=next;
		}
		int count[maxn];
		memset(count,0,sizeof(count));
		for (int p=0;p<qn[now];p++){
			int x=q[now][p].x;
			int ln=n-x;
			count[ln]++;
		}
		ans=0;
		for (int i=0;i<=n;i++){
			printf("i=%d, %d\n",i,count[i]);
			ans=max(ans,count[i]*count[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
