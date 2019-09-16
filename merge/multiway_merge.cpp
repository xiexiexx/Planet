#include <vector>
#include <iostream>
#include <queue>

using namespace std;

template <typename T>
void merge(const vector<vector<T>>& V, vector<T>& S)
{
  size_t L = 0;
  for (size_t i = 0; i < V.size(); ++i)
    L += V[i].size();
  S.clear();
  S.reserve(L);
  using range = pair<typename vector<T>::const_iterator,
                     typename vector<T>::const_iterator>;
  auto cmp = [](range a, range b) { return *(a.first) > *(b.first); };
  priority_queue<range, vector<range>, decltype(cmp)> PQ(cmp);
  for (size_t i = 0; i < V.size(); ++i)
    if (V[i].begin() != V[i].end())
      PQ.push({V[i].begin(), V[i].end()});
  while (!PQ.empty())
  {
    auto R = PQ.top();
    PQ.pop();
    S.push_back(*(R.first));
    R.first = R.first + 1;
    if (R.first != R.second)
      PQ.push(R);
  }
}

int main()
{
  vector<vector<int>> A = { {1, 2, 4}, {}, {2, 3, 5}, {3, 4, 6, 8} };
  // A[0], A[1], A[2], A[3] are sorted.
  vector<int> B;

  merge(A, B);
  for (const auto& x : B)
    cout << x << endl;
  return 0;
}
