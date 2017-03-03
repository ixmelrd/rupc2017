import java.io.BufferedReader;
import java.io.Closeable;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class Main {
	public static void main(String[] args) {
		try{
			new Main().solve();
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	void solve() throws IOException{
		ContestScanner in = new ContestScanner();
		int n = in.nextInt();
		int m = in.nextInt();
		int k = in.nextInt();
		MinCostFlow mcf = new MinCostFlow(n+m+2, n-k);
		int[] a = new int[n];
		final int s = n+m;
		final int t = n+m+1;
		int first = 0;
		for(int i=0; i<n; i++){
			a[i] = in.nextInt();
			first += a[i];
			mcf.edge(s, i, 1, 0);
		}
		for(int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				int b = in.nextInt();
				if(b<a[j]) continue;
				mcf.edge(j, n+i, 1, 100-(b-a[j]));
			}
		}
		for(int i=0; i<m; i++){
			int time = in.nextInt();
			mcf.edge(n+i, t, time, 0);
		}
		int score_plus = -mcf.flow(s, t);
		System.out.println(first+score_plus+(n-k-mcf.f)*100);
		in.close();
	}
}

class MinCostFlow{
	final int n;
	int f;
	List<Edge>[] node;
	@SuppressWarnings("unchecked")
	public MinCostFlow(int n, int f) {
		this.n = n;
		this.f = f;
		node = new List[n];
		for(int i=0; i<n; i++) node[i] = new ArrayList<>();
	}
	void edge(int from, int to, int cap, int cost){
		Edge e = new Edge(to, cap, cost);
		Edge r = new Edge(from, 0, -cost);
		e.rev = r;
		r.rev = e;
		node[from].add(e);
		node[to].add(r);
	}
	int flow(int s, int t){
		int[] h = new int[n];
		int[] dist = new int[n];
		int[] preV = new int[n];
		int[] preE = new int[n];
		final int inf = Integer.MAX_VALUE;
		PriorityQueue<Pos> qu = new PriorityQueue<>();
		int res = 0;
		while(f>0){
			Arrays.fill(dist, inf);
			dist[s] = 0;
			qu.clear();
			qu.add(new Pos(s, 0));
			while(!qu.isEmpty()){
				Pos p = qu.poll();
				if(dist[p.v]<p.d) continue;
				final int sz = node[p.v].size();
				for(int i=0; i<sz; i++){
					Edge e = node[p.v].get(i);
					final int nd = e.cost+p.d + h[p.v]-h[e.to];
					if(e.cap>0 && nd < dist[e.to]){
						preV[e.to] = p.v;
						preE[e.to] = i;
						dist[e.to] = nd;
						qu.add(new Pos(e.to, nd));
					}
				}
			}
			if(dist[t]==inf) break;
			for(int i=0; i<n; i++) h[i] += dist[i];
			int minf = f;
			for(int i=t; i!=s; i=preV[i]){
				minf = Math.min(minf, node[preV[i]].get(preE[i]).cap);
			}
			f -= minf;
			res += minf*h[t];
			for(int i=t; i!=s; i=preV[i]){
				node[preV[i]].get(preE[i]).cap -= minf;
				node[preV[i]].get(preE[i]).rev.cap += minf;
			}
		}
		return res;
	}
}

class Pos implements Comparable<Pos>{
	int v, d;
	public Pos(int v, int d) {
		this.v = v;
		this.d = d;
	}
	@Override
	public int compareTo(Pos o) {
		return d-o.d;
	}
}

class Edge{
	int to, cap, cost;
	Edge rev;
	Edge(int t, int c, int co){
		to = t;
		cap = c;
		cost = co;
	}
	void rev(Edge r){
		rev = r;
	}
}

class ContestScanner implements Closeable{
	private BufferedReader in;private int c=-2;
	public ContestScanner()throws IOException 
	{in=new BufferedReader(new InputStreamReader(System.in));}
	public ContestScanner(String filename)throws IOException
	{in=new BufferedReader(new InputStreamReader(new FileInputStream(filename)));}
	public String nextToken()throws IOException {
		StringBuilder sb=new StringBuilder();
		while((c=in.read())!=-1&&Character.isWhitespace(c));
		while(c!=-1&&!Character.isWhitespace(c)){sb.append((char)c);c=in.read();}
		return sb.toString();
	}
	public String readLine()throws IOException{
		StringBuilder sb=new StringBuilder();if(c==-2)c=in.read();
		while(c!=-1&&c!='\n'&&c!='\r'){sb.append((char)c);c=in.read();}
		return sb.toString();
	}
	public long nextLong()throws IOException,NumberFormatException
	{return Long.parseLong(nextToken());}
	public int nextInt()throws NumberFormatException,IOException
	{return(int)nextLong();}
	public double nextDouble()throws NumberFormatException,IOException 
	{return Double.parseDouble(nextToken());}
	public void close() throws IOException {in.close();}
}