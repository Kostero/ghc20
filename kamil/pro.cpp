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




struct FastFlow {
  using T = int;
  struct E {
    int dest;
    T orig, *lim, *rev;
  };
  int zr, uj, n = 0;
  vector<unique_ptr<T>> ts;
  vector<vector<E>> graf;
  vector<int> ptr, odl;
  void vert(int v) {
    n = max(n, v + 1);
    graf.resize(n);
    ptr.resize(n);
    odl.resize(n);
  }
  bool iszero(T v) {
    return !v; // Zmienić dla doubli.
  }
  void bfs() {
    fill(odl.begin(), odl.end(), 0);
    vector<int> kol = {zr};
    odl[zr] = 1;
    for (int i = 0; i < (int) kol.size(); i++) {
      for (E& e : graf[kol[i]]) {
        if (!odl[e.dest] and !iszero(*e.lim)) {
          odl[e.dest] = odl[kol[i]] + 1;
          kol.push_back(e.dest);
        }
      }
    }
  }
  T dfs(int v, T lim) {
    if (v == uj) return lim;
    T ret = 0, wez;
    for (int& i = ptr[v]; i < (int) graf[v].size(); i++) {
      E& e = graf[v][i];
      if (odl[e.dest] == odl[v] + 1 and !iszero(*e.lim) and
          !iszero(wez = dfs(e.dest, min(*e.lim, lim)))) {
        ret += wez;
        *e.lim -= wez;
        *e.rev += wez;
        lim -= wez;
        if (iszero(lim)) break;
      }
    }
    return ret;
  }
  void add_edge(int u, int v, T lim, bool bi = false /* bidirectional? */) {
    vert(max(u, v));
    T *a = new T(lim), *b = new T(lim * bi);
    ts.emplace_back(a);
    ts.emplace_back(b);
    graf[u].push_back(E{v, lim,      a, b});
    graf[v].push_back(E{u, lim * bi, b, a});
  }
  T dinic(int zr_, int uj_) {
    zr = zr_; uj = uj_;
    vert(max(zr, uj));
    T ret = 0;
    while (true) {
      bfs();
      fill(ptr.begin(), ptr.end(), 0);
      const T sta = dfs(zr, numeric_limits<T>::max());  // Dla doubli można dać
      if (iszero(sta)) break;                           // infinity() zamiast
      ret += sta;                                       // max().
    }
    return ret;
  }
  vector<int> cut() {
    vector<int> ret;
    bfs();
    for (int i = 0; i < n; i++)
      if (odl[i])
        ret.push_back(i);
    return ret;
  }
  map<pair<int, int>, T> get_flowing() {  // Tam gdzie plynie 0 może nie być
    map<pair<int, int>, T> ret;           // krawędzi.
    for (int i = 0; i < n; i++)
      for (E& e : graf[i])
        if (*e.lim < e.orig)
          ret[make_pair(i, e.dest)] += e.orig - *e.lim;
    for (auto& i : ret) {
      const pair<int, int> rev{i.first.second, i.first.first};
      const T x = min(i.second, ret[rev]);
      i.second -= x;
      ret[rev] -= x;
    }
    return ret;
  }
};


struct Assignment {
  int score;
  vector<vector<int>> booksChosen;
};

Assignment optimal(const vector<Lib> &libs, int D, const vector<int> &scores, const vector<int> &order) {
  Assignment res;
  res.score = 0;
  
  FastFlow F;
  int B = scores.size();
  int L = libs.size();
  int S = B + L + 1;
  int T = B + L + 2;

  vector<int> ready_time(L, D);
  assert ((int) order.size() <= L);
  int day = 0;
  for (int i : order) {
    ready_time[i] = day + libs[i].signup_time;
    day += libs[i].signup_time;
  }
  assert (day <= D);

  vector<pair<int, int>> booksByScore;

  for (int i = 0; i < L; ++i) {
    F.add_edge(S, i, min((long long) libs[i].per_day * (D - ready_time[i]), (long long) B));
    for (int b : libs[i].books) {
      F.add_edge(i, L + b, 1);
    }
  }

  for (int i = 0; i < B; ++i) {
    // F.add_edge(L + i, T, 1, 0);
    booksByScore.push_back({scores[i], i});
  }

  sort (booksByScore.begin(), booksByScore.end(), greater<pair<int, int>> ());

  int flo = F.dinic(S, T);

  for (int i = 0; i < B; ++i) {
    int bb = booksByScore[i].second;
    F.add_edge(L + bb, T, 1);
    // F.add_edge(S, L + bb, 1);
    if (i + 1 == L || booksByScore[i + 1].first != booksByScore[i].first) {
      if(booksByScore[i].first % 50 == 0) cerr << "scores " << booksByScore[i].first << endl;
      flo += F.dinic(S, T);
    }
  }

  auto flows = F.get_flowing();
  
  res.booksChosen.resize(L);
  for (int i = 0; i < L; ++i) {
    for (int b : libs[i].books) {
      if (flows[{i, L + b}] > 0) res.booksChosen[i].push_back(b);
    }
  }

  for (int i = 0; i < B; ++i) {
    if (flows[{L + i, T}] == 1) res.score += scores[i]; 
  }

  return res;
}












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
  
  
  vector<int> all_books(B);
  for(int i = 0; i < B; ++i) {
    all_books[i] = i;
  }
  sort(all_books.begin(), all_books.end(), [&](int a, int b) {
    return score[a] > score[b];
  });
  vector<vector<int>> where_is(B);
  for(int il = 0; il < L; ++il) {
    for(int b : libs[il].books) {
      where_is[b].push_back(il);
    }
  }
  
  auto estimate = [&](const vector<int>& order, int exact) {
    if(!exact) {
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
        can = min(can, (int) llround(libs[il].books.size()));
        would += libs[il].sorted[can-1];
      }
      return would;
    }
    else if(exact == 2) {
          int day = 0;
          vector<int> only;
          for(int il : order) {
            day += libs[il].signup_time;
            if(day < D) {
              only.push_back(il);
            }
            else {
              day -= libs[il].signup_time;
            }
            // else {
              // break;
            // }
          }
          // order = only;
          // for(int i = 0; i < (int) order.size(); ++i) {
            // day += 
        // }
          
            return optimal(libs, D, score, only).score;
          }

    
          vector<pair<int,int>> stats(L);
        {
          int day = 0;
          for(int il : order) {
            day += libs[il].signup_time;
            if(day >= D) {
              break;
            }
            int can = min(1000LL * 1000, (long long) libs[il].per_day * (D - day));
            stats[il] = make_pair(can, libs[il].books.size());
          }
        }
        
        vector<vector<int>> his_books(L);
        long long total_score = 0;
        for(int b : all_books) {
          pair<int,int> best{INT_MIN, INT_MIN};
          for(int il : where_is[b]) {
            if(stats[il].first > 0) {
              best = max(best, make_pair(stats[il].first - stats[il].second, il));
            }
          }
          if(best.first == INT_MIN) {
            continue;
          }
          int il = best.second;
          total_score += score[b];
          his_books[il].push_back(b);
          stats[il].first--;
          for(int il : where_is[b]) {
            stats[il].second--;
          }
        }
        return (int) total_score;
    
    
  };
  
  vector<int> order;
  vector<bool> ready(L);
  long long current_score = 0;
  const int times = 330 * 1000 * 1000LL / L;
  for(int rep = 0; rep < times; ++rep) {
    vector<int> new_order = order;
    int type = rand() % 5;
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
      // pair<int, pair<int,int>> best;
      // best = make_pair(INT_MAX, make_pair(0, 0));
      // for(int rep = 0; rep < 3; ++rep) {
        // i = rand() % order.size();
        // j = rand() % order.size();
        // if(i == j) {
          // continue;
        // }
        // best = min(best, {abs(i-j), {i, j}});
      // }
      // if(best.first == INT_MAX) {
        // continue;
      // }
      swap(new_order[i], new_order[j]);
    }
    else if(type == 3) {
      if(order.empty()) {
        continue;
      }
      new_order.erase(new_order.begin() + rand() % new_order.size());
    }
    else if(type == 4) {
      if(new_order.empty()) {
        continue;
      }
      int i = rand() % new_order.size();
      int s = rand() % min(5, (int) new_order.size() - i);
      random_shuffle(new_order.begin() + i, new_order.begin() + i + s + 1);
    }
    else {
      assert(false);
    }
    
    bool exact = rep > times - 1000; // times - 20,000 dziala dobrze w E
    if(exact) {
      current_score = estimate(order, exact);
    }
    long long new_score = estimate(new_order, exact);
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
  cerr << estimate(order, false) << endl;
  auto exact = estimate(order, 2);
  cerr << exact << endl;
  // assert(exact <= 5237041);
  // cerr << estimate(order, true) << endl;
  
  ready = vector<bool>(L, false);
  // return 0;
  
  vector<pair<int,int>> stats(L);
  {
    int day = 0;
    for(int il : order) {
      day += libs[il].signup_time;
      if(day >= D) {
        break;
      }
      int can = min(1000LL * 1000, (long long) libs[il].per_day * (D - day));
      stats[il] = make_pair(can, libs[il].books.size());
    }
  }
  
  vector<vector<int>> his_books(L);
  long long total_score = 0;
  for(int b : all_books) {
    pair<int,int> best{INT_MIN, INT_MIN};
    for(int il : where_is[b]) {
      if(stats[il].first > 0) {
        best = max(best, make_pair(stats[il].first - stats[il].second, il));
      }
    }
    if(best.first == INT_MIN) {
      continue;
    }
    int il = best.second;
    total_score += score[b];
    his_books[il].push_back(b);
    stats[il].first--;
    for(int il : where_is[b]) {
      stats[il].second--;
    }
  }
  
  vector<bool> scanned(B);
  int day = 0;
  vector<pair<int, vector<int>>> strategy;
  for(int il : order) {
    if(!his_books[il].empty()) {
      strategy.emplace_back(il, his_books[il]);
    }
  }
  /*
  long long total_score = 0;
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
        cerr << "time = " << can << ",  " << remaining.size() << " / " << libs[il].books.size() << endl;
        if(can < (long long) remaining.size()) {
          remaining.resize(can);
        }
        long long gain = 0;
        for(int b : remaining) {
          gain += score[b];
        }
        gain = gain * 1000 * 1000 / pow(libs[il].signup_time, 1.);
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
  }*/
  // cerr << endl;
  printf("%d\n", (int) strategy.size());
  for(pair<int, vector<int>> pp : strategy) {
    printf("%d %d\n", pp.first, (int) pp.second.size());
    for(int x : pp.second) {
      printf("%d ", x);
    }
    puts("");
  }
  
  
  cerr << "score = " << total_score / 1000. / 1000. << " " << atoi(argv[1]) << endl;
}








