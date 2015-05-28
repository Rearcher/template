/**
 * Created by rahul on 5/28/15.
 */
public class QuickSort {
    private int N = 10000;
    private int[] a = new int[N];

    public void init() {
        for(int i = 0; i < N; i++)
            a[i] = (int)(Math.random()*(9999-1)+1);
    }

    public void showArray() {
        for(int i : a)
            System.out.println(i);
    }

    public void exch(int i, int j) {
        int swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    public int partition(int lo, int hi) {
        int i = lo, j = hi+1;
        while(true) {
            while(a[++i] < a[lo])
                if(i == hi) break;
            while(a[--j] > a[lo])
                if(j == lo) break;
            if(i >= j) break;
            exch(i,j);
        }
        exch(lo, j);
        return j;
    }

    public void sort(int lo, int hi) {
        //Random shuffle guarantee the efficiency
        /*Small Array using Insertion sort can be faster
        if(hi <= lo + CUTOFF -1)
        {
            Insertion.sort(a, lo, hi);
            return;
        }
        */
        if(hi <= lo) return;
        /*Estimate true median by taking median of sample
        int m = medianOf3(lo, (lo+hi)/2, hi);
        exch(lo, m);
        */
        int index = partition(lo, hi);
        sort(lo, index-1);
        sort(index+1, hi);
    }

    /*Sort with many duplicate keys, the 3-way quick sort
    public void sort(int lo, int hi) {
        if(hi <= lo) return;
        int lt = lo, gt = hi;
        int v = a[lo];
        int i = lo;
        while(i <= gt) {
            if(a[i] < v) exch(i++, lt++);
            else if(a[i] > v) exch(gt--, i);
            else i++;
        }
        sort(lo, lt-1);
        sort(gt+1, hi);
    }
    */

    public QuickSort() {
        this.init();
        this.sort(0,N-1);
        this.showArray();
    }

    public static void main(String[] args) {
        new QuickSort();
    }
}
