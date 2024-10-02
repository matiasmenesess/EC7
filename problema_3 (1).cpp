//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<typename T>
struct NodeBT {
    T data;
    NodeBT *left = nullptr;
    NodeBT *right = nullptr;
};

template<typename T>
class Stack {

    vector<T> stack_;
    int max_size;

public:

    Stack(int size) : max_size(size) {}

    void push(T val) {
        if (stack_.size() != max_size) {
            stack_.push_back(val);
        } else {
            cout << "Stack is full!" << endl;
        }
    }

    void pop() {
        if (!stack_.empty()) {
            stack_.pop_back();
        } else {
            cout << "Stack is empty!" << endl;
        }
    }

    bool isempty() {
        return stack_.size() == 0;
    }

    bool isfull() {
        return stack_.size() == max_size;
    }

    T top() {
        return stack_.back();
    }
};

template<typename T>
struct Node {
    T data;
    Node<T> *prev = nullptr;
    Node<T> *next = nullptr;
};

template<typename T>
class Double_Linked_List {
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    int size = 0;

public:
    T front_() {
        return front->data;
    }

    T rear_() {
        return rear->data;
    }

    bool empty() {
        return front == nullptr;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = rear;

        if (rear == nullptr) {
            front = newNode;
        } else {
            rear->next = newNode;
        }
        rear = newNode;
        size++;
    }

    void pop_front() {
        if (front == nullptr) {
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        } else {
            front->prev = nullptr;
        }
        delete temp;
        size--;
    }

    int getSize() const {
        return size;
    }
};

template<typename T>
class Queue {
    Double_Linked_List<T> queue_;
    int max_size;

public:
    Queue(int size) : max_size(size) {}

    bool isempty() {
        return queue_.empty();
    }

    bool isfull() const {
        return queue_.getSize() == max_size;
    }

    T front() {
        return queue_.front_();
    }

    void enqueue(T val) {
        if (isfull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        queue_.push_back(val);
    }

    void dequeue() {
        if (isempty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        queue_.pop_front();
    }

    int getSize() const {
        return queue_.getSize();
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
    int findBottomLeftValue(TreeNode* root) {
        if(!root) return -1;
        queue<TreeNode*> queue;
        queue.push(root);
        int menorval = root->val;
        int level = 0;
        while(!queue.empty()){
            int nivel = queue.size();
            for(int i=0;i<nivel;i++){
                TreeNode* node = queue.front();
                queue.pop();
                if(i==0) menorval = node -> val;
                if(node->left!=nullptr){
                    queue.push(node->left);
                }
                if(node->right!=nullptr){
                    queue.push(node->right);
                }
            }
        }
        return menorval;
    }
};
