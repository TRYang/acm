#define maxn 100000
#define maxm 26
int trie[maxn][maxm];
int tag[maxn];
int fail[maxn];
int q[maxn];
int tn;
int main(){
	//Init
	memset(trie,,sizeof(trie));		//��n�ܴ�ʱ,��������,ÿ��չ���һ��
	memset(tag,0,sizeof(tag));
	tn=1;
	
	//Insert
	char s;
	int k=0;
	for (int i=0;i<strlen(s);k=trie[k][s[i++]])
		if (trie[k][s[i]]==0) trie[k][s[i]]=tn++;	//New һ�����
	tag[k]=1;										//���Ϊ����
	
	//Make fail
	memset(fail,0,sizeof(fail));
	int qn=0;
	for (int i=0;i<maxm;i++)
		if (trie[0][i])	q[qn++]=trie[0][i];
		
	for (int p=0;p<qn;p++)
		for (int i=0;i<maxm;i++)
			if (trie[q[p]][i]){
				int y=trie[q[p]][i];
				fail[y]=trie[fail[q[p]]][i];
				q[qn++]=y;
				tag[y] |= tag[q[p]];				//�󳤶ȸ�Ϊmax()
			}else trie[q[p]][i]=trie[fail[q[p]]][i];
	
	//�Ӹ���ʼ�߼���
	return 0;
}