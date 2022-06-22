package sise.puzzle.solver;

public class Result {

    String path;
    boolean solved;
    int finishedNum;
    int visitedNum;
    int maxDepth;
    long timeNanos;

    public Result() {
        this.path = "";
    }
}
