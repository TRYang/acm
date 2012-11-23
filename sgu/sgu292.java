import java.util.*;
import java.math.*;

public class sgu292{
	public static void main(String arg[]){
		Scanner in=new Scanner(System.in);
		BigInteger n=in.nextBigInteger();
		BigInteger m=in.nextBigInteger();
		BigInteger K=in.nextBigInteger();
		if (K.compareTo(n)<=0 || K.compareTo(m)<=0){
			if (K.compareTo(n)>0){
				BigInteger ans=m.divide(K);
				ans=ans.multiply(n);
				System.out.println(ans);
				return;
			}
			if (K.compareTo(m)>0){
				BigInteger ans=n.divide(K);
				ans=ans.multiply(m);
				System.out.println(ans);
				return;
			}
			BigInteger t1=n.mod(K);
			BigInteger t2=m.mod(K);
			BigInteger c1=K.subtract(t1);
			BigInteger c2=K.subtract(t2);

			BigInteger ans1=n.multiply(m);
			ans1=ans1.subtract(t1.multiply(t2));
			ans1=ans1.divide(K);

			BigInteger ans2=n.multiply(m);
			ans2=ans2.subtract(c1.multiply(c2));
			ans2=ans2.divide(K);
			ans1=ans1.max(ans2);

			System.out.println(ans1);
		}else{
			System.out.println("0");
		}
	}
}
