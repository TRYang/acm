#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

/***************** Suffix Automaton *******************/
#define maxn 1000010
#define char_set_size 26

struct node{
	node *fail;
	node *nxt[char_set_size];
	int len;
	int tot;
	node(){
		len = 0;
		tot = 0;
		fail = NULL;
		memset(nxt, 0, sizeof(nxt));
	}
};
struct SuffixAutomaton{
	//pointer to the first node and the last node
	//visit must start on *head, *tail is used for insert
	node *head, *tail;
	//the size of the automaton
	int tn;
	//node of the automaton, double size of the length of the string
	node T[maxn<<1];

	//initialization, must call this before insert
	void init(){
		tn = 1;
		head = tail = &T[0];
	}

	//insert operation
	//the first parameter is the char which insert to the last
	//the second parameter is the length of that prefix
	void insert(int c, int len){
		node *x = &T[tn++], *p;
		x->len = len;
		x->tot = 1;
		for (p = tail; p && p->nxt[c] == NULL; p = p->fail) p->nxt[c] = x;
		tail = x;
		if (p){
			node *q = p->nxt[c];
			if (p->len + 1 < q->len){
				node *np = &T[tn++];
				*np = *q;
				np->tot = 0;
				np->len = p->len + 1;
				q->fail = x->fail = np;
				for (;p && p->nxt[c] == q; p = p->fail) p->nxt[c] = np;
			}else x->fail = q;
		}else x->fail = head;
	}

	//must call this function after all insert opepration to calculate the total sub node of each node
	int c[maxn<<1], idx[maxn<<1];
	void finish(){
		memset(c, 0, sizeof(c));
		for (int i = 0; i < tn; i++) c[T[i].len]++;
		for (int i = 1; i < maxn; i++){
			c[i] += c[i-1];
			if (c[i] == 0) break;
		}
		for (int i = 0; i < tn; i++) idx[--c[T[i].len]] = i;
		for (int i = tn - 1; i; i--) T[idx[i]].fail->tot += T[idx[i]].tot;
	}

	long long find_substr(char *s, int n, int rep){
		node *p = head;
		int len = 0;
		for (int i = 0; i < n; i++){
			int c = s[i] - 'a';
			while (p && p->nxt[c] == NULL){
				p = p->fail;
				if (p) len = p->len;else len = 0;
			}
			if (p){
				p = p->nxt[c];
				++len;
			}else p = head;
		}
		long long ret = 0;
		for (int i = 0; i < rep; i++){
			if (len == n){
				ret += p->tot;
				--len;
				if (len <= p->fail->len) p = p->fail;
			}
			if (i == rep - 1) break;
			int c = s[i] - 'a';
			while (p && p->nxt[c] == NULL){
				p = p->fail;
				if (p) len = p->len;else len = 0;
			}
			if (p){
				p = p->nxt[c];
				++len;
			}else p = head;
		}
		return ret;
	}
} sam;
/********************* End *************************/

//kmp algorithm find the least repetend of a cyclical string
int pre[maxn];
int repetend(char *s, int n){
	pre[0] = -1;
	for (int i = 1, j = -1; i < n; i++){
		while (j > -1 && s[j + 1] != s[i]) j = pre[j];
		if (s[j + 1] == s[i]) ++j;
		pre[i] = j;
	}
	int ret = n - 1 - pre[n - 1];
	return n % ret == 0 ? ret : n;
}
/********************* End *************************/

char s[maxn];
int main(){
	scanf("%s",s);
	int n = strlen(s);
	sam.init();
	for (int i = 0; i < n; i++) sam.insert(s[i]-'a', i+1);
	sam.finish();
	int qn;
	for (scanf("%d",&qn); qn; qn--){
		scanf("%s",s);
		n = strlen(s);
		printf("%lld\n", sam.find_substr(s, n, repetend(s, n)));
	}
	return 0;
}
