//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso




#include <iostream>
#include <vector>
using namespace std;



template <typename T>
struct NodeBT{
    T data;
    int height;
    NodeBT<T>* left;
    NodeBT<T>* right;
    NodeBT():left(nullptr),right(nullptr),height(0){}
    explicit NodeBT(T value):data(value), height(0){
        left = right = nullptr;
    }    void killself(){
        if(left != nullptr){left->killself();}
        if(right != nullptr){right->killself();}
        delete this;
    }
};

template <typename T>
class AVL{
    NodeBT<T>* root;
public:
    AVL():root(nullptr){}
    void insert(T value){
        insert(root,value);
    }
    bool find(T value){
        if(!root){
            NodeBT<T>* nodo = find(root,value);
            if(nodo != nullptr){return true;}
        }
        else{
            return false;
        }
    }
    int height(){
        return height(root);
    }
    T minValue(){
        if(root){
            return minValue(root)->data;
        }
        throw std::invalid_argument("root not initialized\n");
    }
    T maxValue(){
        if(root){return maxValue(root)->data;}
        throw std::invalid_argument("root not initialized\n");
    }
    bool isBalanced(){
        if(root){
            return isBalanced(root);
        }
        else{
            throw std::invalid_argument("root isnt initialized\n");
        }
    }
    int size();
    void remove(T value){
        if(root){
            remove(root,value);
        }
        else {
            throw std::invalid_argument("root is not initialized\n");
        }
    }
    void display(){
        if(root == nullptr){
            throw std::invalid_argument("root is not initialized\n");
        }
        else{
            display(root);
        }
    }
    void displayPreOrder(){
        if(root == nullptr){
            throw std::invalid_argument("root is not initialized\n");
        }
        else{
            displayPreOrder(root);
        }
    }
    void clear(){
        if(root){
            root->killself();
            root = nullptr;
        }
    }

    void BFS(vector<int>& v) const {
        if (!root) {
            return;//vacio
        }
        queue<NodeBT<T>*> q(100); //le di size pq 100 como la otra vez
        q.enqueue(root);
        while (!q.isempty()) {
            int LEVEL = q.getSize();
            for (int i = 0; i < LEVEL; ++i) {
                NodeBT<T>* actual = q.front();
                q.dequeue();
                v.push_back(actual->data);
                if (actual->left) {
                    q.enqueue(actual->left);
                }
                if (actual->right) {
                    q.enqueue(actual->right);
                }
            }
        }
    }


    ~AVL(){clear();}
private:
    void insert(NodeBT<T>*& node,T value){
        if(node == nullptr){
            node = new NodeBT<T>(value);
        }
        else if(node->data < value){insert(node->right,value);}
        else if(node->data > value){insert(node->left,value);}        
        updateheight(node);
        balancear(node);

    }



    void remove(NodeBT<T>*& node,T value){
        if(node == nullptr){return;}
        else if(node->data < value){remove(node->right,value);}
        else if(node->data > value){remove(node->left,value);}
        else{
            if(node->left == nullptr && node->right == nullptr){delete node; node = nullptr;}
            else if(node->left == nullptr){
                NodeBT<T>* tmp = node;
                node = node->right;
                delete tmp; 
            }
            else if(node->right == nullptr){
                NodeBT<T>* tmp = node;
                node = node->left;
                delete tmp;
            }
            else{
                T temp = maxValue(node->left)->data;
                node->data = temp;
                remove(node->left,temp);
            }
        }
        if(node){
            updateheight(node);
            balancear(node);
        }
    }
    NodeBT<T>* find(NodeBT<T>* node, T value){
        if(node == nullptr){
            return nullptr;
        }
        if(node->data == value){
            return node;
        }
        else if(node->data < value){
            return find(node->right,value);
        }
        else {
            return find(node->left,value);
        }
    }
    int height(NodeBT<T>* node){
        if(node == nullptr){
            return -1;
        }
        return std::max(height(node->left),height(node->right)) + 1;
    }
    void updateheight(NodeBT<T>*& node){
        node->height = std::max(height(node->left),height(node->right)) + 1;
    }
    NodeBT<T>* minValue(NodeBT<T>* node){
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }
    NodeBT<T>* maxValue(NodeBT<T>* node){
        while(node->right != nullptr){
            node = node->right;
        }
        return node;
    }
    void display(NodeBT<T>* node){
        if(node == nullptr){return;}
        display(node->left);
        cout<<node->data<<" ";
        display(node->right);
    }
    void displayPreOrder(NodeBT<T>* node){
        if(node == nullptr){return;}
        cout<<node->data<<" ";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }
    bool isBalanced(NodeBT<T>* node){
        if(node == nullptr){return true;}

        int left = height(node->left);
        int right = height(node->right);
        int difference = std::abs(left - right);
        if(difference > 1){return false;}

        return isBalanced(node->left) && isBalanced(node->right);
    }

    void rrota(NodeBT<T>*& node){
        NodeBT<T>* hijo_izquierdo = node->left;
        node->left = hijo_izquierdo->right;
        hijo_izquierdo->right = node;
        updateheight(node);
        updateheight(hijo_izquierdo);
        node = hijo_izquierdo;
    }
    void lrota(NodeBT<T>*& node){
        NodeBT<T>* hijo_derecho = node->right;//hijo derecho de node
        node->right = hijo_derecho->left;// hijo derecho de node es ahora el hijp izquierdo del hijo derecho
        hijo_derecho->left = node;
        updateheight(node);
        updateheight(hijo_derecho);
        node = hijo_derecho;//con esto se converva los enlaces con el padre de node
    }
    void balancear(NodeBT<T>*& node){
        int hb = factorBalanceo(node);
        if(hb > 1){
            if(factorBalanceo(node->left)< 0){
                lrota(node->left);
            }
            rrota(node);
        }
        else if(hb < -1){
            if(factorBalanceo(node->right) > 0){
                rrota(node->right);
            }
            lrota(node);
        }
    }
    int factorBalanceo(NodeBT<T>* node){
        return height(node->left) - height(node->right);
    }
};


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
    TreeNode* convertBST(TreeNode* root) {
        int val_inicial= 0;
        ACUMULAR(root, val_inicial);        
        return root;
    }

int ACUMULAR(TreeNode* TN, int v){
    if(TN == nullptr){
        return v;
    }
    int DER = ACUMULAR(TN->right,v);
    if(TN->right != nullptr)
    TN->val = TN->val + TN->right->val;

    return ACUMULAR(TN->left, TN->val);
}

};