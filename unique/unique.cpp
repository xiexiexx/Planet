#include <iostream>
#include <vector>
#include <algorithm>

void unique_old(std::vector<int>& S)
{
  sort(S.begin(), S.end());
  for (size_t L = 0, R; L < S.size(); L = R)
  {
    for (R = L + 1; R < S.size(); ++R)
      if (S[R] != S[L])
        break;
    std::cout << S[L] << ": " << R - L << std::endl;
  }
}

void unique(std::vector<int>& S)
{
  sort(S.begin(), S.end());
  size_t L, R;
  for (L = 0, R = 0; R < S.size(); ++R)
    if (S[R] != S[L])
    {
      std::cout << S[L] << ": " << R - L << std::endl;
      L = R;
    }
  if (S.size() > 0)
    std::cout << S[L] << ": " << R - L << std::endl;
}

int main()
{
  std::cout << "Example A: " << std::endl;
  std::vector<int> A = {7, 2, 3, 2, 5, 1, 1};
  unique(A);
  std::cout << "Example B: " << std::endl;
  std::vector<int> B = {-9};
  unique(B);
  std::cout << "Example C: " << std::endl;
  std::vector<int> C;
  unique(C);
  return 0;
}
