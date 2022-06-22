package sise.puzzle.solver;

import java.util.Arrays;

public class Node {

    Board board;
    Node parent;

    public Node(Node parent, Board board) {
        this.board = board;
        this.parent = parent;
    }

    public String getPath() {
        StringBuilder path = new StringBuilder("");
        for (Node node = this; node.parent != null; node = node.parent) {
            path.append(node.board.lastMove);
        }
        return path.reverse().toString();
    }

    public int getDepth() {
        int depth = 0;
        for (Node node = this; node.parent != null; node = node.parent) {
            depth++;
        }
        return depth;
    }

    public Node goUp() {
        if (board.emptyID - board.width >= 0) {
            swapZero(board.emptyID - board.width);
            Board movedBoard = new Board(board.data, 'U', board.emptyID, board.width, board.height);
            Node move = new Node(this, movedBoard);
            swapZero(board.emptyID + board.width);
            return move;
        }
        return null;
    }

    public Node goDown() {
        if (board.emptyID + board.width < board.width * board.height) {
            swapZero(board.emptyID + board.width);
            Board movedBoard = new Board(board.data, 'D', board.emptyID, board.width, board.height);
            Node move = new Node(this, movedBoard);
            swapZero(board.emptyID - board.width);
            return move;
        }
        return null;
    }

    public Node goRight() {
        if ((board.emptyID + 1) % board.width != 0) {
            swapZero(board.emptyID + 1);
            Board movedBoard = new Board(board.data, 'R', board.emptyID, board.width, board.height);
            Node move = new Node(this, movedBoard);
            swapZero(board.emptyID - 1);
            return move;
        }
        return null;
    }

    public Node goLeft() {
        if (board.emptyID % board.width != 0) {
            swapZero(board.emptyID - 1);
            Board movedBoard = new Board(board.data, 'L', board.emptyID, board.width, board.height);
            Node move = new Node(this, movedBoard);
            swapZero(board.emptyID + 1);
            return move;
        }
        return null;
    }

    public Node[] getNeighbours() {
        return new Node[]{goDown(), goUp(), goLeft(), goRight()};
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node node = (Node) o;
        return Arrays.equals(node.board.data, board.data);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(board.data);
    }

    private void swapZero(int index) {
        board.data[board.emptyID] = board.data[index];
        board.data[index] = 0;
        board.emptyID = index;
    }
}