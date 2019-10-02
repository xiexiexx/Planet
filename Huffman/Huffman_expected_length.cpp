#include <iostream>
#include <vector>
#include <queue>

using namespace std;

double wrong_expected_length(vector<double> P)
{
  // {0.1, 0.1, 0.2, 0.2, 0.15, 0.15, 0.1}
  if (P.size() < 2)
    return 0;
  sort(P.begin(), P.end(), greater<double>());
  queue<double> F;
  double length = 0;
  size_t n = P.size();
  for (size_t k = 1; k < n; ++k)
  {
    double x, y;
    x = P.empty() ? F.front() : P.back();
    if (F.empty())
      P.pop_back();
    else if (F.front() < x)
    {
      x = F.front();
      F.pop();
    }
    else
      P.pop_back();
    y = P.empty() ? F.front() : P.back();
    if (F.empty())
      P.pop_back();
    else if (F.front() < y)
    {
      y = F.front();
      F.pop();
    }
    else
      P.pop_back();
    length += x + y;
    F.push(x + y);
  }
  return length;
}

double correct_expected_length(vector<double> P)
{
  if (P.size() < 2)
    return 0;
  sort(P.begin(), P.end(), greater<double>());
  queue<double> F;
  double length = 0;
  size_t n = P.size();
  for (size_t k = 1; k < n; ++k)
  {
    double x, y;
    if (F.empty())
    {
      x = P.back();
      P.pop_back();
    }
    else if (P.empty())
    {
      x = F.front();
      F.pop();
    }
    else if (F.front() < P.back())
    {
      x = F.front();
      F.pop();
    }
    else
    {
      x = P.back();
      P.pop_back();
    }
    if (F.empty())
    {
      y = P.back();
      P.pop_back();
    }
    else if (P.empty())
    {
      y = F.front();
      F.pop();
    }
    else if (F.front() < P.back())
    {
      y = F.front();
      F.pop();
    }
    else
    {
      y = P.back();
      P.pop_back();
    }
    length += x + y;
    F.push(x + y);
  }
  return length;
}

double another_expected_length(vector<double> P)
{
  if (P.size() < 2)
    return 0;
  sort(P.begin(), P.end(), greater<double>());
  queue<double> F;
  double length = 0;
  size_t n = P.size();
  for (size_t k = 1; k < n; ++k)
  {
    double x, y;
    if (P.empty())
    {
      x = F.front();
      F.pop();
      y = F.front();
      F.pop();
    }
    else if (F.empty())
    {
      x = P.back();
      P.pop_back();
      y = P.back();
      P.pop_back();
    }
    else if (P.back() < F.front())
    {
      x = P.back();
      P.pop_back();
      if (P.empty())
      {
        y = F.front();
        F.pop();
      }
      else if (P.back() < F.front())
      {
        y = P.back();
        P.pop_back();
      }
      else
      {
        y = F.front();
        F.pop();
      }
    }
    else
    {
      x = F.front();
      F.pop();
      if (F.empty())
      {
        y = P.back();
        P.pop_back();
      }
      else if (P.back() < F.front())
      {
        y = P.back();
        P.pop_back();
      }
      else
      {
        y = F.front();
        F.pop();
      }
    }
    length += x + y;
    F.push(x + y);
  }
  return length;
}

const double POSITIVE_INFINITY = numeric_limits<double>::infinity();

double expected_length(vector<double> P)
{
  size_t n = P.size();
  if (n < 2)
    return 0;
  P.reserve(n + 2);
  P.insert(P.begin(), POSITIVE_INFINITY);
  P.push_back(POSITIVE_INFINITY);
  sort(P.begin() + 1, P.begin() + 1 + n);
  size_t i = 1;
  size_t j = 0;
  size_t m = 1;
  double length = 0;
  for (size_t k = 1; k < n; ++k)
  {
    double d;
    if (P[i] < P[j])
      d = P[i++];
    else
      d = P[j++];
    if (P[i] < P[j])
      d += P[i++];
    else
      d += P[j++];
    length += d;
    P[m] = P[m - 1];
    P[m - 1] = d;
    ++m;
  }
  return length;
}

int main()
{
  vector<double> P = {0.1, 0.1, 0.2, 0.2, 0.15, 0.15, 0.1};
  cout << wrong_expected_length(P) << endl;
  cout << correct_expected_length(P) << endl;
  cout << another_expected_length(P) << endl;
  cout << expected_length(P) << endl;
  return 0;
}
