#include <gtest/gtest.h>

#include <vector>

#include "bst.h"

// Test fixture for BST
class BSTTest : public ::testing::Test {
 protected:
  BST bst;

  void SetUp() override {
    // Initialize the BST with some values for basic tests
    // 10, 5, 15, 3, 7, 12, 18
    bst.insertItem(10);
    bst.insertItem(5);
    bst.insertItem(15);
    bst.insertItem(3);
    bst.insertItem(7);
    bst.insertItem(12);
    bst.insertItem(18);
  }
};

// --- Existing Tests ---

// Test insertion
TEST_F(BSTTest, Insert) {
  std::vector<BST_node*> inorder;
  bst.inorderTrav(inorder, bst.get_root());
  std::vector<int> expected = {3, 5, 7, 10, 12, 15, 18};
  std::vector<int> result;
  for (auto node : inorder) {
    result.push_back(node->data);
  }
  EXPECT_EQ(result, expected);
}

// Test findItem
TEST_F(BSTTest, Find) {
  BST_node* node = bst.findItem(7);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, 7);

  node = bst.findItem(20);
  EXPECT_EQ(node, nullptr);
}

// Test removeItem
TEST_F(BSTTest, Remove) {
  bst.removeItem(10);
  std::vector<BST_node*> inorder;
  bst.inorderTrav(inorder, bst.get_root());
  std::vector<int> expected = {3, 5, 7, 12, 15, 18};
  std::vector<int> result;
  for (auto node : inorder) {
    result.push_back(node->data);
  }
  EXPECT_EQ(result, expected);
}

// Test inorder traversal
TEST_F(BSTTest, InorderTraversal) {
  std::vector<BST_node*> inorder;
  bst.inorderTrav(inorder, bst.get_root());
  std::vector<int> expected = {3, 5, 7, 10, 12, 15, 18};
  std::vector<int> result;
  for (auto node : inorder) {
    result.push_back(node->data);
  }
  EXPECT_EQ(result, expected);
}

// Test preorder traversal
TEST_F(BSTTest, PreorderTraversal) {
  std::vector<BST_node*> preorder;
  bst.preorderTrav(preorder, bst.get_root());
  std::vector<int> expected = {10, 5, 3, 7, 15, 12, 18};
  std::vector<int> result;
  for (auto node : preorder) {
    result.push_back(node->data);
  }
  EXPECT_EQ(result, expected);
}

// Test postorder traversal
TEST_F(BSTTest, PostorderTraversal) {
  std::vector<BST_node*> postorder;
  bst.postorderTrav(postorder, bst.get_root());
  std::vector<int> expected = {3, 7, 5, 12, 18, 15, 10};
  std::vector<int> result;
  for (auto node : postorder) {
    result.push_back(node->data);
  }
  EXPECT_EQ(result, expected);
}

// Test height
TEST_F(BSTTest, Height) { 
    EXPECT_EQ(bst.height(bst.get_root()), 3); 
}

// Test findMin
TEST_F(BSTTest, FindMin) {
  BST_node* minNode = bst.findMin(bst.get_root());
  ASSERT_NE(minNode, nullptr);
  EXPECT_EQ(minNode->data, 3);
}

// Test findMax
TEST_F(BSTTest, FindMax) {
  BST_node* maxNode = bst.findMax(bst.get_root());
  ASSERT_NE(maxNode, nullptr);
  EXPECT_EQ(maxNode->data, 18);
}

// --- New Tests from src/test_bst.cpp converted to GTest ---

TEST(BSTComprehensive, InsertRemove) {
    BST test_bst;
    
    // Test Insert (Iterative & Recursive)
    test_bst.insertItem(10, false); // Iterative
    test_bst.insertItem(5, true);   // Recursive
    test_bst.insertItem(15, false);
    test_bst.insertItem(3, true);
    test_bst.insertItem(7, false);
    test_bst.insertItem(12, true);
    test_bst.insertItem(18, false);

    // Verify structure via inorder traversal
    std::vector<BST_node*> nodes;
    test_bst.inorderTrav(nodes, test_bst.get_root());
    std::vector<int> expected = {3, 5, 7, 10, 12, 15, 18};
    
    ASSERT_EQ(nodes.size(), expected.size());
    for(size_t i=0; i<nodes.size(); ++i) {
        EXPECT_EQ(nodes[i]->data, expected[i]);
    }

    // Test Remove (Leaf)
    test_bst.removeItem(3, false); // Iterative
    EXPECT_EQ(test_bst.findItem(3), nullptr);

    // Test Remove (One child)
    test_bst.removeItem(5, true); // Recursive, 5 has right child 7
    EXPECT_EQ(test_bst.findItem(5), nullptr);
    BST_node* node7 = test_bst.findItem(7);
    ASSERT_NE(node7, nullptr);
    ASSERT_NE(node7->parent, nullptr);
    EXPECT_EQ(node7->parent->data, 10);

    // Test Remove (Two children)
    test_bst.removeItem(15, false); // Iterative, 15 has 12 and 18
    EXPECT_EQ(test_bst.findItem(15), nullptr);
    EXPECT_NE(test_bst.findItem(12), nullptr);
    EXPECT_NE(test_bst.findItem(18), nullptr);
    
    // Root removal
    test_bst.removeItem(10, true);
    EXPECT_EQ(test_bst.findItem(10), nullptr);
}

TEST(BSTComprehensive, RotationLogic) {
    BST rotation_bst;
    rotation_bst.insertItem(10);
    rotation_bst.insertItem(20);

    // Tree: 10 -> right: 20
    BST_node *root = rotation_bst.get_root();
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
    
    // Rotate Left on Root
    rotation_bst.rotateLeft(root);

    // New root should be 20
    BST_node *new_root = rotation_bst.get_root();
    ASSERT_NE(new_root, nullptr);
    EXPECT_EQ(new_root->data, 20);
    
    // Check for Cycle / Parent Pointer Bug
    EXPECT_EQ(new_root->parent, nullptr) << "New root's parent should be nullptr";
    
    if (new_root->parent != nullptr) {
        if (new_root->parent == root) {
             FAIL() << "CRITICAL: Cycle detected! Old root is parent of new root.";
        }
    }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
