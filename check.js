// eiweowioe 100000000
const num1 = 40000000;

class Board {
    board = [
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0]
    ]

    setTile(i, j, value) {
        this.board[i][j] = value;
    }

    get() {
        const a = 2;

        return a;
    }
};

console.time("looping");

Array(num1).fill(new Board())

console.timeEnd("looping");