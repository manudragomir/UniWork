package utils;

import domain.NotaUtila;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileFeedbackSaver {
    public void storeToFile(String filename, NotaUtila notaUtila) {
        Path path = Paths.get(filename);
        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.CREATE, StandardOpenOption.APPEND)) {
            bufferedWriter.write(notaUtila.toString());
            bufferedWriter.write("\n");
        } catch (IOException e) { e.printStackTrace(); }
    }
}
