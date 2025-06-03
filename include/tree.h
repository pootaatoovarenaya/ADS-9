// Copyright 2022 NNTU-CS
#pragma once
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>
#include <iostream>

class PMTree {
public:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  // Constructor builds the tree immediately using create_tree
  explicit PMTree(const std::vector<char>& elements) : root(nullptr), total_permutations(0) {
    create_tree(root, elements);
  }

  ~PMTree() = default;

  void create_tree(std::shared_ptr<Node>& parent, const std::vector<char>& remain);
  void create(std::vector<char>& elements);

  std::shared_ptr<Node> getRoot() const { return root; }
  int getTotalPermutations() const { return total_permutations; }

private:
  std::shared_ptr<Node> root;
  int total_permutations;
};

// External permutation interface functions
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
std::vector<char> generateAlphabet(int n);

#endif  // INCLUDE_TREE_H_
