import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		
		try {
			inputStream = new FileInputStream("next.in");
			outputStream = new FileOutputStream("next.out");
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
	class Permutation extends ArrayList<Integer>{
		public int m;
		
		public Permutation(int m) {
			this.m = m;
		}
		
		public Permutation(int m, long sum) {
			this.m = m;
			long nn = sum / this.m;
			long rem = sum - nn * this.m;
			int c = this.m;
			if (nn == 0)
				return;
			c += rem / nn;
			rem %= nn;
			for (int i = 0; i < rem; i++) {
				this.add(c + 1);
			}
			for (int i = 0; i < nn - rem; i++) {
				this.add(c);
			}
		}
		
		public Permutation next() {
			long sum = 0;
			for (int i = this.size() - 1; i >= 0; --i) {
				while ((i == 0 || this.get(i) < this.get(i - 1)) && (sum > 0)) {
					sum--;
					this.set(i, this.get(i) + 1);
					long nn = sum / this.m;
					long rem = sum - nn * this.m;
					int maxc = this.m;
					if (nn == 0 && rem > 0)
						continue;
					if (nn > 0) {
						maxc += rem / nn;
						rem %= nn;
						if (rem > 0)
							maxc++;
					} else {
						maxc = -1;
					}
					
					if (maxc <= this.get(i)) {
						Permutation ans = new Permutation(this.m);
						ans.addAll(this.subList(0, i));
						ans.add(this.get(i));
						ans.addAll(new Permutation(this.m, sum));
						return ans;
					}
				}
				sum += this.get(i);
			}
			return new Permutation(m, sum + 1);
		}
		
	}
	public void solve(InputReader in, PrintWriter out) {
		int k = in.nextInt();
		int m = in.nextInt();
		Permutation st = new Permutation(m);
		for (int i = 0; i < k; i++) {
			int a = in.nextInt();
			st.add(a);
		}
		Permutation en = st.next();
		out.println(en.size());
		for (int i = 0; i < en.size(); i++) {
			out.print(en.get(i));
			out.print(" ");
		}
		out.println();
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
