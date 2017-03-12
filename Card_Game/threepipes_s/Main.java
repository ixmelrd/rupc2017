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
	
	@SuppressWarnings("unchecked")
	void solve() throws IOException{
		ContestScanner in = new ContestScanner();
		int n = in.nextInt();
		int m = in.nextInt();
		int r = in.nextInt();
		int q = in.nextInt();
		node = new List[n];
		for(int i=0; i<n; i++){
			node[i] = new ArrayList<>();
		}
		for(int i=0; i<m; i++){
			int a = in.nextInt()-1;
			int b = in.nextInt()-1;
			int c = in.nextInt();
			node[b].add(new Edge(a, c));
		}
		PriorityQueue<Pos> qu = new PriorityQueue<>();
		// 各地点からグループRに到達する最小コスト
		int[][] dist = new int[r][];
		for(int i=0; i<r; i++){
			for(int j=i; j<n; j+=r){
				qu.add(new Pos(j, 0));
			}
			dist[i] = dijkstra(qu, n);
		}
		long ans = 0;
		for(int i=0; i<q; i++){
			int x = in.nextInt()-1;
			int y = in.nextInt()-1;
			int z = in.nextInt();
			int min = inf;
			for(int j=0; j<r; j++){
				min = Math.min(min, dist[j][x]+dist[j][y]);
			}
			ans += Math.max(0, z-min);
		}
		System.out.println(ans);
		in.close();
	}
	
	final int max_gain = 100000;
	final int inf = Integer.MAX_VALUE/2;
	List<Edge>[] node;
	int[] dijkstra(PriorityQueue<Pos> qu, int n){
		int[] dist = new int[n];
		Arrays.fill(dist, inf);
		while(!qu.isEmpty()){
			Pos pos = qu.poll();
			int p = pos.p;
			if(dist[p]<=pos.dist) continue;
			dist[p] = pos.dist;
			for(Edge e: node[p]){
				int newdist = dist[p] + e.cost;
				// 報酬を超える交換は行わない
				if(newdist>max_gain) continue;
				qu.add(new Pos(e.to, newdist));
			}
		}
		return dist;
	}
}

class Pos implements Comparable<Pos>{
	int p, dist;
	Pos(int p, int d){
		this.p = p;
		dist = d;
	}
	@Override
	public int compareTo(Pos o) {
		return dist-o.dist;
	}
}

class Edge{
	int to, cost;
	Edge(int to, int cost){
		this.to = to;
		this.cost = cost;
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