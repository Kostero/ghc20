#include "bits/stdc++.h"

using namespace std;

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
    sort(books.begin(), books.end());
  }
};

int main(int argc, char** argv) {
  string input_file = argv[1];
  string output_file = argv[2];
  int B, L, D;
  vector <int> score;
  vector<Lib> libs;
  auto read_input = [&](const string& input_file) {
    freopen(input_file.c_str(), "r", stdin);
    scanf("%d%d%d", &B, &L, &D);
    score.resize(B);
    for(int i = 0; i < B; ++i) {
      scanf("%d", &score[i]);
    }
    libs.resize(L);
    for(int il = 0; il < L; ++il) {
      libs[il].read();
    }
  };
  int signing_time = 0;
  int signed_libraries = 0;
  auto read_output = [&](const string& output_file) -> int {
    freopen(output_file.c_str(), "r", stdin);
    int ret = 0;
    vector <bool> sign(L), scanned(B);
    int A;
    scanf("%d", &A);
    for (int i=0; i<A; i++) {
      int Y, K;
      scanf("%d%d", &Y, &K);
      if (sign[Y]) {
        printf("%d was already signed.\n", Y);
        exit(1);
      }
      sign[Y] = true;
      signing_time += libs[Y].signup_time;
      if (signing_time > D) break;
      signed_libraries++;
      long long allowed_to_scan = 1LL * (D - signing_time) * libs[Y].per_day;
      if (allowed_to_scan < K) {
        printf("In library %d, you are allowed to scan only %d books"
               "after signing it on %d day.\n", Y, allowed_to_scan, signing_time);
        exit(1);
      }
      for (int j=0; j<K; j++) {
        int B_id;
        scanf("%d", &B_id);
        if (!binary_search(libs[Y].books.begin(), libs[Y].books.end(), B_id)) {
          printf("Book %d cannot be find in library %d.\n", B_id, Y);
          exit(1);
        }
        if (scanned[B_id]) {
          printf("%d was already scanned.\n", B_id);
          exit(1);
        }
        scanned[B_id] = true;
        ret += score[B_id];
      }
    }
    return ret;
  };
  read_input(input_file);
  printf("Score: %d\n", read_output(output_file));
  printf("You signed %d libraries out of %d.\n", signed_libraries, L);
  printf("Signing libarary took %.2f on average.\n", 1.0 * signing_time / signed_libraries);
  return 0;
}
