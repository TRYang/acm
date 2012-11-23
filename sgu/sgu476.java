import java.util.*;
import java.math.BigInteger;

public class sgu476{
	public static int g(int x){
		return (3*x-1)*(3*x-2)/2;
	}
	public static void main(String [] arg){
		int n=0,m=0;
		int [][] a=new int[1010][3];
		Scanner In=new Scanner(System.in);
		n=In.nextInt();
		m=In.nextInt();
		for (int i=0;i<m;i++)
			for (int j=0;j<3;j++) a[i][j]=In.nextInt();
//		System.out.println(n);
		BigInteger [] f=new BigInteger[1010];
		f[0]=BigInteger.ONE;
		f[1]=BigInteger.ONE;
		for (int i=2;i<=n;i++)
			f[i]=f[i-1].multiply(BigInteger.valueOf(g(i)));
		BigInteger ans=f[n];
		int [] tag=new int[3010];
		int [] sum=new int[1010];
		for (int i=0;i<=n;i++) tag[i]=-1;
		for (int i=0;i<=n;i++) sum[i]=0;
		for (int mask=1;mask<(1<<m);mask++){
			int flag=1,tot=0;
			for (int i=0;i<m;i++)
				if ((mask&(1<<i))>0){
					for (int j=0;j<3;j++){
						if (tag[a[i][j]]==mask) flag=0;
						tag[a[i][j]]=mask;
					}
					++tot;
				}
			if (flag==1){
				if (tot%2==1) sum[n-tot]--;else sum[n-tot]++;
			}
		}
		BigInteger temp;
		for (int i=0;i<n;i++){
			if (sum[i]==0) continue;
			temp=f[i].multiply(BigInteger.valueOf(sum[i]));
			ans=ans.add(temp);
		}
		System.out.println(ans);
	}
}
