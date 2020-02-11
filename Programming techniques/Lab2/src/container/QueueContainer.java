package container;

import task.Task;

public class QueueContainer extends AbstractContainer {
    private int front;
    private int rear;

    public QueueContainer() {
        super();
        this.front = 0;
        this.rear = -1;
    }

    @Override
    public void add(Task task) {
        if(size == capacity){
            Task[] t = new Task[tasks.length*2];
            System.arraycopy(tasks,0,t,0,size);
            tasks = t;
        }
        rear = (rear + 1) % capacity;
        tasks[rear] = task;
        size++;
    }

    @Override
    public Task remove() {
        if (!isEmpty())
        {
            Task elem = tasks[front];
            front = (front + 1) % capacity;
            size--;
            return elem;
        }
        return null;
    }
}
