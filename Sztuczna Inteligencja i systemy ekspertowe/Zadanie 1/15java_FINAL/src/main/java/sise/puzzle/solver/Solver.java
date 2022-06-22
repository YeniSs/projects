package sise.puzzle.solver;

import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

public abstract class Solver {

    protected byte[] target;

    protected char[] order;

    protected Node currNode;

    protected Set<Node> explored;

    protected LinkedList<Node> frontier;

    protected Result result;

    public abstract Result solve(Board board, String order);

    protected void init(Board board, String order) {
        this.target = Tools.genTarget(board.width * board.height);
        this.order = order.toUpperCase().toCharArray();
        this.currNode = new Node(null, board);
        this.explored = new HashSet<>();
        this.frontier = new LinkedList<>();
        this.result = new Result();
    }

    protected boolean isSolved(Node node) {
        return Arrays.equals(node.board.data, target);
    }
}
