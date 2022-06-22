package sise.puzzle.solver;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class DFSSolver extends Solver {

    public final int MAX_DEPTH = 20;
    private Map<Node, Node> explored;

    @Override
    protected void init(Board board, String order) {
        super.init(board, order);
        this.explored = new HashMap<>();
    }

    @Override
    public Result solve(Board board, String order) {
        long timeStart = System.nanoTime();
        init(board, order);
        hashMinCostNode(currNode);
        while (!frontier.isEmpty() && !result.solved) {
            currNode = frontier.pop();
            explorePaths(currNode);
        }
        result.timeNanos = System.nanoTime() - timeStart;
        return result;
    }

    private void hashMinCostNode(Node node) {
        if (node == null) return;
        if (isSolved(node)) {
            result.visitedNum++;
            result.solved = true;
            result.path = node.getPath();
            return;
        }
        Node prevNode = explored.get(node);
        if (prevNode == null || prevNode.getDepth() > node.getDepth()) {
            result.visitedNum++;
            explored.put(node, node);
            frontier.push(node);
        }
    }

    private void explorePaths(Node node) {
        if (result.finishedNum < 10)
            Arrays.toString(node.board.data);
        int depth = node.getDepth();
        result.maxDepth = Math.max(result.maxDepth, depth);
        if (isSolved(node)) {
            result.solved = true;
            result.path = node.getPath();
            return;
        }
        if (depth < MAX_DEPTH) {
            for (int i = order.length - 1; i >= 0 && !result.solved; i--) {
                char c = order[i];
                if (c == 'L') {
                    hashMinCostNode(node.goLeft());
                } else if (c == 'R') {
                    hashMinCostNode(node.goRight());
                } else if (c == 'U') {
                    hashMinCostNode(node.goUp());
                } else if (c == 'D') {
                    hashMinCostNode(node.goDown());
                }
            }
            result.maxDepth = Math.max(result.maxDepth, depth + 1);
            result.finishedNum++;
        }
    }
}
