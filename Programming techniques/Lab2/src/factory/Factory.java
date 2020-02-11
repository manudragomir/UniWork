package factory;

import container.Container;
import container.StrategyContainer;

public interface Factory {
    Container createContainer(StrategyContainer strategyContainer);

}
