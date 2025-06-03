// Copyright 2022 NNTU-CS
#pragma once
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

// PMTree class represents a permutation tree that stores all possible
// permutations of a given set of elements in a tree structure
class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;

  std::shared_ptr<Node> getRoot() const { return root; }
  size_t getTotalPermutations() const { return total_permutations; }

 private:
  std::shared_ptr<Node> root;
  size_t total_permutations;
  void buildTree(std::shared_ptr<Node> parent,
                const std::vector<char>& remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
std::vector<char> generateAlphabet(int n);

#endif  // INCLUDE_TREE_H_
