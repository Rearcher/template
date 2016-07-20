/**
 * Created by Huan on 2015/5/15.
 */
public class QuickUF {
    private int[] id;
    private int[] sz;

    public QuickUF(int N){
        id = new int[N];  //record root
        sz = new int[N];  //record the tree size
        for(int i = 0; i < N; i++){
            id[i] = i;
            sz[i] = 1;
        }
    }

    private int root(int i){
        while(i != id[i]){
            id[i] = id[id[i]]; //path compression, to make the tree flatter
            i = id[i];
        }
        return i;
    }

    public boolean connected(int p, int q){
        return root(p) == root(q);
    }

    public void union(int p, int q){
        int prt = root(p);
        int qrt = root(q);
        if(prt == qrt) return;

        if(sz[prt] < sz[qrt]){  //to make small tree lower
            id[prt] = qrt;
            sz[qrt] += sz[prt];
        }
        else{
            id[qrt] = prt;
            sz[prt] += sz[qrt];
        }
    }

    public static void main(String[] args){

    }
}
