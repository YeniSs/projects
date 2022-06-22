package sise.puzzle.solver;

import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;


public class AsSolver extends Solver {

    private boolean useHamm;
    private Set<Node> frontier;

    private void heuristic(Node node) {
        if (node != null && explored.add(node)) {
            node.board.heurScore = node.getDepth();
            node.board.heurScore += useHamm ? hamm(node) : manh(node);
            frontier.add(node);
            result.visitedNum++;
        }
    }

    private int hamm(Node node) {
        int dist = 0;
        for (int i = 0; i < node.board.data.length; i++) {
            if (node.board.data[i] != target[i])
                dist++;
        }
        return dist;
    }

    private int manh(Node node) {
        int dataX, dataY, goalX, goalY, dist = 0;
        for (int i = 0; i < node.board.data.length; i++) {
            if (node.board.data[i] != target[i]) {
                int goalPos = Tools.whichID(target, node.board.data[i]);
                dataX = i % node.board.width;
                dataY = i / node.board.width;
                goalX = goalPos % node.board.width;
                goalY = goalPos / node.board.width;
                dist += Math.abs(dataX - goalX) + Math.abs(dataY - goalY);
            }
        }
        return dist;
    }

    @Override
    protected void init(Board board, String order) {
        super.init(board, order);
        this.useHamm = order.equals("hamm");
        this.frontier = new HashSet<>();
    }

    @Override
    public Result solve(Board board, String order) {
        long timeStart = System.nanoTime();
        init(board, order);
        heuristic(currNode);
        while (!frontier.isEmpty() && !result.solved) {
            currNode = Collections.min(frontier, Comparator.comparingInt(a -> a.board.heurScore));
            frontier.remove(currNode);
            explorePaths(currNode);
        }
        result.timeNanos = System.nanoTime() - timeStart;
        return result;
    }

    private void explorePaths(Node node) {
        result.maxDepth = Math.max(result.maxDepth, node.getDepth());
        if (isSolved(node)) {
            result.solved = true;
            result.path = node.getPath();
            return;
        }
        Node[] neighbours = node.getNeighbours();
        for (Node neighbour : neighbours) {
            heuristic(neighbour);
        }
        result.finishedNum++;
    }
}
