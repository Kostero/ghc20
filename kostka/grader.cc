#include "bits/stdc++.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc < 4) {
    cerr << "Usage: ./grader input_file output_file best_file\n";
    return 1;
  }
  string input_file = argv[1];
  string output_file = argv[2];
  string best_file = argv[3];
  auto read_input = [&](string input_file) {
    return;
  };
  auto read_output = [&](string output_file, bool debug) -> double {
    freopen(output_file.c_str(), "r", stdin);
    double res;
    cin >> res;
    return res;
  };
  read_input(input_file);
  double output_score = read_output(output_file, true);
  double best_score = read_output(best_file, false);
  cout << "Output score: " << output_score
       << " (best was: " << best_score << ")\n";
  if (best_score < output_score) {
    cout << "Updating best... ";
    string command = "cp " + output_file + " " + best_file;
    system(command.c_str());
    cout << "Done!\n";
  }
}
