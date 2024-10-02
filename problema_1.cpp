//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <vector>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void saveValue(TreeNode* root, vector<int>& values) {
        if (root == nullptr) {
            return;
        }

        values.push_back(root->val);
        saveValue(root->left, values);
        saveValue(root->right, values);
    }

    int getMinimumDifference(TreeNode* root) {
        vector<int> values;

        saveValue(root, values);

        sort(values.begin(), values.end());

        int minAbsDiff = 10000000000000; 

        for (int i = 1; i < values.size(); i++) {
            minAbsDiff = min(minAbsDiff, values[i] - values[i - 1]);
        }

        return minAbsDiff;        
    }
};
