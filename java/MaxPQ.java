/**
 * Created by rahul on 5/30/15.
 */
public class MaxPQ<Key extends Comparable<Key>> {
    private Key[] pq;
    private int N;

	//indexing from 1, so you need add 1 to capacity when initial the array
    public MaxPQ(int capacity) {
        pq = (Key[]) new Comparable[capacity+1];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public void insert(Key key) {
        pq[++N] = key;
        swim(N);
    }

    public Key delmax() {
        Key max = pq[1];
        exch(1, N--);
        sink(1);
        pq[N+1] = null;
        return max;
    }

    public void show() {
        for(Key i : pq)
            System.out.print(i);
    }

    //When an element is added, it should swim up if the heap order is wrong.
    private void swim(int k) {
        while(k > 1 && less(k/2, k)) {
            exch(k, k/2);
            k = k/2;
        }
    }

    //When the max element, the root of the heap, is removed, it exchange it with the last element,
    //then the last element be the root place, it should sink down if the order is wrong.
    private void sink(int k) {
        while(2*k <= N) {
            int j = 2*k;
            if(j < N && less(j,j+1)) j++;
            if(!less(k, j)) break;
            exch(k,j);
            k = j;
        }
    }
	//indexing from 1
    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) < 0;
    }
	//indexing from 1
    private void exch(int i, int j) {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }

    public static void main(String[] args) {
        MaxPQ<Integer> a = new MaxPQ(5);
        for(int i = 1; i <= 5; i++)
            a.insert(i);
        a.show();
    }
}
