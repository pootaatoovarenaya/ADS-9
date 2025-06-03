// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

void printExample() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  std::cout << "All permutations for {1,2,3}:" << std::endl;
  auto perms = getAllPerms(tree);
  for (const auto& perm : perms) {
    for (char c : perm) {
      std::cout << c;
    }
    std::cout << std::endl;
  }

  std::cout << "\nGetting permutations by index:" << std::endl;
  for (int i = 1; i <= 6; ++i) {
    auto perm1 = getPerm1(tree, i);
    auto perm2 = getPerm2(tree, i);

    std::cout << "Permutation " << i << ": ";
    for (char c : perm1) std::cout << c;
    std::cout << " (getPerm1), ";
    for (char c : perm2) std::cout << c;
    std::cout << " (getPerm2)" << std::endl;
  }
}

void runExperiment() {
  std::ofstream data_file("experiment_data.csv");
  data_file << "n,getAllPerms_time,getPerm1_time,getPerm2_time\n";

  std::random_device rd;
  std::mt19937 gen(rd());

  for (int n = 1; n <= 10; ++n) {
    auto elements = generateAlphabet(n);
    PMTree tree(elements);
    size_t total_perms = tree.getTotalPermutations();

    // Generate random permutation indices for testing
    std::uniform_int_distribution<> distr(1, total_perms);
    const int test_cases = 10;
    std::vector<int> test_nums(test_cases);
    for (int i = 0; i < test_cases; ++i) {
      test_nums[i] = distr(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto all_perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double all_perms_time = std::chrono::duration<double>(end - start).count();

    double perm1_total_time = 0;
    for (int num : test_nums) {
      start = std::chrono::high_resolution_clock::now();
      auto perm = getPerm1(tree, num);
      end = std::chrono::high_resolution_clock::now();
      perm1_total_time += std::chrono::duration<double>(end - start).count();
    }

    double perm2_total_time = 0;
    for (int num : test_nums) {
      start = std::chrono::high_resolution_clock::now();
      auto perm = getPerm2(tree, num);
      end = std::chrono::high_resolution_clock::now();
      perm2_total_time += std::chrono::duration<double>(end - start).count();
    }

    data_file << n << "," << all_perms_time << ","
              << perm1_total_time/test_cases << ","
              << perm2_total_time/test_cases << "\n";
    std::cout << "n=" << n << " completed." << std::endl;
  }

  data_file.close();
}

int main() {
  // Demonstration of basic functionality
  printExample();
  runExperiment();
  return 0;
}
