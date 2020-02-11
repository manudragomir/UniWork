package utils.ObserverPattern;

import java.util.ArrayList;
import java.util.List;

public class Observable {
    private ArrayList<Observer> listObs = new ArrayList<>();

    public void addObserver(Observer observer){
        listObs.add(observer);
    }

    public void removeObserver(Observer observer){
        listObs.remove(observer);
    }

    public void notifyy(){
        for (int i=0; i<listObs.size(); i++) {
            listObs.get(i).update();
        }
    }
}
