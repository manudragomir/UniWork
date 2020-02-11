package factory;

import container.Container;
import container.QueueContainer;
import container.StackContainer;
import container.StrategyContainer;


public class TaskContainerFactory implements Factory{
    private TaskContainerFactory(){};

    private static Factory instance = null;

    public static Factory getInstance(){
        if(instance == null){
            instance = new TaskContainerFactory();
        }
        return instance;
    }

    @Override
    public Container createContainer(StrategyContainer strategyContainer) {
        switch(strategyContainer){
            case LIFO:
                return new StackContainer();
            case FIFO:
                return new QueueContainer();
            default:
                return null;
        }
    }
}
