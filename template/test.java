import java.util.*;
import java.io.*;
import java.math.*;

public class test {
  static BufferedReader reader;
  static StringTokenizer tokenizer;

  public static void main(String [] args) throws IOException {
    reader = new BufferedReader(new InputStreamReader(System.in));
    tokenizer = null;
  }

  public static String nextToken() throws IOException {
    while (tokenizer == null || !tokenizer.hasMoreTokens()) {
      tokenizer = new StringTokenizer(reader.readLine());
    }
    return tokenizer.nextToken();
  }

  public static int nextInt() throws IOException {
    return Integer.parseInt(nextToken());
  }
}
