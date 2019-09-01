#include <iostream>
#include <vector>

using namespace std;

// 为方便讲解, 我们不定义point的相等(==)和不相等(!=)运算符.
struct point {
  int x;
  int y;
};

const int m = 5;
const int n = 7;
const char unvisited = '0'; // 未访问过的标记.
const char visited = 'V';   // 访问过的标记.
// 迷宫字符数组, 周围一圈全是墙(以'*'标记).
char maze[m][n] = {
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '0', '0', '0', '*', '0', '*'},
    {'*', '0', '*', '*', '*', '0', '*'},
    {'*', '0', '0', '0', '0', '0', '*'},
    {'*', '*', '*', '*', '*', '*', '*'}
};
const int d = 4;      // 可行方向总数.
// 以下标取值0, 1, 2, 3标记东南西北与当前位置的偏移量.
const point delta[d] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
// 起点与终点的坐标.
point source = {1, 1};
point destination = {3, 5};

// 递归形式求解迷宫, 实际上不用递归更好, 避免了参数传递, 但要保存每个点的direction当前值.
bool solved = false;
void backtrack(vector<point>& X)
{
  if (X.back().x == destination.x && X.back().y == destination.y)
  {
    solved = true;
    for (const auto& c : X)
      cout << c.x << ' ' << c.y << endl;
  }
  else
    for (int direction = 0; direction < d; ++direction)
    {
      point next = {X.back().x + delta[direction].x,
                    X.back().y + delta[direction].y};
      if (maze[next.x][next.y] == unvisited)
      {
        maze[next.x][next.y] = visited;
        X.push_back(next);
        backtrack(X);
        X.pop_back();
        if (solved)
          return;
      }
    }
}

int main()
{
  vector<point> P;
  P.reserve(m * n);
  P.push_back(source);                      // 初始点设为入口点.
  maze[source.x][source.y] = visited;
  backtrack(P);
  return 0;
}
