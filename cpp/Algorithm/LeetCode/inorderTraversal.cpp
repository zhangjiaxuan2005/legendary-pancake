//
// Created by 17246 on 2025/8/13.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

void inorder(TreeNode* root, vector<int>& res) {
    if (!root) {
        return;
    }
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    inorder(root, res);
    return res;
}

vector<int> inorderTraversal2(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stk;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}

vector<int> inorderTraversal3(TreeNode* root) {
    vector<int> res;
    TreeNode *predecessor = nullptr;

    while (root != nullptr) {
        if (root->left != nullptr) {

            predecessor = root->left;
            while (predecessor->right != nullptr && predecessor->right != root) {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr) {
                predecessor->right = root;
                root = root->left;
            }

            else {
                res.push_back(root->val);
                predecessor->right = nullptr;
                root = root->right;
            }
        }

        else {
            res.push_back(root->val);
            root = root->right;
        }
    }
    return res;
}



int main() {
    auto root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    vector<int> res = inorderTraversal(root);
    for (int i : res) {
        cout << i << endl;
    }
    delete root->right->left;
    delete root->right;
    delete root;
}

