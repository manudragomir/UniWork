package utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class FileDates {
    private String filename1;

    public FileDates(String filename1) {
        this.filename1 = filename1;
    }

    public Date getFirstDayOfSemester() {
        Path path = Paths.get(filename1);
        String day = null;
        try {
            BufferedReader bufferedReader = Files.newBufferedReader(path);
            day = bufferedReader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }

        if(day != null){
            try {
                return new SimpleDateFormat("dd.MM.yyyy").parse(day);
            } catch (ParseException e) {
                e.printStackTrace();
            }
        }
        return null;
    }

    public Map<Date, Integer> getHolidaysOfSemester(){
        Map<Date, Integer> map = new HashMap<Date, Integer>();
        Path path = Paths.get(filename1);
        try {
            BufferedReader bufferedReader = Files.newBufferedReader(path);
            String day = bufferedReader.readLine();
            int numberOfHolidays = Integer.parseInt(bufferedReader.readLine());
            for (int i = 0; i < numberOfHolidays; i++) {
                String line = bufferedReader.readLine();
                String[] args = line.split(",");
                map.put(new SimpleDateFormat("dd.MM.yyyy").parse(args[0]), Integer.parseInt(args[1]));
            }
        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }

        if(map.size() != 0){
            return map;
        }
        return null;

    }
}
