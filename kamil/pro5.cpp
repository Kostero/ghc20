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
    for(int x : {2289,11112,2930,8172,1416,2073,3393,4318,15783,2577,4336,4971,9038,157,370,585,2096,2145,2359,2401,7706,13716,20788,24152,1108,1197,1959,2749,2811,4250,4646,6076,6758,8159,24846,20,1057,1377,1692,2788,3465,3922,8584,11598,650,1034,1277,3217,3358,8006,9333,9454,10016,11020,16426,19813,19815,21239,850,1075,1120,1239,1370,2095,3689,4390,4912,5174,6689,7952,8952,13347,15544,15612,15985,327,1170,1186,1861,3522,6893,7204,13908}) {
      mul[x] = 0;;
    }
    for(int x : {10369,17026,1335,1085,3999,5818,7675,2137,3165,4446,12315,822,2708,3133,4759,5710,8972,20400,26118,1841,4159,4719,14124,816,2309,2416,4908,5378,6792,7876,10417,12602,24325,8927,11690,16292,26119,405,1008,1890,2219,4346,4813,10548,13013,20247,1058,1799,10910,12100,12748}) {
      mul[x] = 0;;
    }
    for(int x : {18810,2656,7768,8992,10025,10834,12287,15707,216,8720,10893,3293,9022,9440,11305,13432,4085,4991,5592,8342,13864,20177,27699,388,416,1037,1392,1581,3781,5550,5870,6246,6962,7549,8256,16068,16992,24372,558,2844,3351,4637,6205,6276,18686,20725,346,1590,13826}) {
      mul[x] = 0;
    }
  while(true) {
    debug() << imie(day);
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
        gain *= mul[il];
        assert(gain <= 1000 * 1000 * 1000);
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
}








