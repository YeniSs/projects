package sise.puzzle.solver;

import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Tools {

    public static Board readBoardFromFile(String path) {
        int width = 0, height = 0, zeroPos = 0;
        byte[] data = null;

        try {
            List<int[]> lines = Files.lines(Paths.get(path))
                    .map(line -> Arrays.stream(line.split(" ")).mapToInt(Byte::parseByte).toArray())
                    .collect(Collectors.toList());
            width = lines.get(0)[0];
            height = lines.get(0)[1];
            data = new byte[width * height];
            int index = 0;
            for (int i = 1; i < lines.size(); i++) {
                for (int j = 0; j < lines.get(i).length; j++) {
                    data[index++] = (byte) lines.get(i)[j];
                    if (lines.get(i)[j] == 0) {
                        zeroPos = (i - 1) * width + j;
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return new Board(data, Character.MIN_VALUE, zeroPos, width, height);
    }

    public static void writeResult(Result result, String path) {
        try (FileWriter ostream = new FileWriter(path)) {
            if (result.path.length() > 0) {
                ostream.write(result.path.length() + "\n");
                ostream.write(result.path);
            } else {
                ostream.write("failed");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void writeStats(Result result, String path) {
        try (FileWriter ostream = new FileWriter(path)) {
            if (result.path.length() > 0) {
                ostream.write(result.path.length() + "\n");
            } else {
                ostream.write("failed\n");
            }
            ostream.write(result.visitedNum + "\n");
            ostream.write(result.finishedNum + "\n");
            ostream.write(result.maxDepth + "\n");
            double timeMillis = result.timeNanos / 1E6;
            DecimalFormat threeDigits = new DecimalFormat("#0.000");
            ostream.write(threeDigits.format(timeMillis) + "\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static byte[] genTarget(int len) {
        byte[] target = new byte[len];
        for (int i = 0; i < target.length - 1; i++) {
            target[i] = (byte) (i + 1);
        }
        target[target.length - 1] = 0;
        return target;
    }

    public static int whichID(byte[] arr, int arg) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == arg) {
                return i;
            }
        }
        return -1;
    }
}
