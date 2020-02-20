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
      cerr << "scores " << booksByScore[i].first << endl;
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


  vector<int> kol;
  int ss;
  scanf("%d", &ss);
  for (int rr = 0; rr < ss; ++rr) {
    int l, ile;
    scanf("%d %d", &l, &ile);
    int x;
    while (ile--) scanf("%d", &x);
    kol.push_back(l);
  }

  Assignment ass = optimal(libs, D, score, kol);

  printf("%d\n", ss);
  for (int l : kol) {
    printf("%d %d\n", l, (int) ass.booksChosen[l].size());
    for (int b : ass.booksChosen[l]) printf("%d ", b);
    printf("\n");
  }
  cerr << "newScore = " << ass.score << endl;
}












