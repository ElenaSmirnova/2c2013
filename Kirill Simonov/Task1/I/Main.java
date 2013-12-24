import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		
		try {
			inputStream = new FileInputStream("arranger.in");
			outputStream = new FileOutputStream("arranger.out");
		} catch (FileNotFoundException e) {
			System.err.println("File not found");
			return;
		}
		
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Solver solver = new Solver();
		solver.solve(in, out);
		out.close();
	}
}

class Solver {
	public void solve(InputReader in, PrintWriter out) {
		int n = in.nextInt();
		int k = in.nextInt();
		long[] st = new long[k + 1];
		st[0] = 1;
		for (int i = 1; i <= k; i++) {
			st[i] = st[i - 1] * (n - k + i);
		}
		int[] use = new int[n];
		for (int i = 0; i < n; i++) {
			use[i] = i + 1;
		}
		long ans = 0;
		for (int i = k - 1; i >= 0; --i) {
			int a = in.nextInt();
			int c = 0;
			for (int j = 0; j < n; j++) {
				if (use[j] == a) {
					use[j] = 0;
					break;
				}
				if (use[j] != 0)
					c++;
			}
			
			
			ans += st[i] * c;
		}
		
		out.print(ans);
	}
}

class InputReader {
	private BufferedReader reader;
	private StringTokenizer tokenizer;

	public InputReader(InputStream stream) {
		reader = new BufferedReader(new InputStreamReader(stream));
		tokenizer = null;
	}

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public long nextLong() {
		return Long.parseLong(next());
	}

	public int nextInt() {
		return Integer.parseInt(next());
	}

	public double nextDouble() {
		return Double.parseDouble(next());
	}
}
