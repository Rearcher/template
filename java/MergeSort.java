/**
 * Created by rahul on 5/27/15.
 */
public class MergeSort {
    private int N = 10000;
    private int a[] = new int[N];
    private int aux[] = new int[N];

    public void init(){
        for(int i = 0; i < N; i++)
            a[i] = (int)(Math.random()*(9999-1)+1);
    }

    public void showArray(){
        for(int i : a)
            System.out.println(i);
    }

    //public boolean isSorted(int lo, int hi){}

    public void merge(int lo, int mid, int hi){
        //assert isSorted(lo, mid);
        //assert isSorted(mid, hi);

        for(int i = lo; i <= hi; i++)
            aux[i] = a[i];

        int i = lo, j = mid+1;
        for(int k = lo; k <= hi; k++){
            if(i > mid) a[k] = aux[j++];
            else if(j > hi) a[k] = aux[i++];
            else if(aux[i] < aux[j]) a[k] = aux[i++];
            else a[k] = aux[j++];
        }
        //assert isSorted(lo, hi);
    }

    public void sort(int lo, int hi){
        /*When the array is small,use insertion sort can be fast!
        if(hi <= lo + CUTOFF - 1)
        {
            Insertion.sort(hi, lo);
            return;
        }
        */
        if(hi <= lo) return;
        int mid = (hi+lo)/2;
        sort(lo, mid);
        sort(mid+1, hi);
        /*when a[mid]<a[mid+1],the whole array is already in order,no need to merge again.
        if(a[mid] < a[mid+1]) return;
        */
        merge(lo, mid, hi);
    }

    public void sort(){
        sort(0,N-1);
    }

    public MergeSort(){
        this.init();
        this.sort();
        this.showArray();
    }

    public static void main(String[] args){
        new MergeSort();
    }
}
