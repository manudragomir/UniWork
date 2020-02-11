package complex;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NumarComplex {
    private int re, im;
    public NumarComplex(int re, int im){
        this.re = re;
        this.im = im;
    }

    public NumarComplex(String e){
        Pattern p = Pattern.compile("-?\\d+");
        Matcher m = p.matcher(e);
        String real = "0";
        String imag = "0";

        for(int i=0; i<e.length(); i++){
            if(e.charAt(i) == 'i'){
                if(i!=0 && e.charAt(i-1)=='-'){
                    imag = "-1";
                }
                if(i!=0 && e.charAt(i-1) == '+' || i==0){
                    imag = "1";
                }
            }
        }

        if(m.find()){
            real = m.group(0);
            if(m.find()){
                imag = m.group(0);
            }
        }

        //check daca avem parte reala
        for(int i=0; i<e.length(); i++){
            if(e.charAt(i) == 'i'){
                i--;
                int cnt = 0;
                while(i>=0){
                    if(e.charAt(i) == '+' || e.charAt(i) == '-'){
                        cnt++;
                    }
                    i--;
                }

                if(cnt == 0){
                    if(!imag.equals("1")) {
                        imag = real;
                        real = "0";
                    }
                }
                else if(cnt == 1 && (e.charAt(0) == '+' || e.charAt(0) == '-')){
                    if(!imag.equals("-1")) {
                        imag = real;
                        real = "0";
                    }
                }
                break;
            }
        }

        this.im = Integer.valueOf(imag);
        this.re = Integer.valueOf(real);

    }

    public int getRe() {
        return re;
    }

    @Override
    public String toString() {
        return Integer.toString(re) + "+i*" + Integer.toString(im);
    }

    public void setRe(int re) {
        this.re = re;
    }

    public int getIm() {
        return im;
    }

    public void setIm(int im) {
        this.im = im;
    }

    public NumarComplex conjugat(){
        return new NumarComplex(re, -im);
    }

    public NumarComplex adunare(NumarComplex c){
        return new NumarComplex(re + c.getRe(), im + c.getIm());
    }

    public NumarComplex scadare(NumarComplex c){
        return new NumarComplex(re - c.getRe(), im - c.getIm());
    }

    public NumarComplex inmultire(NumarComplex c){
        int a1 = re;
        int a2 = c.getRe();
        int b1 = im;
        int b2 = c.getIm();
        return new NumarComplex(a1*a2-b1*b2, a1*b2+a2*b1);
    }

    public NumarComplex impartire(NumarComplex c){
        int a1 = re;
        int a2 = c.getRe();
        int b1 = im;
        int b2 = c.getIm();
        return new NumarComplex((a1*a2+b1*b2)/(a2*a2+b2*b2), (a2*b1-a1*b2)/(a2*a2+b2*b2));
    }
}
