package runner;

import utils.Constants;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner{
    public PrinterTaskRunner(TaskRunner runner) {
        super(runner);
    }

    public void executeOneTask(){
        super.executeOneTask();
        System.out.println("Task executat la: " + LocalDateTime.now().format(Constants.DATE_TIME_FORMATTER));
    }

}
