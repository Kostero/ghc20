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

struct MinCost {
  using ll = int;
  struct kra {
    int cel, *prze1, *prze2;
    ll koszt;
  };
  int n=0, zr, uj;
  const ll inf=1e9;
  vector <vector <kra>> graf;
  vector <int> bylo, aktu;
  vector <ll> odl, pamodl;
  void vert(int v) {
    if (v>n) {
      n=v;
      graf.resize(n);
      bylo.resize(n);
      aktu.resize(n);
      odl.resize(n);
      pamodl.resize(n);
    }
  }
  void add_edge(int v, int u, int prze, ll koszt) {
    vert(v+1); vert(u+1);
    kra ret1{u, new int(prze), new int(0), koszt};
    kra ret2{v, ret1.prze2, ret1.prze1, -koszt};
    graf[v].push_back(ret1);
    graf[u].push_back(ret2);
  }
  void spfa() {
    for (int i=0; i<n; i++) {
      aktu[i]=1;
      pamodl[i]=inf;
    }
    aktu[zr]=pamodl[zr]=0;
    queue <int> kol;
    kol.push(zr);
    while(!kol.empty()) {
      int v=kol.front();
      kol.pop();
      if (aktu[v])
        continue;
      aktu[v]=1;
      for (kra i : graf[v]) {
        if (*i.prze1 && pamodl[v]+i.koszt<pamodl[i.cel]) {
          pamodl[i.cel]=pamodl[v]+i.koszt;
          aktu[i.cel]=0;
          kol.push(i.cel);
        }
      }
    }
  }
  void dij() {
    for (int i=0; i<n; i++)
      odl[i]=inf;
    priority_queue < pair <ll,int> > dijks;
    dijks.push({0, zr});
    while(!dijks.empty()) {
      ll dis=-dijks.top().first;
      int v=dijks.top().second;
      dijks.pop();
      if (odl[v]!=inf)
        continue;
      odl[v]=pamodl[v]+dis;
      for (auto j : graf[v])
        if ((*j.prze1) && odl[j.cel]==inf)
          dijks.push({-(dis+pamodl[v]-pamodl[j.cel]+j.koszt), j.cel});
    }
  }
  int dfs(int v) {
    if (v==uj)
      return 1;
    bylo[v]=1;
    for (int i=0; i<(int)graf[v].size(); i++) {
      if (!bylo[graf[v][i].cel] && (*graf[v][i].prze1) &&
      odl[v]+graf[v][i].koszt==odl[graf[v][i].cel] && dfs(graf[v][i].cel)) {
        (*graf[v][i].prze1)--;
        (*graf[v][i].prze2)++;
        return 1;
      }
    }
    return 0;
  }
  pair <int,ll> flow(int zrzr, int ujuj) {
    zr=zrzr; uj=ujuj;
    vert(zr+1); vert(uj+1);
    spfa();
    pair <int,ll> ret{0, 0};
    while(1) {
      dij();
      for (int i=0; i<n; i++)
        bylo[i]=0;
      if (!dfs(zr))
        break;
      ret.first++;
      ret.second+=odl[uj];
    }
    return ret;
  }
};


struct Assignment {
  int score;
  vector<vector<int>> books;
};

Assignment optimal(const vector<Lib> &libs, const vector<int> &limits, const vector<int> &scores) {
  Assignment res;
  

}

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








