package com.renhuanhuan.convex;

import java.util.Comparator;

/**
 * Created by rahul on 5/31/15.
 */
public class Point2D {
    public final Comparator<Point2D> POLAR_ORDER = new PolarOrder();
    public final double x;
    public final double y;

    public Point2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    //judge a counterclockwise turn
    public static int ccw(Point2D a, Point2D b, Point2D c) {
        double area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
        if(area2 < 0) return -1;
        else if(area2 > 0) return +1;
        else return 0;
    }

    private class PolarOrder implements Comparator<Point2D> {
        public int compare(Point2D q1, Point2D q2) {
            double dy1 = q1.y - y;
            double dy2 = q2.y - y;

            if(dy1 == 0 && dy2 == 0) return 0;   //p, q1, q2 horizontal
            else if(dy1 >= 0 && dy2 < 0) return -1; //q1 above p, q2 below p
            else if(dy2 >= 0 && dy1 < 0) return +1; //q1 below p, q2 above p
            else return -ccw(Point2D.this, q1, q2);
        }
    }

    public static void main(String[] args) {

    }
}

class YOrder implements  Comparator<Point2D> {
    public int compare(Point2D q1, Point2D q2) {
        if(q1.y - q2.y < 0) return -1;
        else return 1;
    }
}
