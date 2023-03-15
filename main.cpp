#include <iostream>
#include <vector>

using namespace std;

int DIF_BEGGINER = 0;
int DIF_INTERMEDIATE = 1;
int DIF_EXPERT = 2;

class Table{
public:
  Table() {
    height = 9;
    width = 9;
    mines_cnt = 10;
    Init();
  };
  Table(int diff) {
    if(diff == DIF_BEGGINER){
      height = 9;
      width = 9;
      mines_cnt = 10;
    }
    if(diff == DIF_INTERMEDIATE){
      height = 16;
      width = 16;
      mines_cnt = 40;
    }
    if(diff == DIF_EXPERT){
      height = 16;
      width = 30;
      mines_cnt = 100;
    }
    Init();
  };
  bool Check(int x, int y, char ch) {
    if(display[y][x] != '~'){
      return true;
    }
    if(table[y][x] < 0){
      if(ch == 'F'){
        display[y][x] = ch;
        mines_cnt--;
        return true;
      }
      display[y][x] = 'M';
      return false;
    }
    if(ch == 'F'){
      display[y][x] = ch;
      return true;
    }
    display[y][x] = table[y][x] + '0';
    if(table[y][x] == 0){
      for (int j = -1; j <= 1; ++j) {
        for (int k = -1; k <= 1; ++k) {
          if (y + j >= 0 && y + j < height && x + k >= 0 && x + k < width) {
            Check(x + k, y + j, ch);
          }
        }
      }
    }
    return true;
  };
  bool CheckMines() {
    return mines_cnt == 0;
  }
  void Print() {
    for(int i = 0;i<table.size();++i){
      for(int j = 0;j<table[i].size();++j){
        cout<<display[i][j]<<' ';
      }
      cout<<endl;
    }
  };
private:
  void Init() {
    int x, y;
    display.assign(height, vector<char>(width, '~'));
    table.assign(height, vector<int>(width, 0));
    for(int i = 0;i<mines_cnt;++i) {
      x = rand() % width;
      y = rand() % height;
      while(table[y][x] < 0){
        x = rand() % width;
        y = rand() % height;
      }
      table[y][x] = -mines_cnt;
      for(int j = -1;j<=1;++j) {
        for(int k = -1;k<=1;++k) {
          if(y + j >= 0 && y + j < height && x + k >= 0 && x + k < width) {
            table[y + j][x + k]++;
          }
        }
      }
    }
  };
  int mines_cnt;
  int height;
  int width;
  vector<vector<int> > table;
  vector<vector<char> > display;
};

void Game() {
  cout<<"Choose difficulty: 0- begginer, 1- intermediate, 2- expert"<<endl;
  int diff;
  cin>>diff;
  Table tb(diff);
  tb.Print();
  int x, y;
  char ch;
  while(true){
    cin>>x>>y>>ch;
    if(!tb.Check(x - 1, y - 1, ch)) {
      cout<<"GAME OVER"<<endl;
      return;
    }
    if(tb.CheckMines()) {
      cout<<"CONGRATS YOU WIN"<<endl;
      return;
    }
    tb.Print();
  }
}

int main() {
  char ch;
  while(ch != 'n') {
    Game();
    cout<<"Do you want to play again? y/n"<<endl;
    cin>>ch;
  }
}