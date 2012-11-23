import java.util.*;
import java.math.*;

public class sgu389{
	static final int maxn=100010;
	static final int mod=1000000007;
	static long [] fac=new long[maxn];
	static long [] dfac=new long[maxn];
	public static long C(int n,int m){
		return ((fac[n]*dfac[n-m])%mod*dfac[m])%mod;
	}
	public static long POW(long x,int y){
		long ret=1;
		while (y>0){
			if ((y&1)>0) ret=(ret*x)%mod;
			x=(x*x)%mod;
			y>>=1;
		}
		return ret;
	}
	public static void main(String [] arg){
		fac[0]=1;
		for (int i=1;i<maxn;i++) fac[i]=(fac[i-1]*i)%mod;
		for (int i=0;i<maxn;i++) dfac[i]=POW(fac[i],mod-2);
		Scanner in=new Scanner(System.in);
		String [] s=new String[3];
		for (int i=0;i<3;i++) s[i]=in.next();
		int [] t=new int[3];
		for (int i=0;i<3;i++) t[i]=0;
		int n=s[0].length(),tot=0;
		for (int i=0;i<n;i++){
			int v1=s[0].charAt(i)-'0',v2=s[1].charAt(i)-'0',v3=s[2].charAt(i)-'0';
			if (v1==v2 && v2==v3) ++tot;
			if ((v1==1 && v2==0 && v3==0) || (v1==0 && v2==1 && v3==1)){
				++t[0];
			}
			if ((v1==0 && v2==1 && v3==0) || (v1==1 && v2==0 && v3==1)){
				++t[1];
			}
			if ((v1==0 && v2==0 && v3==1) || (v1==1 && v2==1 && v3==0)){
				++t[2];
			}
		}

	}
}
