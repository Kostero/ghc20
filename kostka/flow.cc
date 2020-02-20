#include "bits/stdc++.h"

using namespace std;


struct Lib {
  int n, id, signup_time, per_day;
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
  int best_sc = 0;
  vector <bool> best_sol;
  int B, L, D;
  scanf("%d%d%d", &B, &L, &D);
  vector<int> score(B);
  for(int i = 0; i < B; ++i) {
    scanf("%d", &score[i]);
  }
  vector<Lib> libs(L);
  for(int il = 0; il < L; ++il) {
    libs[il].id = il;
    libs[il].read(score);
  }
  vector <int> covered(B);
  vector <bool> added(L);
  int books_covered = 0;

  auto get_score = [&](vector<bool> added2, bool print) -> int {
    vector <Lib> taken;
    for (int i=0; i<L; i++) if(added2[i]) taken.push_back(libs[i]);
    sort(taken.begin(), taken.end(), [&](Lib a, Lib b) {
      return a.n > b.n;
    });
    vector <int> order;
    for (auto t : taken) order.push_back(t.id);
    vector<bool> scanned(B), ready(L);
    int day = 0;
    vector<pair<int, vector<int>>> strategy;
    long long total_score = 0;
    while (true) {
      pair<int, pair<int, vector<int>>> best;
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
          if(gain > best.first) {
            best = {(int) gain, {il, remaining}};
          }
        }
      }
      if(best.first == 0) {
        break;
      }
      total_score += best.first;
      int il = best.second.first;
      ready[il] = true;
      strategy.emplace_back(il, best.second.second);
      for(int b : best.second.second) {
        assert(!scanned[b]);
        scanned[b] = true;
        // answer += score[b];
      }
      day += libs[il].signup_time;
    }
    if(print) {
      printf("%d\n", (int) strategy.size());
      for(pair<int, vector<int>> pp : strategy) {
        printf("%d %d\n", pp.first, (int) pp.second.size());
        for(int x : pp.second) {
          printf("%d ", x);
        }
        puts("");
      }
    }
    cerr << "TS " << total_score << "\n";
    return total_score;
  };

  auto dodaj = [&](int library) {
    if (added[library]) return;
    added[library] = true;
    for(auto x : libs[library].books) {
      covered[x]++;
      if (covered[x]==1) books_covered++;
    }
  };

  auto usun = [&](int library) {
    if (!added[library]) return;
    added[library] = false;
    for(auto x : libs[library].books) {
      covered[x]--;
      if (covered[x]==0) books_covered--;
    }
  };

  freopen("d.out", "r", stdin);
  int libraries;
  scanf("%d", &libraries);
  for (int i=0; i<libraries; i++) {
    int id, x;
    scanf("%d%d", &id, &x);
    dodaj(id);
    while(x--) {
      scanf("%d", &id);
    }
  }

  for (int rep=0; rep<10; rep++) {
    cerr << "REP " << rep << "\n";
    auto old_added = added;
    int library1 = rand()%L;
    while (added[library1]) library1 = rand()%L;
    int library2 = rand()%L;
    while (!added[library2]) library2 = rand()%L;
    dodaj(library1);
    usun(library2);
    {
      auto sc = get_score(added, false);
      cerr << best_sc << " " << sc << "\n";
      if (sc > best_sc) {
        best_sc = sc;
        best_sol = added;
      } else {
        added = old_added;
      }
    }
  }
  get_score(best_sol, true);
}
