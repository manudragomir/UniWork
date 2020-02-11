import complex.NumarComplex;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParser {
    public static boolean checkExpression(String[] args){
        if(checkSign(args) == false){
            return false;
        }
        else{
            for(int i=0; i<args.length; i+=2){
                if(checkComplex(args[i]) == false){
                    return false;
                }
                else{
                    NumarComplex c = new NumarComplex(args[i]);
                }
            }
        }
        return true;
    }
    private static boolean checkComplex(String e){
        String enou = e;
        int x = -1;
        for(int i=0; i<e.length(); i++){
            if(e.charAt(i) == 'i'){
                x = i;
            }
        }

        if(x!=-1 && (x!=0 && e.charAt(x-1) != '*')) {
            enou = e.substring(0, x) + '*' + e.substring(x, e.length());
        }

        if(x==0){
            enou = "*" + enou;
        }

        String regexRealImaginary = "^([+,\\-]?[0-9]+)([+,\\-][0-9]*)\\*i$";
        String regexReal = "^([+,\\-]?[0-9]+)$";
        String regexImaginary = "^([+,\\-]?[0-9]*)\\*i$";
        Pattern p1 = Pattern.compile(regexRealImaginary);
        Pattern p2 = Pattern.compile(regexReal);
        Pattern p3 = Pattern.compile(regexImaginary);

        Matcher m1 = p1.matcher(enou);
        Matcher m2 = p2.matcher(enou);
        Matcher m3 = p3.matcher(enou);
        return (m1.matches() || m2.matches() || m3.matches());
    }
    private static boolean checkSign(String[] args){
        int len = args.length;
        if(len>1){
            String op = args[1];
            for(int i=3; i<len; i+=2){
                if(!args[i].equals(op)){
                    return false;
                }
            }
        }
        return true;
    }
}
