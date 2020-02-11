import container.StrategyContainer;
import runner.*;
import task.MessageTask;
import task.SortingTask;
import task.Task;
import utils.SortStrategy;

import java.time.LocalDateTime;

public class Test {
    public static MessageTask[] creatingMessageTasks(){
        MessageTask[] arr = new MessageTask[5];
        arr[0] = new MessageTask("1","Feedback lab1","Ai obtinut 9.60", "Gigi", "Manu", LocalDateTime.now());
        arr[1] = new MessageTask("2","Feedback lab2","Ai obtinut 10", "Mona", "Leana", LocalDateTime.of(
                2019,5,25,10,25));
        arr[2] = new MessageTask("3","Feedback lab3","Ai obtinut 9.90", "Gica", "Mihai", LocalDateTime.now());
        arr[3] = new MessageTask("4","Feedback lab4","Ai obtinut 9.80", "Mane", "Gogu", LocalDateTime.now());
        arr[4] = new MessageTask("5","Feedback lab5","Ai obtinut 9.99", "Veta", "Mara", LocalDateTime.now());
        return arr;
    }

    //TASK 4
    public static void printingTasks(){
        MessageTask[] arr = creatingMessageTasks();
        for(int i=0; i<arr.length; i++){
            System.out.println(arr[i]);
        }
    }

    //TASK 3
    public static void sorting(){
        int arr[] = {-5,2,-3,0,5,3};
        SortingTask t = new SortingTask("1", "sorteaza", SortStrategy.QUICK, arr);
        t.execute();
    }

    //TASK 10
    public static void test10(String[] args){
        TaskRunner runner = new StrategyTaskRunner(getStrategyFromCL(args));
        MessageTask[] arr = creatingMessageTasks();
        for(int i=0; i<arr.length; i++){
            runner.addTask(arr[i]);
        }

        runner.executeAll();
    }

    //TASK 14
    public static void test14(String[] args){
        test10(args);
        MessageTask[] arr = creatingMessageTasks();
        TaskRunner runner = new StrategyTaskRunner(getStrategyFromCL(args));

        AbstractTaskRunner runner1 = new PrinterTaskRunner(runner);
        for(int i=0; i<arr.length; i++){
            runner1.addTask(arr[i]);
        }
        runner1.executeAll();

        AbstractTaskRunner runner2 = new DelayTaskRunner(runner);
        for(int i=0; i<arr.length; i++){
            runner2.addTask(arr[i]);
        }
        runner2.executeAll();
    }

    private static StrategyContainer getStrategyFromCL(String[] args) {
        if(args.length == 0){
            System.out.println("No params: DEFAULT LIFO");
            return StrategyContainer.LIFO;
        }
        StrategyContainer strategyContainer;
        if(args[0].equals("FIFO")){
            strategyContainer = StrategyContainer.FIFO;
        }
        else{
            strategyContainer = StrategyContainer.LIFO;
        }

        return strategyContainer;
    }

    public static void main(String[] args){
        test14(args);
    }
}
