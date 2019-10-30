#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

/* Yonsei Electrical Engineering
 * Made by Hyunu Kim
 * everyone can use this code freely
 * I won first prize for 코딩왕 경진대회(for Yonsei EE undergrad students) on 2019.10.31 :)
 * sorry for showing off lol this code is just a shit
 */

using namespace std;

/* print4x4 
 *
 * gets an array of 16 int elements
 * and draw it in 4x4 shape
 */
void print4x4(int data[]) {
    char line[] = "+------+------+------+------+";
    for (int row = 0; row < 4; row++) {
        cout << '\n' << line << '\n';
    for (int col = 0; col < 4; col++) {
        int val = data[row * 4 + col];
        if (val == 0) {
            cout << "|      ";
        }
        else {
            cout << '|' << setw(6) << val;
        }
    }
    cout << '|';
    }
    cout << '\n' << line << '\n';
}


// generate number 2 with 90 percent, 4 with 10 percent
int make_new(){
    if (rand()%100 < 10)
        return 4;
    else
        return 2;
}

// initialize game: start with 2 filled array among 16 blocks
void init_game(int data[]){
    int index1, index2;
    index1 = rand()%16;
    index2 = rand()%16;
    if (index1 == index2) 
        index2 = (index1 + 8) %16;
    for (unsigned i = 0; i<16; i++){
        if (i == index1 or i == index2)
            data[i] = make_new();
        else
            data[i] = 0;
    }
}

// move function
void move_left(int data[]){
    bool moved = false; // flag for invalid movement
    int new_idx = rand()%4;
    for (unsigned line = 0; line <4; line++){
        //double number which can be overlapped 
        for (unsigned i = 4*line ; i < 4*line+4; i ++){
            for (unsigned j = i+1; j< 4*line + 4; j++){
                if (data[j] == 0) continue;
                else if (data[j] == data[i]){
                    data[j] = 0;
                    data[i] *= 2;
                    i = j;
                    moved = true;
                    break;
                }
                else break;

            }
        }
        //move number to left side if there exists rooms
        for (unsigned k = 4*line; k < 4*line + 4; k++){
            if (!data[k]) continue;
            for (unsigned m = 4*line; m < k; m++){
                if (data[m] == 0){
                    data[m] = data[k];
                    data[k] = 0;
                    moved = true; 
                }
            }
        }
        //add new number for each movement
        if (line == new_idx)
            if (!data[4*line+3])
                data[4*line + 3] = make_new();
    }
    //print message when there is no block to be moved
    if (!moved){
        cout<<"#############################\n#####invalid movement!#######\n############################"<<endl;
    }
}

void move_right(int data[]){
    int right_data[16];
    for (unsigned i = 0; i < 16; i++){
        right_data[i] = data[(i/4)*4 + 3 - i%4];
    }
    move_left(right_data);
    for (unsigned i = 0; i < 16; i++){
        data[i] = right_data[(i/4)*4 + 3 - i%4];
    }

}

void move_up(int data[]){
    int up_data[16];
    for (unsigned i = 0; i < 16; i++){
        up_data[i] = data[(i/4) +  (i%4)*4];
    }
    move_left(up_data);
    for (unsigned i = 0; i < 16; i++){
        data[i] = up_data[(i/4) + (i%4)*4];
    }

}

void move_down(int data[]){
    int down_data[16];
    for (unsigned i = 0; i < 16; i++){
        down_data[i] = data[(3 - i/4)*4 + i%4];
    }
    move_up(down_data);
    for (unsigned i = 0; i < 16; i++){
        data[i] = down_data[(3-i/4)*4 + i%4];
    }

}

// return true when the player managed to make 2048
bool check_2048(int data[]){
    for (unsigned i = 0; i<16; i++){
        if (data[i] >= 2048)
            return true;
    }
    return false; 
}


int main() {
    int data[16];
    srand(static_cast<unsigned int>(std::time(0))); // get seed (time)
    char input;
    int key;
    init_game(data);
    print4x4(data);
    // you can implement this function with Keyboard not using charactor in Windows.
    // headerfile conio.h and function getch(), kbhit() helps to do this
    // cannot implement easily with ubuntu though :(
    while(1){
        cout<<"up: u, down: d, left: l, right : r"<<endl;
        cin>> input;
        if (input == 'r')
            move_right(data);
        else if (input == 'l')
            move_left(data);
        else if (input == 'u')
            move_up(data);
        else if (input == 'd')
            move_down(data);
        else if (input == 'i')
            init_game(data);
        print4x4(data);

        //print congrats message when players managed to make 2048
        if (check_2048(data)){
            cout<<"congrats! you made 2048!"<<endl;
            break;
        }
        
    }
    return 0;
}
