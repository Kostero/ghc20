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

struct Lib {
  int n, signup_time, per_day;
  vector<int> books;
  void read() {
    scanf("%d%d%d", &n, &signup_time, &per_day);
    for(int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      books.push_back(x);
    }
  }
};

int main() {
  int B, L, D;
  scanf("%d%d%d", &B, &L, &D);
  vector<int> score(B);
  for(int i = 0; i < B; ++i) {
    scanf("%d", &score[i]);
  }
  vector<Lib> libs(L);
  for(int il = 0; il < L; ++il) {
    libs[il].read();
  }
  vector<bool> scanned(B), ready(L);
  int day = 0;
  vector<pair<int, vector<int>>> strategy;
  long long total_score = 0;
  while(true) {
    // debug() << imie(day);
    // cerr << day << " ";
    pair<long long, pair<int, vector<int>>> best;
    best.first = 0;
    for(int il = 0; il < L; ++il) {
      if(!ready[il]) {
        vector<int> remaining;
        for(int b : libs[il].books) {
          if(!scanned[b]) {
            remaining.push_back(b);
          }
        }
        sort(remaining.begin(), remaining.end(), [&](int a, int b) {
          return score[a] > score[b];
        });
        long long can = max(0, D - day - libs[il].signup_time) * (long long) libs[il].per_day;
        if(can < (long long) remaining.size()) {
          remaining.resize(can);
        }
        long long gain = 0;
        for(int b : remaining) {
          gain += score[b];
        }
        gain = gain * 1000 * 1000 / pow(libs[il].signup_time, 1.5);
        // assert(gain <= 1000 * 1000 * 1000);
        if(gain > best.first) {
          best = {(int) gain, {il, remaining}};
        }
      }
    }
    if(best.first == 0) {
      break;
    }
    // total_score += best.first;
    int il = best.second.first;
    ready[il] = true;
    strategy.emplace_back(il, best.second.second);
    for(int b : best.second.second) {
      assert(!scanned[b]);
      scanned[b] = true;
      total_score += score[b];
    }
    day += libs[il].signup_time;
  }
  cerr << endl;
  printf("%d\n", (int) strategy.size());
  for(pair<int, vector<int>> pp : strategy) {
    printf("%d %d\n", pp.first, (int) pp.second.size());
    for(int x : pp.second) {
      printf("%d ", x);
    }
    puts("");
  }
  // vector<int> his;
  // long long can = (long long) libs[0].per_day * (D - libs[0].signup_time);
  // for(int book : libs[0].books) {
    // if(can > 0) {
      // can--;
      // his.push_back(book);
    // }
  // }
  // puts("1"); // ile bibliotek
  // printf("%d %d\n", 0, (int) his.size());
  // long long result = 0;
  // for(int x : his) {
    // printf("%d ", x);
    // result += score[x];
  // }
  // puts("");
  cerr << "score = " << total_score / 1000. / 1000. << endl;
}








