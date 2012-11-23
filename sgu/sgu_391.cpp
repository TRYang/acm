#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 1000010

using namespace std;

struct node{
    int x,y;
    void read(){
        scanf("%d%d",&x,&y);
    }
} a[maxn];
int cx[maxn],cy[maxn];
unsigned long long h[maxn],hv[maxn],POW[maxn];
int xn,yn;
int n,m,N;
int check(){
    for (int i=0;i<N;i++){
        cx[a[i].x]++;
        cy[a[i].y]++;
    }
    for (int i=1;i<=n;i++)
        if (cx[i]) ++xn;
    for (int i=1;i<=m;i++)
        if (cy[i]) ++yn;
    for (int i=1;i<=n;i++)
        if (cx[i] && cx[i]!=yn) return 0;
    for (int i=1;i<=m;i++)
        if (cy[i] && cy[i]!=xn) return 0;
    return 1;
}
int check2(int *cx,int n){
    POW[0]=1;
    for (int i=1;i<=n;i++) POW[i]=POW[i-1]*19;
    h[0]=0;
    for (int i=1;i<=n;i++)
        if (cx[i]) h[i]=h[i-1]*19+11;else h[i]=h[i-1]*19+7;
    hv[n+1]=0;
    for (int i=n;i>0;i--)
        if (cx[i]) hv[i]=hv[i+1]*19+11;else hv[i]=hv[i+1]*19+7;
	int s=1,t=n;
	int l=s+1,r=t-1;
	while (1){
		int flag=0;
		while (l<=t){
			if (l-s>t-l+1){
				++l;
				break;
			}
			unsigned long long t1=h[l-1]-h[s-1]*POW[l-s];
			unsigned long long t2=hv[l]-hv[l+(l-s)]*POW[l-s];
			if (t1==t2){
				s=l;
				++l;
				flag=1;
				break;
			}
			++l;
		}
		while (r>=s){
			if (t-r>r-s+1){
				--r;
				break;
			}
			unsigned long long t1=h[r]-h[r-(t-r)]*POW[t-r];
			unsigned long long t2=hv[r+1]-hv[t+1]*POW[t-r];
			if (t1==t2){
				t=r;
				--r;
				flag=1;
				break;
			}
			--r;
		}
		if (!flag) break;
	}
    int tot=0;
    for (int i=s;i<=t;i++)
        if (cx[i]) ++tot;
    return tot==1;
}
int main(){
    scanf("%d%d%d",&n,&m,&N);
    for (int i=0;i<N;i++) a[i].read();
    if (check() && check2(cx,n) && check2(cy,m)) puts("YES");else puts("NO");
    return 0;
}                                 
