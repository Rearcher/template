import sun.misc.Queue;

/**
 * Created by rahul on 6/1/15.
 */
//Symbol table implemented in binary search trees
public class BST<Key extends Comparable<Key>, Value> {

    private class Node {
        private Key key;
        private Value value;
        private Node left, right;
        private int count;

        public Node(Key key, Value value) {
            this.key = key;
            this.value = value;
        }
    }

    private Node root;

    //size operation
    public int size() {
        return size(root);
    }

    private int size(Node x) {
        return x.count;
    }//end of size operation


    //put operation
    public void put(Key key, Value val) {
        root = put(root, key, val);
    }

    private Node put(Node x, Key key, Value val) {
        if(x==null) return new Node(key, val);

        int cmp = key.compareTo(x.key);
        if(cmp < 0) x.left = put(x.left, key, val);
        else if(cmp > 0) x.right = put(x.right, key, val);
        else x.value = val;

        x.count = 1 + size(x.left) + size(x.right);//update size
        return x;
    }//end of put operation

    //get operation
    public Value get(Key key) {
        Node x = root;
        while(x!=null) {
            int cmp = key.compareTo(x.key);
            if(cmp < 0) x = x.left;
            else if(cmp > 0) x = x.right;
            else return x.value;
        }
        return null;
    }//end of get operation

    //floor operation, to find the max key <= KEY
    public Key floor(Key key) {
        Node x = floor(root, key);
        if(x == null) return null;
        return x.key;
    }

    private Node floor(Node x, Key key) {
        if(x==null) return null;

        int cmp = key.compareTo(x.key);
        if(cmp == 0) return x;  //just find the key = KEY
        if(cmp < 0) return floor(x.left, key); //go to the left sub tree

        Node t = floor(x.right, key); //go to the right sub tree
        if(t!=null) return t;
        else return x;
    }//end of floor operation

    //rank operation, to find the KEY rank in tree
    public int rank(Key key) {
        return rank(key, root);
    }

    private int rank(Key key, Node x) {
        if(x == null) return 0;
        //three conditions
        int cmp = key.compareTo(x.key);
        if(cmp < 0) return rank(key, x.left);
        else if(cmp == 0) return size(x);
        else return 1+size(x.left)+rank(key,x.right);
    }//end of rank operation


    //delete operation
    public void deleteMin() {
        root = deleteMin(root);
    }

    private Node deleteMin(Node x) {
        if(x.left == null) return x.right;
        x.left = deleteMin(x.left);
        x.count = 1 + size(x.left) + size(x.right);
        return x;
    }

    private Node min(Node x) {
        while(x.left != null)
            x = x.left;
        return x;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node x, Key key) {
        if(x == null) return null;
        int cmp = key.compareTo(x.key);
        if(cmp < 0) x.left = delete(x.left, key);
        else if(cmp > 0) x.right = delete(x.right, key);
        else {
            if(x.right == null) return x.left;
            if(x.left == null) return x.right;

            Node t = x;
            x = min(t.right);
            x.right = deleteMin(t.right);
            x.left = t.left;
        }
        x.count = size(x.left) + size(x.right) + 1;
        return x;
    }//end of delete operation

    //iterator
    public Iterable<Key> keys() {
        Queue<Key> q = new Queue<Key>();
        inorder(root, q);
        return (Iterable<Key>) q; //some problem
    }

    private void inorder(Node x, Queue<Key> q) {
        if(x == null) return;
        inorder(x.left, q);
        q.enqueue(x.key);
        inorder(x.right, q);
    }//end of iterator
}
