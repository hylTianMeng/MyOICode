#include <bits/stdc++.h>

std::vector<int> solve(int, const std::vector<std::vector<int>> &);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> a(1 << n, std::vector<int>(n));
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
    }
  }

  auto p = solve(n, a);
  if ((int)p.size() != (1 << n)) {
    std::cout << "Wrong Answer\n";
    return 0;
  }
  std::vector<bool> vis(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    if (p[i] < 0 || p[i] >= (1 << n) || vis[p[i]]) {
      std::cout << "Wrong Answer\n";
      return 0;
    }
    vis[p[i]] = true;
  }
  for (int i = 0; i < (1 << n); ++i) {
    std::cout << p[i] << " \n"[i + 1 == (1 << n)];
  }
}
