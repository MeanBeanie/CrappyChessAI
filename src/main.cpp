#include <iostream>
#include <string>
#include <vector>

class Move{
    public:
        int spos[2];
        int epos[2];
        char piece = '+';
        Move(){};
};

class Board{
    public:
        char gameBoard[8][8] = {
            {'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'}
        };
        Board(){};
        bool isAvailable(char c){
            return (c == '-' || isWhite(c));
        }
        // draws board
        void draw(){
            std::string s;
            for(int i = 0; i < 8; i++){
                for(char c : gameBoard[i]){
                    s.push_back(c);
                }
                std::cout << s << std::endl;
                s.clear();
            }
        }
        // Makes Move on Board
        void MakeMove(Move move){
            if(move.piece == '+'){
                // auto defines a moves piece
                // in case it hasn't been set
                move.piece = gameBoard[move.spos[0]][move.spos[1]];
            }
            // Swaps the spos and epos chars in the board
            gameBoard[move.spos[0]][move.spos[1]] = '-';
            gameBoard[move.epos[0]][move.epos[1]] = move.piece;
        }
        void PickRandomMove(){
            std::vector<Move> moves = GenerateLegalMoves();
            std::cout << "Enter num between 0 and " << moves.size()-1 << ": ";
            int index = 0;
            std::cin >> index;
            MakeMove(moves.at(index));
        }
    private:
        bool isWhite(char c){
            // 65 to 90 = white
            // 97 to 122 = black
            return c >= 65 && c <= 90;
        }
        std::vector<Move> GenerateMoves(char board[8][8]){
            std::vector<Move> result;
            // 2 loops, 1 for row, 1 for column
            for(int r = 0; r < 8; r++){
                for(int c = 0; c < 8; c++){
                    Move move;
                    move.spos[0] = r;
                    move.spos[1] = c;
                    move.piece = board[r][c];
                    // switch statement to calculate possible moves for each piece
                    switch(board[r][c]){
                        case 'p':{
                            if(r+1 < 8 && board[r+1][c] == '-'){
                                move.epos[0] = r+1;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            if(r+1 < 8 && c+1 < 8 && isWhite(board[r+1][c+1])){
                                move.epos[0] = r+1;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            if(r+1 < 8 && c-1 > 0 && isWhite(board[r+1][c-1])){
                                move.epos[0] = r+1;
                                move.epos[1] = c-1;
                                result.push_back(move);
                            }
                            break;
                        }
                        case 'r':{
                            int i = 0;
                            while(r+i < 8 && (board[r+i][c] == '-' || isWhite(board[r+i][c]))){
                                move.epos[0] = r+1;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i > 0 && (board[r-i][c] == '-' || isWhite(board[r-i][c]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            i = 0;
                            while(c+i < 8 && (board[r][c+i] == '-' || isWhite(board[r][c+i]))){
                                move.epos[0] = r;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(c-i > 0 && (board[r][c-i] == '-' || isWhite(board[r][c-i]))){
                                move.epos[0] = r;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }
                            break;
                        }
                        case 'n':{
                            if(r+2 < 8 && c+1 < 8 && isAvailable(board[r+2][c+1])){
                                move.epos[0] = r+2;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            if(r+2 < 8 && c-1 > 0 && isAvailable(board[r+2][c-1])){
                                move.epos[0] = r+2;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            if(r-2 < 8 && c+1 < 8 && isAvailable(board[r-2][c+1])){
                                move.epos[0] = r-2;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            if(r-2 < 8 && c-1 > 0 && isAvailable(board[r-2][c-1])){
                                move.epos[0] = r-2;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            
                            if(c+2 < 8 && r+1 < 8 && isAvailable(board[r+1][c+2])){
                                move.epos[0] = r+1;
                                move.epos[1] = c+2;
                                result.push_back(move);
                            }
                            if(c+2 < 8 && r-1 < 8 && isAvailable(board[r-1][c+2])){
                                move.epos[0] = r-1;
                                move.epos[1] = c+2;
                                result.push_back(move);
                            }
                            if(c-2 < 8 && r+1 < 8 && isAvailable(board[r+1][c-2])){
                                move.epos[0] = r+1;
                                move.epos[1] = c-2;
                                result.push_back(move);
                            }
                            if(c-2 < 8 && r-1 < 8 && isAvailable(board[r-1][c-2])){
                                move.epos[0] = r-1;
                                move.epos[1] = c-2;
                                result.push_back(move);
                            }
                            break;
                        }
                        case 'b':{
                            int i = 0;
                            while(r+i < 8 && c+i < 8 && (board[r+i][c+i] == '-' || isWhite(board[r+i][c+i]))){
                                move.epos[0] = r+i;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r+i < 8 && c-i > 0 && (board[r+i][c-i] == '-' || isWhite(board[r+i][c-i]))){
                                move.epos[0] = r+i;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i < 8 && c+i < 8 && (board[r-i][c+i] == '-' || isWhite(board[r-i][c+i]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i < 8 && c-i > 0 && (board[r-i][c-i] == '-' || isWhite(board[r-i][c-i]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }
                            break;
                        }
                        case 'k':{
                            if(r+1 < 8 && (board[r+1][c] == '-' && isWhite(board[r+1][c]))){
                                move.epos[0] = r+1;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            if(r-1 > 0 && (board[r-1][c] == '-' && isWhite(board[r-1][c]))){
                                move.epos[0] = r-1;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            if(c+1 < 8 && (board[r][c+1] == '-' && isWhite(board[r][c+1]))){
                                move.epos[0] = r;
                                move.epos[1] = c+1;
                                result.push_back(move);
                            }
                            if(c-1 < 8 && (board[r][c-1] == '-' && isWhite(board[r][c-1]))){
                                move.epos[0] = r;
                                move.epos[1] = c-1;
                                result.push_back(move);
                            }
                            break;
                        }
                        case 'q':{
                            int i = 0;
                            while(r+i < 8 && (board[r+i][c] == '-' || isWhite(board[r+i][c]))){
                                move.epos[0] = r+1;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i > 0 && (board[r-i][c] == '-' || isWhite(board[r-i][c]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c;
                                result.push_back(move);
                            }
                            i = 0;
                            while(c+i < 8 && (board[r][c+i] == '-' || isWhite(board[r][c+i]))){
                                move.epos[0] = r;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(c-i > 0 && (board[r][c-i] == '-' || isWhite(board[r][c-i]))){
                                move.epos[0] = r;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }                         
                            i = 0;
                            while(r+i < 8 && c+i < 8 && (board[r+i][c+i] == '-' || isWhite(board[r+i][c+i]))){
                                move.epos[0] = r+i;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r+i < 8 && c-i > 0 && (board[r+i][c-i] == '-' || isWhite(board[r+i][c-i]))){
                                move.epos[0] = r+i;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i < 8 && c+i < 8 && (board[r-i][c+i] == '-' || isWhite(board[r-i][c+i]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c+i;
                                result.push_back(move);
                            }
                            i = 0;
                            while(r-i < 8 && c-i > 0 && (board[r-i][c-i] == '-' || isWhite(board[r-i][c-i]))){
                                move.epos[0] = r-i;
                                move.epos[1] = c-i;
                                result.push_back(move);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            return result;
        }
        std::vector<Move> GenerateLegalMoves(){
            std::vector<Move> result;
            std::vector<Move> possibleMoves = GenerateMoves(gameBoard);
            std::vector<Move> ndResult;
            for(Move move : possibleMoves){
                if(move.piece == '+'){
                    move.piece = gameBoard[move.spos[0]][move.spos[1]];
                }
                char simBoard[8][8];
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        simBoard[i][j] = gameBoard[i][j];
                    }
                }
                simBoard[move.spos[0]][move.spos[1]] = '-';
                simBoard[move.epos[0]][move.epos[1]] = move.piece;
                for(Move res : GenerateMoves(simBoard)){
                    if(simBoard[res.epos[0]][res.epos[1]] == 'k'){
                        // Illegal Move
                    }
                    else{
                        result.push_back(move);
                    }
                }
            }
            return result;
        }
};

int main(){
    Board b;
    b.draw();
    b.PickRandomMove();
    std::cout << "========\n";
    b.draw();
    return 0;
}