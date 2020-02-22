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
  vector<int> books, sorted;
  void read(const vector<int>& score) {
    scanf("%d%d%d", &n, &signup_time, &per_day);
    for(int i = 0; i < n; ++i) {
      int x;
      scanf("%d", &x);
      books.push_back(x);
      sorted.push_back(score[x]);
    }
    sort(sorted.rbegin(), sorted.rend()); // decreasingly
    for(int i = 1; i < (int) sorted.size(); ++i) {
      sorted[i] += sorted[i-1]; // prefix sums
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
    libs[il].read(score);
  }
  
  auto estimate = [&](vector<int> order) {
    int would = 0;
    int day = 0;
    for(int il : order) {
      day += libs[il].signup_time;
      if(day >= D) {
        break;
      }
      long long _can = (long long) libs[il].per_day * (D - day);
      // assert(_can <= 1000 * 1000 * 1000);
      int can = min(1000LL * 1000 * 1000, _can);
      can = min(can, (int) libs[il].books.size());
      would += libs[il].sorted[can-1];
    }
    return would;
  };
  
  vector<int> order;
  vector<bool> ready(L);
  long long current_score = 0;
  for(int rep = 0; rep < 400000; ++rep) {
    vector<int> new_order = order;
    int type = rand() % 3;
    if(type == 0) {
      // insert
      int i = rand() % L;
      if(ready[i]) {
        continue;
      }
      new_order.insert(new_order.begin() + rand() % (1 + new_order.size()), i);
    }
    else if(type == 1) {
      // replace
      int i = rand() % L;
      if(ready[i] || order.empty()) {
        continue;
      }
      new_order[rand() % order.size()] = i;
    }
    else if(type == 2) {
      if(order.empty()) {
        continue;
      }
      int i = rand() % order.size();
      int j = rand() % order.size();
      swap(new_order[i], new_order[j]);
    }
    else {
      assert(false);
    }
    
    long long new_score = estimate(new_order);
    if(new_score > current_score) {
      current_score = new_score;
      // cerr << current_score << ": " << new_order.size() << endl;
      // ";
      // for(int x : new_order) cerr << x << " ";
      // cerr << endl;
      order = new_order;
      ready = vector<bool>(L, false);
      for(int il : new_order) {
        ready[il] = true;
      }
    }
  }
  ready = vector<bool>(L, false);
  // return 0;
  vector<bool> scanned(B);
  int day = 0;
  vector<pair<int, vector<int>>> strategy;
  long long total_score = 0;
    vector<double> mul(L, 1.);
    int times = rand() % 5;
    for(int i = 0; i < times; ++i) {
      int j = rand() % L;
      if(rand() % 3) {
        mul[j] -= rand() % 1000 / 1000. / 2;
      }
      else {
        mul[j] += rand() % 1000 / 1000. / 2;
      }
    }
  while(true) {
    // debug() << imie(day);
    // cerr << day << " ";
    pair<long long, pair<int, vector<int>>> best;
    best.first = 0;
    for(int il : order) {
    // for(int il = 0; il < L; ++il) {
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
        gain = gain * 1000 * 1000 / pow(libs[il].signup_time, 1) * mul[il];
        // assert(gain <= 1000 * 1000 * 1000);
        if(gain > best.first) {
          best = {(int) gain, {il, remaining}};
        }
        break;
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
  cerr << "score = " << total_score / 1000. / 1000. << " " << atoi(argv[1]) << endl;
  assert(total_score <= 5348248);
}








