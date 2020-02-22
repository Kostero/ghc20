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

int main(int argc, char* argv[]) {
  srand(atoi(argv[1]));
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
  vector<int> his_score(L);
  vector<vector<int>> where_is(B);
  for(int il = 0; il < L; ++il) {
    for(int b : libs[il].books) {
      where_is[b].push_back(il);
      his_score[il] += score[b];
    }
  }
  vector<int> spec(L);
  int times = 1 + rand() % 5;
  for(int i = 0; i < times; ++i) {
    spec[rand() % L] = 1 + rand() % 3;
  }
  while(true) {
    // debug() << imie(day);
    // cerr << day << " ";
    pair<long long, pair<int, vector<int>>> best;
    best.first = 0;
    for(int il = 0; il < L; ++il) {
      if(!ready[il]) {
        // vector<int> remaining;
        // for(int b : libs[il].books) {
          // if(!scanned[b]) {
            // remaining.push_back(b);
          // }
        // }
        // sort(remaining.begin(), remaining.end(), [&](int a, int b) {
          // return score[a] > score[b];
        // });
        // long long can = max(0, D - day - libs[il].signup_time) * (long long) libs[il].per_day;
        // if(can < (long long) remaining.size()) {
          // remaining.resize(can);
        // }
        
        long long gain = 0;
        // for(int b : remaining) {
          // gain += score[b];
        // }
        if(day + libs[il].signup_time >= D) {
          continue;
        }
        gain = his_score[il];
        gain = gain * 1000 * 1000 / pow(libs[il].signup_time, 1.);
        if(spec[il] == 1) {
          continue;
        }
        if(spec[il] == 2) {
          gain *= 10;
        }
        if(spec[il] == 3) {
          gain *= 2;
        }
        if(day > D * 0.98) {
          gain *= (1000 + rand() % 150);
        }
        else if(day > D * 0.95) {
          gain *= (1000 + rand() % 100);
        }
        // assert(gain <= 1000 * 1000 * 1000);
        if(gain > best.first) {
          best = {(int) gain, {il, {}}};
        }
      }
    }
    if(best.first == 0) {
      break;
    }
    // total_score += best.first;
    int il = best.second.first;
    ready[il] = true;
    vector<int> used;
    for(int b : libs[il].books) if(!scanned[b]) {
      assert(!scanned[b]);
      scanned[b] = true;
      total_score += score[b];
      used.push_back(b);
      for(int x : where_is[b]) {
        his_score[x] -= score[b];
      }
    }
    strategy.emplace_back(il, used);
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
  cerr << "score = " << total_score << " " << atoi(argv[1]) << endl;
  assert(total_score <= 5690369);
}








