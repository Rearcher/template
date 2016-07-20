import java.util.ArrayList;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by rahul on 7/20/16.
 */
public class SimpleThreadPool {
    public static BlockingQueue<Integer> testQueue = new LinkedBlockingQueue<>();

    private int limits;
    private ArrayList<WorkerThread> workers;
    private BlockingQueue<Runnable> taskQueue;

    SimpleThreadPool(int nums) {
        limits = nums;
        workers = new ArrayList<>();
        taskQueue = new LinkedBlockingQueue<>();
    }

    private int currentWorking() {
        return workers.size();
    }

    public void submit(Runnable task) {
        if (currentWorking() < limits) {
            WorkerThread worker = new WorkerThread();
            worker.start();
            workers.add(worker);
        }
        try {
            taskQueue.put(task);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void destroy() {
        while (!taskQueue.isEmpty());
        for (WorkerThread worker : workers) {
            worker.close();
        }
    }

    class WorkerThread extends Thread {
        private Boolean isRunning = true;

        public void close() {
            isRunning = false;
        }

        public void run() {
            while (isRunning) {
                Runnable task = null;
                try {
                    task = taskQueue.take();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                task.run();
            }
        }
    }

    public static void main(String[] args) {
        SimpleThreadPool pool = new SimpleThreadPool(10);
        for (int i = 0; i < 100; ++i) {
            pool.submit(new test("Task " + i));
        }
        pool.destroy();
    }
}

class test implements Runnable {
    private String id;

    public test(String str) { id = str; }

    public void run() {
        try {
            System.out.println("Start process " + id);
            Thread.sleep(1000);
            System.out.println(id + " Completed!");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}