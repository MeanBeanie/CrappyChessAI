#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

struct vec2{
    int x;
    int y;
    vec2(){
        // Error Handling
    }
    vec2(int _x, int _y):x(_x), y(_y) {};
} typedef vec2;

enum PieceType{
    Pawn = 1,
    Knight = 3,
    Bishop = 4,
    Rook = 5,
    Queen = 9,
    King = 999
};

enum PieceColor{
    White,
    Black
};

struct Move{
    int srow;
    int scol;
    int nrow;
    int ncol;
};

class Piece{
    public:
        PieceType type;
        PieceColor color;
        bool hasMoved = false;
        Piece(){
            // Error Handling
        }
        Piece(PieceType _t, PieceColor _c):type(_t), color(_c) {};
        Piece(Piece* p):type(p->type), color(p->color) {};
};

// Returns Piece based on a given char
Piece cTP(char c){
    Piece result;
    if(65 <= (int)c && (int)c <= 90){
        result.color = White;
    }
    else if(97 <= (int)c && 122 >= (int)c){
        result.color = Black;
    }

    if(c == 'P' || c == 'p'){
        result.type = Pawn;
    }
    else if(c == 'R' || c == 'r'){
        result.type = Rook;
    }
    else if(c == 'B' || c == 'b'){
        result.type = Bishop;
    }
    else if(c == 'N' || c == 'n'){
        result.type = Knight;
    }
    else if(c == 'K' || c == 'k'){
        result.type = King;
    }
    else if(c == 'Q' || c == 'q'){
        result.type = Queen;
    }
    return result;
}

// returns true if given value between left and right bounds
bool between(int a, int lb, int rb, bool inclusive = true){
    if(!inclusive){
        return a > lb && a < rb;
    }
    else{
        return a >= lb && a <= rb;
    }
}

// Returns true if given piece is black
bool isBlack(int p){
    return between(p, 97, 122, true);
}

// Returns Given Position to Edge
vec2 pTE(int pos){
    vec2 result;
    result.x = std::abs(0 - pos);
    result.y = 7 - pos;
    return result;
}
class Board{
    public:
        char board[8][8] = {
            {'R', 'B', 'N', 'K', 'Q', 'N', 'B', 'R'},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'-', '-', '-', '-', '-', '-', '-', '-'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'r', 'b', 'n', 'k', 'q', 'n', 'b', 'r'}
        };
        Board(){
            // error handling
        }       
        std::vector<Move> getPossibleMoves(){
            std::cout << "started getPossibleMoves()\n";
            // 65 to 90 = white
            // 97 to 122 = black
            std::vector<Move> result;
            for(int r = 0; r < 8; r++){
                for(int c = 0; c < 8; c++){
                    std::cout << "(" << r << ", " << c << ") is " << board[r][c] << "\n";
                    char ch = board[r][c];
                    Piece piece = cTP(ch);
                    // std::cout << piece.type << std::endl;
                    Move move;
                    move.srow = r;
                    move.scol = c;
                    switch(piece.type){
                        case Pawn:
                            // if(piece.color == White){
                            //     if(r != 7 && (board[r+1][c] == '-' || between((int)board[r+1][c], 97, 122, true))){
                            //         move.nrow = r+1;
                            //         move.ncol = c;
                            //         result.push_back(move);
                            //     }
                            // }
                            if(piece.color == Black){
                                if(r != 0 && (board[r-1][c] == '-' || between((int)board[r-1][c], 65, 90, true))){
                                    move.nrow = r-1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                                if(!piece.hasMoved){
                                    move.nrow = r-2;
                                    move.ncol = c;
                                    piece.hasMoved = false;
                                }
                            }
                            break;
                        case Knight:
                            // if(piece.color == White){
                            //     if(r <= 5 && c != 7 && (board[r+2][c+1] == '-' || between((int)board[r+2][c+1], 97, 122, true))){
                            //         move.nrow = r+2;
                            //         move.ncol = c+1;
                            //         result.push_back(move);
                            //     }
                            //     if(r <= 5 && c != 0 && (board[r+2][c-1] == '-' || between((int)board[r+2][c-1], 97, 122, true))){
                            //         move.nrow = r+2;
                            //         move.ncol = c-1;
                            //         result.push_back(move);
                            //     }
                            //     if(r >= 2 && c != 7 && (board[r-2][c+1] == '-' || between((int)board[r-2][c+1], 97, 122, true))){
                            //         move.nrow = r-2;
                            //         move.ncol = c+1;
                            //         result.push_back(move);
                            //     }
                            //     if(r >= 2 && c != 0 && (board[r-2][c-1] == '-' || between((int)board[r-2][c-1], 97, 122, true))){
                            //         move.nrow = r-2;
                            //         move.ncol = c-1;
                            //         result.push_back(move);
                            //     }
                            //     if(r + 1 < 8 && c + 2 < 8 && (board[r+1][c+2] == '-' || between((int)board[r+1][c+2], 97, 122, true))){
                            //        move.nrow = r+1;
                            //        move.ncol = c+2;
                            //        result.push_back(move);
                            //     }
                            //     if(r - 1 > 0 && c + 2 < 8 && (board[r-1][c+2] == '-' || between((int)board[r-1][c+2], 97, 122, true))){
                            //         move.nrow = r-1;
                            //         move.ncol = c+2;
                            //         result.push_back(move);
                            //     }
                            //     if(r + 1 < 8 && c - 2 < 8 && (board[r+1][c-2] == '-' || between((int)board[r+1][c-2], 97, 122, true))){
                            //         move.nrow = r+1;
                            //         move.ncol = c-2;
                            //         result.push_back(move);
                            //     }
                            //     if(r - 1 > 0 && c - 2 < 8 && (board[r-1][c-2] == '-' || between((int)board[r-1][c-2], 97, 122, true))){
                            //         move.nrow = r-1;
                            //         move.ncol = c-2;
                            //     }
                            // }
                            if(piece.color == Black){
                                printf("1");
                                if(r <= 5 && c != 7 && (board[r+2][c+1] == '-' || between((int)board[r+2][c+1], 65, 90, true))){
                                    move.nrow = r+2;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                                printf("2");
                                if(r <= 5 && c != 0 && (board[r+2][c-1] == '-' || between((int)board[r+2][c-1], 65, 90, true))){
                                    move.nrow = r+2;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                printf("3");
                                if(r >= 2 && c != 7 && (board[r-2][c+1] == '-' || between((int)board[r-2][c+1], 65, 90, true))){
                                    move.nrow = r-2;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                                printf("4");
                                if(r >= 2 && c != 0 && (board[r-2][c-1] == '-' || between((int)board[r-2][c-1], 65, 90, true))){
                                    move.nrow = r-2;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                printf("5");
                                if(r + 1 < 8 && c + 2 < 8 && (board[r+1][c+2] == '-' || between((int)board[r+1][c+2], 65, 90, true))){
                                move.nrow = r+1;
                                move.ncol = c+2;
                                result.push_back(move);
                                }
                                printf("6");
                                if(r - 1 > 0 && c + 2 < 8 && (board[r-1][c+2] == '-' || between((int)board[r-1][c+2], 65, 90, true))){
                                    move.nrow = r-1;
                                    move.ncol = c+2;
                                    result.push_back(move);
                                }
                                printf("7");
                                if(r + 1 < 8 && c - 2 < 8 && (board[r+1][c-2] == '-' || between((int)board[r+1][c-2], 65, 90, true))){
                                    move.nrow = r+1;
                                    move.ncol = c-2;
                                    result.push_back(move);
                                }
                                printf("8");
                                if(r - 1 > 0 && c - 2 < 8 && (board[r-1][c-2] == '-' || between((int)board[r-1][c-2], 65, 90, true))){
                                    move.nrow = r-1;
                                    move.ncol = c-2;
                                }
                                printf("9");
                            }
                            break;
                        case Rook:
                            // if(piece.color == White){
                            //     if(pTE(r).x != 0){
                            //         for(int i = 1; i <= pTE(r).x; i++){
                            //             if(board[r - i][c] == '-' || between((int)board[r+1][c], 97, 122, true)){
                            //                 move.nrow = r - i;
                            //                 move.ncol = c;
                            //             }
                            //         }
                            //     }
                            //     if(pTE(r).y != 0){
                            //         for(int i = 1; i <= pTE(r).y; i++){
                            //             if(board[r + i][c] == '-' || between((int)board[r+1][c], 97, 122, true)){
                            //                 move.nrow = r + i;
                            //                 move.ncol = c;
                            //             }
                            //         }
                            //     }
                            //     if(pTE(c).x != 0){
                            //         for(int i = 1; i<= pTE(c).x; i++){
                            //             if(board[r][c - i] == '-' || between((int)board[r+1][c], 97, 122, true)){
                            //                 move.nrow = r;
                            //                 move.ncol = c - i;
                            //             }
                            //         }
                            //     }
                            //     if(pTE(c).y != 0){
                            //         for(int i = 1; i <= pTE(c).y; i++){
                            //             if(board[r][c + i] == '-' || between((int)board[r+1][c], 97, 122, true)){
                            //                 move.nrow = r;
                            //                 move.ncol = c + i;
                            //             }
                            //         }
                            //     }
                            // }
                            if(piece.color == Black){
                                if(pTE(r).x != 0){
                                    for(int i = 1; i <= pTE(r).x; i++){
                                        if(board[r - i][c] == '-' || !isBlack((int)board[r - i][c])){
                                            move.nrow = r - i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(r).y != 0){
                                    for(int i = 1; i <= pTE(r).y; i++){
                                        if(board[r + i][c] == '-' || !isBlack((int)board[r + i][c])){
                                            move.nrow = r + i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(c).x != 0){
                                    for(int i = 1; i<= pTE(c).x; i++){
                                        if(board[r][c - i] == '-' || !isBlack((int)board[r][c - i])){
                                            move.nrow = r;
                                            move.ncol = c - i;
                                        }
                                    }
                                }
                                if(pTE(c).y != 0){
                                    for(int i = 1; i <= pTE(c).y; i++){
                                        if(board[r][c + i] == '-' || !isBlack((int)board[r][c + i])){
                                            move.nrow = r;
                                            move.ncol = c + i;
                                        }
                                    }
                                }
                            }
                            break;
                        case King:
                            if(piece.color == Black){
                                if(r > 0 && (board[r-1][c] == '-' || !isBlack((int)board[r-1][c]))){
                                    move.nrow = r - 1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                                if(r < 7 && (board[r+1][c] == '-' || !isBlack((int)board[r+1][c]))){
                                    move.nrow = r+1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                                if(c > 0 && (board[r][c-1] == '-' || !isBlack((int)board[r][c-1]))){
                                    move.nrow = r;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                if(c < 7 && (board[r][c+1] == '-' || !isBlack((int)board[r][c+1]))){
                                    move.nrow = r;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                            }
                            break;
                        case Bishop:
                            if(piece.color == Black){
                                int fr = r;
                                int fc = c;
                                while(pTE(fr).x != 0 && pTE(fc).y != 0){
                                    // std::cout << "P " << pTE(fr).x << ", " << pTE(fc).y << '\n';
                                    std::cout << "1\n";
                                    if(board[fr-1][fc+1] == '-' || !isBlack((int)board[fr-1][fc+1])){
                                        std::cout << "2\n";
                                        move.nrow = fr-1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                        std::cout << "3\n";
                                    }
                                    else if(isBlack((int)board[fr-1][fc+1])){
                                        std::cout << "4\n";
                                        break;
                                    }
                                    std::cout << "5\n";
                                    fr--;
                                    fc++;
                                    std::cout << "6\n";
                                }
                                fr = r;
                                fc = c;
                                std::cout << "7\n";
                                while(pTE(fr).y != 0 && pTE(fc).y != 0){
                                    std::cout << "8\n";
                                    if(board[fr+1][fc+1] == '-' || !isBlack((int)board[fr-1][fc+1])){
                                        std::cout << "9\n";
                                        move.nrow = fr+1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(isBlack((int)board[fr+1][fc+1])){
                                        std::cout << "10\n";
                                        break;
                                    }
                                    std::cout << "11\n";
                                    fr++;
                                    fc++;
                                    std::cout << "12\n";
                                }
                                std::cout << "13\n";
                                fr = r;
                                fc = c;
                                std::cout << "14\n";
                                while(pTE(fr).x != 0 || pTE(fc).x != 0){
                                    if(board[fr-1][fc-1] == '-' || !isBlack((int)board[fr-1][fc-1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    else if(isBlack((int)board[fr-1][fc-1])){
                                        break;
                                    }
                                    fr--;
                                    fc--;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 || pTE(fc).x != 0){
                                    if(board[fr+1][fc-1] == '-' || !isBlack((int)board[fr+1][fc-1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    if(isBlack((int)board[fr+1][fc-1])){
                                        break;
                                    }
                                    fr++;
                                    fc--;
                                }
                                std::cout << "finished bishop\n";
                            }
                            break;
                        case Queen:
                            if(piece.color == Black){
                                if(pTE(r).x != 0){
                                    for(int i = 1; i <= pTE(r).x; i++){
                                        if(board[r - i][c] == '-' || !isBlack((int)board[r - i][c])){
                                            move.nrow = r - i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(r).y != 0){
                                    for(int i = 1; i <= pTE(r).y; i++){
                                        if(board[r + i][c] == '-' || !isBlack((int)board[r + i][c])){
                                            move.nrow = r + i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(c).x != 0){
                                    for(int i = 1; i<= pTE(c).x; i++){
                                        if(board[r][c - i] == '-' || !isBlack((int)board[r][c - i])){
                                            move.nrow = r;
                                            move.ncol = c - i;
                                        }
                                    }
                                }
                                if(pTE(c).y != 0){
                                    for(int i = 1; i <= pTE(c).y; i++){
                                        if(board[r][c + i] == '-' || !isBlack((int)board[r][c + i])){
                                            move.nrow = r;
                                            move.ncol = c + i;
                                        }
                                    }
                                }
                                int fr = r;
                                int fc = c;
                                while(pTE(fr).x != 0 && pTE(fc).y != 0){
                                    if(board[fr-1][fc+1] == '-' || !isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(isBlack((int)board[fr-1][fc+1])){
                                        break;
                                    }
                                    fr--;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 && pTE(fc).y != 0){
                                    if(board[fr+1][fc+1] == '-' || !isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(isBlack((int)board[fr+1][fc+1])){
                                        break;
                                    }
                                    fr++;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).x != 0 || pTE(fc).x != 0){
                                    if(board[fr-1][fc-1] == '-' || !isBlack((int)board[fr-1][fc-1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    else if(isBlack((int)board[fr-1][fc-1])){
                                        break;
                                    }
                                    fr--;
                                    fc--;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 || pTE(fc).x != 0){
                                    if(board[fr+1][fc-1] == '-' || !isBlack((int)board[fr+1][fc-1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    if(isBlack((int)board[fr+1][fc-1])){
                                        break;
                                    }
                                    fr++;
                                    fc--;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            std::cout << "result.size = " << result.size() << "\n";
            return result;
        }

        std::vector<Move> getPossibleResponses(char board[8][8]){
            std::cout << "started responses\n";
            std::vector<Move> result;
            for(int r = 0; r < 8; r++){
                for(int c = 0; c < 8; c++){
                    Piece piece = cTP(board[r][c]);
                    Move move;
                    move.srow = r;
                    move.scol = c;
                    switch(piece.type){
                        case Pawn:
                            if(piece.color == White){
                                if(r != 7 && (board[r+1][c] == '-' || between((int)board[r+1][c], 97, 122, true))){
                                    move.nrow = r+1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                            }
                            break;
                        case Knight:
                            if(piece.color == White){
                                if(r <= 5 && c != 7 && (board[r+2][c+1] == '-' || between((int)board[r+2][c+1], 97, 122, true))){
                                    move.nrow = r+2;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                                if(r <= 5 && c != 0 && (board[r+2][c-1] == '-' || between((int)board[r+2][c-1], 97, 122, true))){
                                    move.nrow = r+2;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                if(r >= 2 && c != 7 && (board[r-2][c+1] == '-' || between((int)board[r-2][c+1], 97, 122, true))){
                                    move.nrow = r-2;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                                if(r >= 2 && c != 0 && (board[r-2][c-1] == '-' || between((int)board[r-2][c-1], 97, 122, true))){
                                    move.nrow = r-2;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                if(r + 1 < 8 && c + 2 < 8 && (board[r+1][c+2] == '-' || between((int)board[r+1][c+2], 97, 122, true))){
                                move.nrow = r+1;
                                move.ncol = c+2;
                                result.push_back(move);
                                }
                                if(r - 1 > 0 && c + 2 < 8 && (board[r-1][c+2] == '-' || between((int)board[r-1][c+2], 97, 122, true))){
                                    move.nrow = r-1;
                                    move.ncol = c+2;
                                    result.push_back(move);
                                }
                                if(r + 1 < 8 && c - 2 < 8 && (board[r+1][c-2] == '-' || between((int)board[r+1][c-2], 97, 122, true))){
                                    move.nrow = r+1;
                                    move.ncol = c-2;
                                    result.push_back(move);
                                }
                                if(r - 1 > 0 && c - 2 < 8 && (board[r-1][c-2] == '-' || between((int)board[r-1][c-2], 97, 122, true))){
                                    move.nrow = r-1;
                                    move.ncol = c-2;
                                }
                            }
                            break;
                        case Rook:
                            if(piece.color == White){
                                if(pTE(r).x != 0){
                                    for(int i = 1; i <= pTE(r).x; i++){
                                        if(board[r - i][c] == '-' || between((int)board[r+1][c], 97, 122, true)){
                                            move.nrow = r - i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(r).y != 0){
                                    for(int i = 1; i <= pTE(r).y; i++){
                                        if(board[r + i][c] == '-' || between((int)board[r+1][c], 97, 122, true)){
                                            move.nrow = r + i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(c).x != 0){
                                    for(int i = 1; i<= pTE(c).x; i++){
                                        if(board[r][c - i] == '-' || between((int)board[r+1][c], 97, 122, true)){
                                            move.nrow = r;
                                            move.ncol = c - i;
                                        }
                                    }
                                }
                                if(pTE(c).y != 0){
                                    for(int i = 1; i <= pTE(c).y; i++){
                                        if(board[r][c + i] == '-' || between((int)board[r+1][c], 97, 122, true)){
                                            move.nrow = r;
                                            move.ncol = c + i;
                                        }
                                    }
                                }
                            }
                            break;
                        case King:
                            if(piece.color == White){
                                if(r > 0 && (board[r-1][c] == '-' || isBlack((int)board[r-1][c]))){
                                    move.nrow = r - 1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                                if(r < 7 && (board[r+1][c] == '-' || isBlack((int)board[r+1][c]))){
                                    move.nrow = r+1;
                                    move.ncol = c;
                                    result.push_back(move);
                                }
                                if(c > 0 && (board[r][c-1] == '-' || isBlack((int)board[r][c-1]))){
                                    move.nrow = r;
                                    move.ncol = c-1;
                                    result.push_back(move);
                                }
                                if(c < 7 && (board[r][c+1] == '-' || isBlack((int)board[r][c+1]))){
                                    move.nrow = r;
                                    move.ncol = c+1;
                                    result.push_back(move);
                                }
                            }
                            break;
                        case Bishop:
                            if(piece.color == White){
                                int fr = r;
                                int fc = c;
                                while(pTE(fr).x != 0 && pTE(fc).y != 0){
                                    if(board[fr-1][fc+1] == '-' || isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr-1][fc+1])){
                                        break;
                                    }
                                    fr--;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 && pTE(fc).y != 0){
                                    if(board[fr+1][fc+1] == '-' || isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr+1][fc+1])){
                                        break;
                                    }
                                    fr++;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).x != 0 || pTE(fc).x != 0){
                                    if(board[fr-1][fc-1] == '-' || isBlack((int)board[fr-1][fc-1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr-1][fc-1])){
                                        break;
                                    }
                                    fr--;
                                    fc--;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 || pTE(fc).x != 0){
                                    if(board[fr+1][fc-1] == '-' || !isBlack((int)board[fr+1][fc-1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    if(isBlack((int)board[fr+1][fc-1])){
                                        break;
                                    }
                                    fr++;
                                    fc--;
                                }
                            }
                            break;
                        case Queen:
                            if(piece.color == White){
                                if(pTE(r).x != 0){
                                    for(int i = 1; i <= pTE(r).x; i++){
                                        if(board[r - i][c] == '-' || isBlack((int)board[r - i][c])){
                                            move.nrow = r - i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(r).y != 0){
                                    for(int i = 1; i <= pTE(r).y; i++){
                                        if(board[r + i][c] == '-' || isBlack((int)board[r + i][c])){
                                            move.nrow = r + i;
                                            move.ncol = c;
                                        }
                                    }
                                }
                                if(pTE(c).x != 0){
                                    for(int i = 1; i<= pTE(c).x; i++){
                                        if(board[r][c - i] == '-' || isBlack((int)board[r][c - i])){
                                            move.nrow = r;
                                            move.ncol = c - i;
                                        }
                                    }
                                }
                                if(pTE(c).y != 0){
                                    for(int i = 1; i <= pTE(c).y; i++){
                                        if(board[r][c + i] == '-' || isBlack((int)board[r][c + i])){
                                            move.nrow = r;
                                            move.ncol = c + i;
                                        }
                                    }
                                }
                                int fr = r;
                                int fc = c;
                                while(pTE(fr).x != 0 && pTE(fc).y != 0){
                                    if(board[fr-1][fc+1] == '-' || isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr-1][fc+1])){
                                        break;
                                    }
                                    fr--;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 && pTE(fc).y != 0){
                                    if(board[fr+1][fc+1] == '-' || isBlack((int)board[fr-1][fc+1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc+1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr+1][fc+1])){
                                        break;
                                    }
                                    fr++;
                                    fc++;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).x != 0 || pTE(fc).x != 0){
                                    if(board[fr-1][fc-1] == '-' || isBlack((int)board[fr-1][fc-1])){
                                        move.nrow = fr-1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    else if(!isBlack((int)board[fr-1][fc-1])){
                                        break;
                                    }
                                    fr--;
                                    fc--;
                                }
                                fr = r;
                                fc = c;
                                while(pTE(fr).y != 0 || pTE(fc).x != 0){
                                    if(board[fr+1][fc-1] == '-' || isBlack((int)board[fr+1][fc-1])){
                                        move.nrow = fr+1;
                                        move.ncol = fc-1;
                                        result.push_back(move);
                                    }
                                    if(isBlack((int)board[fr+1][fc-1])){
                                        break;
                                    }
                                    fr++;
                                    fc--;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            std::cout << "ended responses\n";
            return result;
        }

        std::vector<Move> getLegalMoves(){
            std::cout << "Started Legal Moves\n";
            std::vector<Move> result;
            std::vector<Move> possibleMoves = getPossibleMoves();
            printf("-1\n");
            // std::cout << "possibleMoves.size = " << possibleMoves.size() << "\n";
            printf("0\n");
            for(int m = 0; m < possibleMoves.size(); m++){
                printf("1\n");
                Move moove = possibleMoves.at(m);
                printf("2\n");
                char tempBoard[8][8];
                printf("3\n");
                for(int i = 0; i < 8; ++i){
                    printf("4\n");
                    for(int j = 0; j < 8; ++j){
                        printf("5\n");
                        std::cout << "i: " << i << " j:" << j << std::endl;
                        tempBoard[i][j] = board[i][j];
                    }
                }
                printf("6\n");
                std::cout << "srow: " << moove.srow << " scol: " << moove.scol << "\n";
                char c = tempBoard[moove.srow][moove.scol];
                tempBoard[moove.srow][moove.scol] = '-';
                tempBoard[moove.nrow][moove.ncol] = c;
                std::vector<Move> possibleResponses = getPossibleResponses(tempBoard);
                std::cout << "found responses\n";
                for(int r = 0; r < possibleResponses.size(); r++){
                    Move res = possibleResponses.at(r);
                    if(tempBoard[res.nrow][res.ncol] == 'k'){
                        // Illegal Move that Moves us into check
                        std::cout << "found illegal move\n";
                    }
                    else{
                        std::cout << "found legal move\n";
                        result.push_back(moove);
                        std::cout << "added legal move\n";
                    }
                }
            }
            printf("ended legal moves\n");
            return result;
        }

        void MakeMove(std::vector<Move> moves){
            std::cout << "moves.size = " << moves.size() << "\n";
            vec2 result(0, 0);
            int index = 0;
            for(Move move : moves){
                switch(board[move.nrow][move.ncol]){
                    case 'P':
                        if(Pawn > result.y){
                            result.y = Pawn;
                            result.x = index;
                        }
                        break;
                    case 'R':
                        if(Rook > result.y){
                            result.y = Rook;
                            result.x = index;
                        }
                        break;
                    case 'B':
                        if(Bishop > result.y){
                            result.y = Bishop;
                            result.x = index;
                        }
                        break;
                    case 'N':
                        if(Knight > result.y){
                            result.y = Knight;
                            result.x = index;
                        }
                        break;
                    case 'Q':
                        if(Queen > result.y){
                            result.y = Queen;
                            result.x = index;
                        }
                        break;
                    case 'K':
                        result.y = 999;
                        result.x = index;
                        break;
                }
                index++;
            }
            Move chosenMove = moves.at(result.x);
            char c = board[chosenMove.srow][chosenMove.scol];
            std::cout << "Chosen Move: srow: " << chosenMove.srow << ", scol: " << chosenMove.scol << ", nrow: " << chosenMove.nrow << ", ncol: " << chosenMove.ncol << "\n";
            board[chosenMove.srow][chosenMove.scol] = '-';
            board[chosenMove.nrow][chosenMove.ncol] = c;
        }

        void draw(){
            std::string s;
            for(int i = 0; i < 8; i++){
                for(char c : board[i]){
                    s.push_back(c);
                }
                std::cout << s << std::endl;
                s.clear();
            }
        }
};
int main(){

    Board b;
    b.draw();
    b.MakeMove(b.getLegalMoves());
    b.draw();

    return 0;
}
