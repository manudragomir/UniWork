package container;

import task.Task;

public abstract class AbstractContainer implements Container{
    protected Task[] tasks;
    protected int size;
    protected int capacity = 20;

    public AbstractContainer(){
        tasks = new Task[capacity];
        size=0;
    }

    @Override
    public abstract Task remove();

    @Override
    public abstract void add(Task task);

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return (size==0);
    }
}
