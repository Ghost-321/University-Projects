#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>
#include <string>
#include <random>
#include "bst.hpp"

TEST(BST, emptyTree) {
  BST<std::string> tree {};
  EXPECT_EQ(tree.size(), 0);
}

TEST(BST, smallInsert) {
  BST<char> tree {};
  tree.insert('a');
  tree.insert('b');
  tree.insert('c');
  tree.insert('d');
  EXPECT_EQ(tree.size(), 4);
}

TEST(BST, insertAndFind) {
  BST<char> tree {};
  tree.insert('a');
  tree.insert('b');
  tree.insert('c');
  tree.insert('d');
  BST<char>::Node* node = tree.find('e');
  EXPECT_EQ(node, nullptr);
  node = tree.find('c');
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, 'c');
}

TEST(BST, initializerList) {
  BST<char> tree {'x', 'y', 'z'};
  EXPECT_EQ(tree.size(), 3);
  BST<char>::Node* node = tree.find('y');
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, 'y');
}

TEST(BST, successorChar) {
  BST<char> tree {'b', 'c', 'a', 'f', 'e', 'd'};
  BST<char>::Node* node = tree.successor('e');
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, 'f');
  // maximum key
  node = tree.successor('f');
  EXPECT_EQ(node, nullptr);
}

TEST(BST, successorInt) {
  BST<int> tree {9, 3, 1, 8, 74, 7, -10, 5};
  BST<int>::Node* node = tree.successor(-10);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, 1);
  node = tree.successor(8);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, 9);
  // key not in the tree
  node = tree.successor(0);
  EXPECT_EQ(node, nullptr);
  // maximum key
  node = tree.successor(74);
  EXPECT_EQ(node, nullptr);
}

TEST(BST, successorString) {
  BST<std::string> tree {"hello", "how", "are", "you", "world"};
  BST<std::string>::Node* node = tree.successor("world");
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, "you");
  node = tree.successor("hello");
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, "how");
}

TEST(BST, makeVectorInitList) {
  BST<char> tree {'r', 'a', 'y', 's', 'q', 't'};
  std::vector<char> vec = tree.makeVector();
  EXPECT_EQ(vec, std::vector<char>({'a', 'q', 'r', 's', 't', 'y'}));
}

TEST(BST, makeVectorInitListWithDuplicates) {
  BST<char> tree {'r', 'a', 'y', 's', 'r', 'q', 't', 'a', 'y'};
  std::vector<char> vec = tree.makeVector();
  EXPECT_EQ(vec, std::vector<char>({'a', 'q', 'r', 's', 't', 'y'}));
}

TEST(BST, makeVectorPush) {
  std::vector<int> vec {6, -1, 99, 43, -67, 3, 7, 10};
  BST<int> tree {};
  for (auto x : vec) {
    tree.insert(x);
  }
  std::sort(vec.begin(), vec.end());
  std::vector<int> treeVec = tree.makeVector();
  EXPECT_EQ(treeVec, vec);
}

std::vector<int>
generateVectorWithoutDuplicates(int n, unsigned seed) {
  std::mt19937 mt {seed};
  std::uniform_int_distribution<int> dist;
  std::unordered_set<int> setto;
  std::vector<int> vec;
  vec.reserve(n);
  int i = 0;
  while (i < n) {
    int val = dist(mt);
    if (!setto.contains(val)) {
      setto.insert(val);
      vec.push_back(val);
      ++i;
    }
  }
  return vec;
}

TEST(BST, insert) {
  const unsigned seed {23'982'398};
  std::vector<int> vec = generateVectorWithoutDuplicates(30, seed);
  BST<int> tree {};
  for (int x : vec) {
      tree.insert(x);
  }
  EXPECT_EQ(vec.size(), static_cast<unsigned>(tree.size()));
  std::mt19937 mt {seed};
  std::uniform_int_distribution<unsigned> index_dist(0, vec.size()-1);
  // don't insert duplicates
  for (int i = 0; i < 5; ++i) {
    unsigned index = index_dist(mt);
    tree.insert(vec[index]);
    EXPECT_EQ(vec.size(), static_cast<unsigned>(tree.size()));
  }
}

TEST(BST, find) {
  const unsigned seed {8'433'498};
  std::vector<int> vec = generateVectorWithoutDuplicates(50, seed);
  BST<int> tree;
  std::unordered_set<int> setto;
  for (int x : vec) {
    tree.insert(x);
    setto.insert(x);
  }
  std::mt19937 mt {seed};
  int vecSize = static_cast<int>(vec.size());
  std::uniform_int_distribution<int> index_dist {0, vecSize - 1};
  const int numTrials = 20;
  for (int i = 0; i < numTrials; ++i) {
      int index = index_dist(mt);
      BST<int>::Node* node = tree.find(vec[index]);
      ASSERT_NE(node, nullptr);
      EXPECT_EQ(node->key, vec[index]);
  }
  std::uniform_int_distribution<int> val_dist;
  for (int i = 0; i < numTrials; ++i) {
    int val = val_dist(mt);
    if (!setto.contains(val)) {
      BST<int>::Node* node = tree.find(val);
      EXPECT_EQ(node, nullptr);
    }
  }
}

TEST(BST, min) {
  const unsigned seed {3'278'280};
  std::vector<int> vec = generateVectorWithoutDuplicates(50, seed);
  BST<int> tree;
  for (int x : vec) {
      tree.insert(x);
  }
  BST<int>::Node* node = tree.min();
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->key, *min_element(vec.begin(), vec.end()));
}

TEST(BST, inorder) {
  const unsigned seed {27'788'711};
  std::vector<int> vec = generateVectorWithoutDuplicates(50, seed);
  BST<int> tree;
  for (int x : vec) {
    tree.insert(x);
  }
  std::sort(vec.begin(), vec.end());
  std::vector<int> treeVector = tree.makeVector();
  EXPECT_EQ(treeVector, vec);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
