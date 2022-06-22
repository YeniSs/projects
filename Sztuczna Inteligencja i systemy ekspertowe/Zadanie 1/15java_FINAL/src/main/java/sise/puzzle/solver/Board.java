package sise.puzzle.solver;

public class Board {

    byte[] data;
    char lastMove;
    int emptyID;
    byte height;
    byte width;
    int heurScore;

    public Board(byte[] data, char lastMove, int emptyID, int width, int height) {
        this.data = data.clone();
        this.lastMove = lastMove;
        this.emptyID = emptyID;
        this.height = (byte) height;
        this.width = (byte) width;
        this.heurScore = 0;
    }
}
