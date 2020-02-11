package container;

import task.Task;

public class StackContainer extends AbstractContainer {

    @Override
    public Task remove() {
        if (!isEmpty())
        {
            size--;
            return tasks[size];
        }
        return null;
    }

    @Override
    public void add(Task task) {
        if (tasks.length==size)
        {
            Task t[]=new Task[tasks.length*2];
            System.arraycopy( tasks, 0, t, 0, tasks.length );
            tasks=t;
        }
        tasks[size]=task;
        size++;
    }
}
