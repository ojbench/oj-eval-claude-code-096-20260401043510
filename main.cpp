#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int index;
    map<int, int> depthMap;      // node value -> depth
    map<int, int> parentMap;     // node value -> parent value

    // Build tree from preorder traversal (extended binary tree)
    TreeNode* buildTree(const vector<int>& preorder) {
        if (index >= preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[index]);
        index++;
        root->left = buildTree(preorder);
        root->right = buildTree(preorder);

        return root;
    }

    // DFS to record depth and parent of each node
    void dfs(TreeNode* node, int depth, int parent) {
        if (node == nullptr) return;

        depthMap[node->val] = depth;
        parentMap[node->val] = parent;

        dfs(node->left, depth + 1, node->val);
        dfs(node->right, depth + 1, node->val);
    }

    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    int areCousins(const vector<int>& preorder, int x, int y) {
        index = 0;
        depthMap.clear();
        parentMap.clear();

        TreeNode* root = buildTree(preorder);

        if (root == nullptr) {
            return 0;
        }

        // Record depth and parent info
        dfs(root, 0, -1);

        // Check if both nodes exist
        if (depthMap.find(x) == depthMap.end() || depthMap.find(y) == depthMap.end()) {
            deleteTree(root);
            return 0;
        }

        // Check if they are cousins (same depth, different parents)
        bool sameLevelDifferentParent = (depthMap[x] == depthMap[y]) && (parentMap[x] != parentMap[y]);

        deleteTree(root);

        return sameLevelDifferentParent ? 1 : 0;
    }
};

int main() {
    int q;
    cin >> q;

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> preorder;
    int val;
    while (cin >> val) {
        preorder.push_back(val);
    }

    Solution sol;
    for (const auto& query : queries) {
        cout << sol.areCousins(preorder, query.first, query.second) << endl;
    }

    return 0;
}
