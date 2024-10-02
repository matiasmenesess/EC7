#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T> * prev = nullptr;
    Node<T> * next = nullptr;
};

template<typename T>
class Double_Linked_List{
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
class queue{
    Double_Linked_List<T> queue_;
    int max_size;

public:
    queue(int size){
        max_size = size;
    }

    bool isempty() {
        return queue_.empty();
    }

    bool isfull() const {
        return queue_.getSize() == max_size;
    }

    T front(){
        return queue_.front_();
    }

    void enqueue(T val) {
        if (isfull()) {
            return;
        }
        queue_.push_back(val);
    }

    void dequeue() {
        if (isempty()) {
            return;
        }
        queue_.pop_front();
    }

    int getSize() const {
        return queue_.getSize();
    }
};




template<typename T>
struct NodeAVL {
    NodeAVL* right = nullptr;
    NodeAVL* left = nullptr;
    T data = T();
    int hb = 0;
};

template<typename T>
class AVL {
    NodeAVL<T>* root = nullptr;

public:
    void insert(T val) {
        vector<NodeAVL<T>*> path;
        root = insert_function(root, val, path);

        for (int i = path.size() - 1; i >= 0; --i) {
            balancear(path[i]); //no hago el balanceo aca pq se hace en balancear
        }
    }

    void remove(T val) {
        root = remove_function(root, val);
    }

    bool find(T value) {
        return find_function(root, value);
    }

    NodeAVL<T>* getRoot() const {
        return root;
    }

    void BFS() const {
        if (!root) {
            return;//vacio
        }

        queue<NodeAVL<T>*> q(100); //le di size pq 100 como la otra vez
        q.enqueue(root);

        while (!q.isempty()) {
            int LEVEL = q.getSize();
            for (int i = 0; i < LEVEL; ++i) {
                NodeAVL<T>* actual = q.front();
                q.dequeue();
                cout << actual->data << " ";

                if (actual->left) {
                    q.enqueue(actual->left);
                }
                if (actual->right) {
                    q.enqueue(actual->right);
                }
            }
            cout << endl;
        }
    }

private:
    NodeAVL<T>* insert_function(NodeAVL<T>* nodo, T val, vector<NodeAVL<T>*>& path) {
        if (nodo == nullptr) {
            auto* newNode = new NodeAVL<T>();
            newNode->data = val;
            newNode->hb = 0;
            return newNode;
        }

        path.push_back(nodo);

        if (val < nodo->data) {
            nodo->left = insert_function(nodo->left, val, path);
        } else if (val > nodo->data) {
            nodo->right = insert_function(nodo->right, val, path);
        }

        return nodo;
    }

    int height(NodeAVL<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + max(height(nodo->left), height(nodo->right));
    }

    int funcion_hb(NodeAVL<T>* nodo) {
        return height(nodo->left) - height(nodo->right); //formula
    }

    void balancear(NodeAVL<T>*& node) {
        if (node == nullptr) return;

        node->hb = funcion_hb(node);

        if (node->hb == 2) {
            if (funcion_hb(node->left) < 0) {
                RotacionDobleIzquierdaDerecha(node);
            } else {
                RotacionDerecha(node);
            }
        } else if (node->hb == -2) {
            if (funcion_hb(node->right) > 0) {
                RotacionDobleDerechaIzquierda(node);
            } else {
                RotacionIzquierda(node);
            }
        }
    }

    void RotacionIzquierda(NodeAVL<T>*& X) {
        //viceversa de derecha
        NodeAVL<T>* Z = X->right;
        X->right = Z->left;
        Z->left = X;
        X = Z;
    }

    void RotacionDerecha(NodeAVL<T>*& Y) {
        // izquierda (+) -> +
        NodeAVL<T>* Z = Y->left;
        Y->left = Z->right;
        Z->right = Y;
        Y = Z;
    }

    void RotacionDobleIzquierdaDerecha(NodeAVL<T>*& Y) {
        //  (-) -> (+)
        RotacionIzquierda(Y->left);
        RotacionDerecha(Y);
    }

    void RotacionDobleDerechaIzquierda(NodeAVL<T>*& Y) {
        //  (+) -> (-)
        RotacionDerecha(Y->right);
        RotacionIzquierda(Y);
    }

    NodeAVL<T>* remove_function(NodeAVL<T>* nodo, T val) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (val < nodo->data) {
            nodo->left = remove_function(nodo->left, val);
        } else if (val > nodo->data) {
            nodo->right = remove_function(nodo->right, val);
        } else {
            //ENCONTRADO
            if (nodo->left == nullptr && nodo->right == nullptr) {
                delete nodo; //si no tiene hijos lo borro
                nodo = nullptr;
            } else if (nodo->left == nullptr) {
                NodeAVL<T>* temp = nodo;
                nodo = nodo->right; // solo hijo derecho hacen cambio
                delete temp;
            } else if (nodo->right == nullptr) {
                NodeAVL<T>* temp = nodo;
                nodo = nodo->left; // solo hijo derecho hacen cambio
                delete temp;
            } else {
                // 2 hijos
                NodeAVL<T>* pred = predecesor_funcion(nodo->left);
                nodo->data = pred->data; // copio
                //elimino el nodo repetido
                nodo->left = remove_function(nodo->left, pred->data);
            }
        }

        if (nodo == nullptr) {
            return nodo;
        }

        //balanceo los nodos porque puede ser que se hayan cambiado sus hb
        balancear(nodo);

        return nodo;
    }

    NodeAVL<T>* predecesor_funcion(NodeAVL<T>* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    bool find_function(NodeAVL<T>* node, T value) {
        if (node == nullptr) {
            return false;
        } else if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return find_function(node->left, value);
        } else {
            return find_function(node->right, value);
        }
    }

    //lo comento pq sino tengo que poner AVL()
//    ~AVL() {
//        limpiar(root);
//    }
//
//    void limpiar(NodeAVL<T>* node) {
//        if (node != nullptr) {
//            limpiar(node->left);
//            limpiar(node->right);
//            delete node;
//        }
//    }

};

int main() {
    AVL<int> avlTree;

    avlTree.insert(7);
    avlTree.insert(3);
    avlTree.insert(10);
    avlTree.insert(9);
    avlTree.insert(11);
    avlTree.remove(7);


    cout << "Arbol AVL con BFS para comprobar" << endl;
    avlTree.BFS();

    return 0;
}

//Esta forma de insertar es sin el vector que me gusta porque sigue la misma logica del remove que no usa un vector que mantiene record de adonde vamos 
//y sino es recursiva pues cuando porfin termina de insertar, balancea el mismo y retorna subiendo por el camino, balancea, y retorna subiendo y asi hasta la raiz.
//NodeAVL<T>* insert_function(NodeAVL<T>* nodo, T val) {
//    
//    if (nodo == nullptr) {
//        auto* newNode = new NodeAVL<T>();
//        newNode->data = val;
//        newNode->hb = 0; /
//        return newNode;
//    }
//
//    if (val < nodo->data) {
//        nodo->left = insert_function(nodo->left, val);
//    } else if (val > nodo->data) {
//        nodo->right = insert_function(nodo->right, val);
//    } else {
//        return nodo;
//    }
//
//    nodo->hb = funcion_hb(nodo);
//
//    return balancear(nodo);
//}
