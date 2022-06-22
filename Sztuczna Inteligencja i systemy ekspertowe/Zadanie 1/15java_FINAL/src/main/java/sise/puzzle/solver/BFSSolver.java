package sise.puzzle.solver;

public class BFSSolver extends Solver {

    @Override
    public Result solve(Board board, String order) {
        long timeStart = System.nanoTime();
        init(board, order);
        hashNode(currNode);
        while (!frontier.isEmpty() && !result.solved) {
            currNode = frontier.remove();
            explorePaths(currNode);
        }
        result.timeNanos = System.nanoTime() - timeStart;
        return result;
    }

    private void hashNode(Node node) {
        if (node != null && explored.add(node)) {
            result.visitedNum++;
            frontier.add(node);
        }
    }

    private void explorePaths(Node node) {
        result.maxDepth = Math.max(result.maxDepth, node.getDepth());
        if (isSolved(node)) {
            result.solved = true;
            result.path = node.getPath();
            return;
        }
        for (char c : order) {
            if (c == 'L') {
                hashNode(node.goLeft());
            } else if (c == 'R') {
                hashNode(node.goRight());
            } else if (c == 'U') {
                hashNode(node.goUp());
            } else if (c == 'D') {
                hashNode(node.goDown());
            }
        }
        result.finishedNum++;
    }
}
