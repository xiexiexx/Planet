#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [L, M), [M, R) ==> D
template <typename T>
void merge(typename vector<T>::const_iterator L,
           typename vector<T>::const_iterator M,
           typename vector<T>::const_iterator R,
           vector<T>& D)
{
  D.resize(R - L);
  auto iA = L;
  auto iB = M;
  size_t i = 0;
  while (iA != M && iB != R)
    if (*iA < *iB)
      D[i++] = *iA++;
    else
      D[i++] = *iB++;
  while (iA != M)
    D[i++] = *iA++;
  while (iB != R)
    D[i++] = *iB++;
}

int main()
{
  vector<int> A = {3, 2, 1, 4, 5};
  sort(A.begin(), A.begin() + A.size() / 2);
  sort(A.begin() + A.size() / 2, A.end());
  vector<int> B;
  merge(A.begin(), A.begin() + A.size() / 2, A.end(), B);
  for (const auto& x : B)
    cout << x << endl;
  return 0;
}
