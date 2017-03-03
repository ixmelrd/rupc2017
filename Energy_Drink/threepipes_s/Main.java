import java.io.BufferedReader;
import java.io.Closeable;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

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
		Drink[] drink = new Drink[n*2];
		for(int i=0; i<n; i++){
			int a = in.nextInt();
			int b = in.nextInt();
			drink[i*2] = new Drink(a, b, 0);
			drink[i*2+1] = new Drink(b, a, 1);
		}
		Arrays.sort(drink);
		System.out.println(lis(drink));
		in.close();
	}
	
	int lis(Drink[] drink){
		int n = drink.length;
		int[] lis = new int[n];
		Arrays.fill(lis, Integer.MAX_VALUE);
		for(int i=0; i<n; i++){
			int p = bSearch(lis, drink[i].b);
			if(p%2!=drink[i].s) continue;
			lis[p] = drink[i].b;
		}
		for(int i=n-1; i>=0; i--){
			if(lis[i]!=Integer.MAX_VALUE) return i+1;
		}
		return -1;
	}
	
	// return position
	int bSearch(int[] a, int v){
		int ans = a.length;
		int left = 0, right = ans-1;
		while(left<=right){
			int mid = (left+right)/2;
			if(v<=a[mid]){
				ans = mid;
				right = mid-1;
			}else{
				left = mid+1;
			}
		}
		return ans;
	}
}

class Drink implements Comparable<Drink>{
	int a, b, s;
	Drink(int a, int b, int s){
		this.a = a;
		this.b = b;
		this.s = s;
	}
	@Override
	public int compareTo(Drink o) {
		if(a!=o.a) return a-o.a;
		return o.b-b;
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