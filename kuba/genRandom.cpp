#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

mt19937 rng(7458915);
int B, L, D;

struct Lib {
  int n, signup_time, per_day;
  vector<int> books;
  void read() {
    scanf("%d%d%d", &n, &signup_time, &per_day);
    set<int> books_set;
    for(int i = 0; i < n; ++i) {
      int x;
      x = -1;

      while (x == -1 || books_set.find(x) != books_set.end()) {
        x = uniform_int_distribution<int>(0, B - 1)(rng);
      }
      // scanf("%d", &x);
      int y;
      scanf("%d", &y);
      books.push_back(x);
      books_set.insert(x);
    }
  }
};

int main() {
  scanf("%d%d%d", &B, &L, &D);
  vector<int> score(B);
  for(int i = 0; i < B; ++i) {
    scanf("%d", &score[i]);
  }
  vector<Lib> libs(L);
  for(int il = 0; il < L; ++il) {
    libs[il].read();
  }
  
  vector<vector<int>> libsWithBook(B);

  for (int i = 0; i < L; ++i) {
    for (int b : libs[i].books) {
      libsWithBook[b].push_back(i);
    }
  }

  vector<int> cnt(B);
  for (int i = 0; i < B; ++i) cnt[i] = libsWithBook[i].size();

  sort (cnt.begin(), cnt.end());
  for (int i = 0; i < B; ++i) cout << cnt[i] << ' ';
  cout << endl;

  /*
  vector<int> his;
  long long can = (long long) libs[0].per_day * (D - libs[0].signup_time);
  for(int book : libs[0].books) {
    if(can > 0) {
      can--;
      his.push_back(book);
    }
  }

  puts("1"); // ile bibliotek
  printf("%d %d\n", 0, (int) his.size());
  long long result = 0;
  for(int x : his) {
    printf("%d ", x);
    result += score[x];
  }
  puts("");
  cerr << "score = " << result << endl;
*/

}








