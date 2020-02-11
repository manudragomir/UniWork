package complex;

public class ComplexExpressions {
    Operation operation;
    NumarComplex[] args;

    public ComplexExpressions(Operation operation, NumarComplex[] args) {
        this.operation = operation;
        this.args = args;
    }

    public NumarComplex evaluate(){
        BinaryOperator binaryOperator = null;
        switch(operation){
            case SUBTRACTION:
                binaryOperator = new Subtraction();
                break;
            case MULTIPLICATION:
                binaryOperator = new Multiplication();
                break;
            case DIVISION:
                binaryOperator = new Division();
                break;
            default:
                binaryOperator = new Addition();
                break;
        }
        NumarComplex result = args[0];
        for(int index=1; index < args.length; index++){
            result = binaryOperator.compute(result, args[index]);
        }
        return result;
    }
}

interface BinaryOperator{
    NumarComplex compute(NumarComplex c1, NumarComplex c2);
}

class Addition implements BinaryOperator{
    public NumarComplex compute(NumarComplex c1, NumarComplex c2) {
        return c1.adunare(c2);
    }
}

class Subtraction implements BinaryOperator{
    public NumarComplex compute(NumarComplex c1, NumarComplex c2) {
        return c1.scadare(c2);
    }
}

class Division implements BinaryOperator{
    public NumarComplex compute(NumarComplex c1, NumarComplex c2) {
        return c1.impartire(c2);
    }
}

class Multiplication implements BinaryOperator{
    public NumarComplex compute(NumarComplex c1, NumarComplex c2){
        return c1.inmultire(c2);
    }
}
