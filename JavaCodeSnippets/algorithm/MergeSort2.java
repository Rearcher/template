/**
 * Created by rahul on 5/28/15.
 */
public class MergeSort2 {
    //Bottom_up MergeSort
    private int N = 10000;
    private int a[] = new int[N];
    private int aux[] = new int[N];

    public void init() {
        for(int i = 0; i < N; i++)
            a[i] = (int)(Math.random()*(9999-1)+1);
    }

    public void showArray() {
        for(int i : a)
            System.out.println(i);
    }

    public void merge(int lo, int mid, int hi) {
        for(int i = lo; i <= hi; i++)
            aux[i] = a[i];

        int i = lo, j = mid+1;
        for(int k = lo; k <= hi; k++) {
            if(i > mid) a[k] = aux[j++];
            else if(j > hi) a[k] = aux[i++];
            else if(aux[i] < aux[j]) a[k] = aux[i++];
            else a[k] = aux[j++];
        }
    }
    //This version has no recursion!
    public void sort() {
        for(int sz = 1; sz < N; sz = sz+sz)
            for(int lo = 0; lo < N-sz; lo += sz+sz)
                merge(lo, lo+sz-1, Math.min(lo+sz+sz-1, N-1));
    }

    public MergeSort2() {
        this.init();
        this.sort();
        this.showArray();
    }

    public static void main(String[] args) {
        new MergeSort2();
    }

}
