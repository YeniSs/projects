package sise.puzzle;

import sise.puzzle.solver.*;

public class Puzzle {

    public static void main(String[] args) {
        parseArgs(args);
    }

    private static void parseArgs(String[] args) {
        String alg = args[0];
        String order = args[1];
        String dataPath = args[2];
        String resultPath = args[3];
        String statsPath = args[4];
        Solver solver = parseSolver(alg);
        Board board = Tools.readBoardFromFile(dataPath);
        //System.out.printf("%s %s %s\n", alg, order, dataPath);
        Result result = solver.solve(board, order);
        Tools.writeResult(result, resultPath);
        Tools.writeStats(result, statsPath);
    }

    private static Solver parseSolver(String arg) {
        switch (arg) {
            case "bfs":
                return new BFSSolver();
            case "dfs":
                return new DFSSolver();
            case "astr":
                return new AsSolver();
            default:
                throw new IllegalArgumentException();
        }
    }
}