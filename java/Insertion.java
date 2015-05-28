/**
 * Created by rahul on 5/27/15.
 */
public class Insertion {
    private int N = 10000;
    private int[] a = new int[N];

    public void init(){
        for(int i = 0; i < N; i++)
            a[i] = (int)(Math.random()*(9999-1)+1);
    }

    public void exch(int i, int j){
        int swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    public void sort(){
        for(int i = 1; i < N; i++){
            for(int j = i; j > 0; j--)
                if(a[j-1] > a[j])
                    exch(j,j-1);
                else
                    break;
        }
    }

    public void showArray(){
        for(int i : a)
            System.out.println(i);
    }

    public Insertion(){
        this.init();
        this.sort();
        this.showArray();
    }

    public static void main(String[] args){
        new Insertion();
    }
}
