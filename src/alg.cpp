// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <vector>
#include <memory>

void PMTree::create_tree(std::shared_ptr<Node> node, const std::vector<char>& data) {
  if (data.empty()) {
    return;
  }

  if (root && !node) {
    root.reset();  // Automatic memory management thanks to shared_ptr
    root = nullptr;
  }

  if (!root) {
    std::vector<std::shared_ptr<Node>> nodes;
    for (size_t i = 0; i < data.size(); ++i) {
      std::vector<std::shared_ptr<Node>> leaf_nodes;
      auto n = std::make_shared<Node>(data[i], leaf_nodes);
      nodes.push_back(n);
    }

    auto obj = std::make_shared<Node>('\0', nodes);
    root = obj;

    for (size_t i = 0; i < data.size(); ++i) {
      std::vector<char> t = data;
      t.erase(t.begin() + i);
      create_tree(root->children[i], t);
    }
    return;
  }

  for (size_t i = 0; i < data.size(); ++i) {
    std::vector<std::shared_ptr<Node>> leaf_nodes;
    auto n = std::make_shared<Node>(data[i], leaf_nodes);

    if (node->children.size() <= i) {
      node->children.resize(i + 1);
    }

    node->children[i] = n;

    std::vector<char> t = data;
    t.erase(t.begin() + i);
    create_tree(n, t);
  }
}

void collectPermutations(const std::shared_ptr<PMTree::Node>& node,
    std::vector<char>& current, std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  if (node->children.empty()) {
    if (!current.empty()) {
      result.push_back(current);
    }
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
  if (num < 1 || num > tree.getTotalPermutations()) {
    return {};
  }
  auto all_perms = getAllPerms(tree);
  return all_perms[num - 1];
}

std::vector<char> getPerm2Helper(const std::shared_ptr<PMTree::Node>& node,
    int& remaining) {
  if (node->children.empty()) {
    if (--remaining == 0) {
      return { node->value };
    }
    return {};
  }
  for (const auto& child : node->children) {
    auto result = getPerm2Helper(child, remaining);
    if (!result.empty()) {
      if (node->value != '\0') {
        result.insert(result.begin(), node->value);
      }
      return result;
    }
  }
  return {};
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1 || num > tree.getTotalPermutations()) {
    return {};
  }
  int remaining = num;
  return getPerm2Helper(tree.getRoot(), remaining);
}

void PMTree::create(std::vector<char>& data) {
  total_permutations = 1;
  for (size_t i = 1; i <= data.size(); ++i) {
    total_permutations *= i;
  }
  create_tree(nullptr, data);
}

std::vector<char> generateAlphabet(int n) {
  std::vector<char> alphabet;
  for (int i = 0; i < n; ++i) {
    alphabet.push_back('a' + i);
  }
  return alphabet;
}

PMTree::~PMTree() {
  // Destructor not needed as shared_ptr handles memory automatically
}
