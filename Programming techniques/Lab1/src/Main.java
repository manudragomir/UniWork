import complex.ComplexExpressions;
import complex.NumarComplex;
import complex.Operation;

public class Main {
    public static void main(String[] args){
            if(args.length % 2 == 1 && ExpressionParser.checkExpression(args) == true){
                System.out.println("Expresia e corecta!");
                NumarComplex[] numere = new NumarComplex[args.length/2+1];
                int k = 0;
                for(int i=0; i<args.length; i+=2){
                    numere[k++] = new NumarComplex(args[i]);
                }

                Operation op;
                switch(args[1]){
                    case "-":
                        op = Operation.SUBTRACTION;
                        break;
                    case "*":
                        op = Operation.MULTIPLICATION;
                        break;
                    case "/":
                        op = Operation.DIVISION;
                        break;
                    default:
                        op = Operation.ADDITION;
                }

                ComplexExpressions ce = new ComplexExpressions(op, numere);
                System.out.println(ce.evaluate());
            }
            else{
                System.out.println("Expresie incorecta!");
            }
    }
}
