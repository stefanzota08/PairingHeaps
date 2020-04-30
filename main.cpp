#include<iostream>
#include <fstream>
using namespace std;
int n;
char x[256];
struct HeapNode {

    int key;
    bool exista;
    HeapNode *leftChild;
    HeapNode *nextSibling;

    HeapNode():
        leftChild(NULL), nextSibling(NULL), exista(true) {}

    HeapNode(int key_, HeapNode *leftChild_, HeapNode *nextSibling_):
        key(key_), leftChild(leftChild_), nextSibling(nextSibling_) {}

    void addChild(HeapNode *node) {
        if(leftChild == NULL)
            leftChild = node;
        else {
            node->nextSibling = leftChild;
            leftChild = node;
        }
    }
};

bool Empty(HeapNode *node) {
    return (node == NULL);
}

HeapNode *Merge(HeapNode *A, HeapNode *B)
{
    if(A == NULL) return B;
    if(B == NULL) return A;


    if(A->key < B->key) {
        A->addChild(B);
        return A;
    }
    else {
        B->addChild(A);
        return B;
    }

    return NULL;
}

int FindMin(HeapNode *node) {
    return node->key;
}

HeapNode *Insert(HeapNode *node, int key) {
    return Merge(node, new HeapNode(key, NULL, NULL));
}

HeapNode *TwoPassMerge(HeapNode *node) {
    if(node == NULL || node->nextSibling == NULL)
        return node;
    else {
        HeapNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = NULL;
        B->nextSibling = NULL;

        return Merge(Merge(A, B), TwoPassMerge(newNode));
    }

    return NULL;
}

HeapNode *DeleteMin(HeapNode *node) {
    return TwoPassMerge(node->leftChild);
}

void LazyDelete(HeapNode *node, int x)
{
    if(node->key == x && node->exista == true)
        {
            node->exista = false;
        }
    if(node->nextSibling != NULL)
        LazyDelete(node->nextSibling, x);
    if(node->leftChild != NULL)
        LazyDelete(node->leftChild, x);
}


struct PairingHeap {
    HeapNode *root;

    PairingHeap():
        root(NULL) {}

    bool Empty(void) {
        return ::Empty(root);
    }

    int FindMin(void) {
        return ::FindMin(root);
    }

    void Insert(int key) {
        root = ::Insert(root, key);
    }

    void DeleteMin(void) {
        root = ::DeleteMin(root);
    }

    void Join(PairingHeap other) {
        root = ::Merge(root, other.root);
    }

    void LazyDelete(int x) {
        ::LazyDelete(root, x);
    }

};

int main() {
    ifstream f("test.txt");
    PairingHeap steff;
    f>>n;
    f.get();

    for(int j=1;j<=n;j++)
    {
        f.getline(x, 256);
        int actiune = x[0]-'0';
        switch (actiune)
        {
            case 1:
            {
                int elem = x[2]-'0';
                cout<<"[1] Adaugam in heap elementul: "<<elem<<endl;
                steff.Insert(elem);
            }
                break;
            case 2:
            {
                int elem = x[2]-'0';
                steff.LazyDelete(elem);
                cout<<"[2] Au fost sterse toate aparitiile elementului: "<<elem<<endl;
            }
                break;

            case 3:
                cout<<"[3] Minimul actual este: "<<steff.FindMin()<<endl;
                break;

            case 4:
            {
                int minim = steff.FindMin();
                cout<<"[4] Au fost sterse toate aparitiile minimului actual care este: "<<minim<<endl;
                while (steff.FindMin() == minim)
                    steff.DeleteMin();
            }
                break;
        }
    }
    return 0;
}
