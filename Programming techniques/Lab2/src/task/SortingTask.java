package task;

import utils.SortStrategy;

public class SortingTask extends Task{
    private AbstractSorter sorter;
    private int[] vector;

    public SortingTask(String taskID, String descriere, SortStrategy sortStrategy, int[] _vector) {
        super(taskID, descriere);
        if(sortStrategy == SortStrategy.QUICK){
            sorter = new QuickSorter();
        }
        else{
            sorter = new BubbleSorter();
        }
        vector = _vector;
    }

    @Override
    public void execute() {
        sorter.sort(vector);
        for (int i = 0; i < vector.length; i++) {
            System.out.print(vector[i] + " ");
        }
        System.out.println();
    }
}

abstract class AbstractSorter{
    abstract void sort(int[] vector);
}

class QuickSorter extends AbstractSorter{
    @Override
    void sort(int[] vector) {
        quickSort(vector, 0, vector.length-1);
    }

    private void quickSort(int[] vector, int start, int end){
        int partition = partition(vector, start, end);

        if(partition-1>start) {
            quickSort(vector, start, partition - 1);
        }
        if(partition+1<end) {
            quickSort(vector, partition + 1, end);
        }
    }

    private int partition(int[] vector, int start, int end){
        int pivot = vector[end];

        for(int i = start; i < end; i++){
            if(vector[i] < pivot){
                int temp = vector[start];
                vector[start] = vector[i];
                vector[i] = temp;
                start++;
            }
        }

        int temp = vector[start];
        vector[start] = pivot;
        vector[end] = temp;

        return start;
    }
}

class BubbleSorter extends AbstractSorter{
    @Override
    void sort(int[] vector) {
        int n = vector.length;
        for(int i=0; i<n; i++){
            for(int j=1; j<(n-i); j++){
                if(vector[j-1] > vector[j]){
                    int aux = vector[j-1];
                    vector[j-1] = vector[j];
                    vector[j] = aux;
                }
            }
        }
    }
}




