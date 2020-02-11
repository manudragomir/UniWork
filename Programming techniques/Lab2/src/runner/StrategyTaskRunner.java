package runner;

import container.Container;
import container.QueueContainer;
import container.StackContainer;
import container.StrategyContainer;
import factory.TaskContainerFactory;
import task.Task;

public class StrategyTaskRunner implements TaskRunner{
    private Container container;

    public StrategyTaskRunner(StrategyContainer strategyContainer) {
        container = TaskContainerFactory.getInstance().createContainer(strategyContainer);
    }

    @Override
    public void executeOneTask() {
        if(!container.isEmpty()){
            container.remove().execute();
        }
    }

    @Override
    public void executeAll() {
        while(!container.isEmpty()){
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return (!container.isEmpty());
    }
}
