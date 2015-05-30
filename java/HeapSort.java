/**
 * Created by rahul on 5/30/15.
 */
public class HeapSort {
    public static void sort(Comparable[] pq) {
        int N = pq.length;
        //Step1, make it in heap order
        for(int k = N/2; k >= 1; k--)
            sink(pq, k, N);
        //Step2, exchange the root, which is the max element, with the last element in the array,
        //and then sink the new root to keep heap order
        while(N > 1) {
            exch(pq, 1, N);
            sink(pq, 1, --N);
        }
    }

    private static void sink(Comparable[] pq, int k, int N) {
        while(2*k <= N) {
            int j = 2*k;
            if(j < N && less(pq, j, j+1))
                j += 1;
            if(!less(pq, k, j)) break;
            exch(pq, k, j);
            k = j;
        }
    }

    //Pay attention to the indexing, it starts from 0
    private static void exch(Comparable[] pq, int i, int j) {
        i--;
        j--;
        Comparable swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
    }

    //indexing starting from 0
    private static boolean less(Comparable[] pq, int i, int j) {
        return pq[i-1].compareTo(pq[j-1]) < 0;
    }

    public static void main(String[] args) {
        Integer[] a = new Integer[5];
        a[0] = 10;
        a[1] = 5;
        a[2] = 8;
        a[3] = 4;
        a[4] = 6;
        //System.out.println(a.length);
        sort(a);
        for(int i = 0; i < 5; i++)
            System.out.println(a[i]);
    }
}
