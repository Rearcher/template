import java.util.Comparator;

/**
 * Created by rahul on 5/27/15.
 */
class point{
    int x, y;
    public point(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public boolean less(point a) {
        if(x < a.x) return true;
        else return false;
    }
    public String toString() {
        return Integer.toString(x)+" "+Integer.toString(y);
    }
}


public class Insertion {

    private int N = 10000;
    private point[] a = new point[N];

    public void init(){
        for(int i = 0; i < N; i++) {
            a[i] = new point((int)(Math.random()*(100-1)+1),(int)(Math.random()*(100-1)+1));
        }
    }

    public void exch(int i, int j){
        point swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    public void sort(){
        for(int i = 1; i < N; i++){
            for(int j = i; j > 0; j--)
                if(a[j].less(a[j-1]))
                    exch(j,j-1);
                else
                    break;
        }
    }

    public void showArray(){
        for(point i : a)
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
