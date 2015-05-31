package com.renhuanhuan.convex;

import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

/**
 * Created by rahul on 5/31/15.
 */
//Graham scan
public class ConvexHull {

    private static int N;
    private static Scanner scanner;

    public static void main(String[] args) {
        scanner = new Scanner(System.in);
        N = scanner.nextInt();

        Stack<Point2D> hull = new Stack<Point2D>();
        Point2D[] p = new Point2D[N];

        for(int i = 0; i < N; i++) {
            double x = scanner.nextDouble();
            double y = scanner.nextDouble();
            p[i] = new Point2D(x,y);
        }

        Arrays.sort(p, new YOrder());  //Points ordered by y axis, choose the point with smallest y
        Arrays.sort(p, p[0].POLAR_ORDER);  //Points ordered by polar angle with the p[0]

        hull.push(p[0]);
        hull.push(p[1]);
        for(int i = 2; i < N; i++) {
            Point2D top = hull.pop();
            while(Point2D.ccw(hull.peek(), top, p[i]) <= 0) //When it comes across clockwise turn, pop last time point
                top = hull.pop();
            hull.push(top);
            hull.push(p[i]);
        }

        while(!hull.empty()) {
            Point2D temp = hull.pop();
            System.out.println(temp.x + " " + temp.y);
        }
    }
}
