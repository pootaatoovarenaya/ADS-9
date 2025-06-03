// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <random>
#include <vector>

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    total_permutations = 0;
    return;
  }
  
  std::vector<char> sorted_elements = elements;
  std::sort(sorted_elements.begin(), sorted_elements.end());
  
  root = std::make_shared<Node>('\0'); // Root node with null character
  buildTree(root, sorted_elements);
  
  total_permutations = 1;
  for (size_t i = 1; i <= elements.size(); ++i) {
    total_permutations *= i;
  }
}

void PMTree::buildTree(std::shared_ptr<Node> parent,
                      const std::vector<char>& remaining) {
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto child = std::make_shared<Node>(remaining[i]);
    parent->children.push_back(child);
    
    std::vector<char> new_remaining;
    new_remaining.reserve(remaining.size() - 1);
    new_remaining.insert(new_remaining.end(),
                        remaining.begin(), remaining.begin() + i);
    new_remaining.insert(new_remaining.end(),
                        remaining.begin() + i + 1, remaining.end());
    
    buildTree(child, new_remaining);
  }
}

void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  
  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, current, result);
    }
  }
  
  if (node->value != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.getRoot()) {
    return result;
  }
  
  std::vector<char> current;
  collectPermutations(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (num < 1 || static_cast<size_t>(num) > tree.getTotalPermutations()) {
    return {};
  }
  
  auto all_perms = getAllPerms(tree);
  return all_perms[num - 1];
}

size_t factorial(size_t n) {
  size_t result = 1;
  for (size_t i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1 || !tree.getRoot() ||
      static_cast<size_t>(num) > tree.getTotalPermutations()) {
    return {};
  }
  
  std::vector<char> result;
  auto current = tree.getRoot();
  int remaining_num = num - 1;
  
  std::vector<std::shared_ptr<PMTree::Node>> nodes = current->children;
  
  while (!nodes.empty()) {
    size_t n = nodes.size();
    size_t branch_size = factorial(n - 1);
    size_t selected = remaining_num / branch_size;
    
    if (selected >= nodes.size()) {
      return {};
    }
    
    result.push_back(nodes[selected]->value);
    remaining_num %= branch_size;
    nodes = nodes[selected]->children;
  }
  
  return result;
}

std::vector<char> generateAlphabet(int n) {
  std::vector<char> alphabet;
  for (int i = 0; i < n; ++i) {
    alphabet.push_back('a' + i);
  }
  return alphabet;
}
