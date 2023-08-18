//
// Created by mowah on 1/16/2022.
//
#include <iostream>
using namespace std;

template <class T>
class BinaryTree {

    BinaryTree<T>* left;
    BinaryTree<T>* right;
    BinaryTree<T>* parent;
    T value;

public:

    //Constructor
    BinaryTree()
    {
        left=nullptr;
        right=nullptr;
        parent = nullptr;
        value =0;
    }

    //Setter getters
    void setParent(BinaryTree<T>* elder)
    {
        parent = elder;
    }
    void setLeft(BinaryTree<T>* west)
    {
        left = west;
    }
    void setRight(BinaryTree<T>* east)
    {
        right = east;
    }
    void setTreeValue(T num)
    {
        value = num;
    }
    BinaryTree<T>* getLeft()
    {
        return left;
    }
    BinaryTree<T>* getRight()
    {
        return right;
    }
    T getTreeValue()
    {
        return value;
    }

    //Insert Functions
    void insertLeft(T content)
    {
        BinaryTree<T>* temp = new BinaryTree<T>;
        temp->setTreeValue(content);
        temp->setParent(this);
        left = temp;
    }
    void insertRight(T content)
    {
        BinaryTree<T>* temp = new BinaryTree<T>;
        temp->setTreeValue(content);
        temp->setParent(this);
        right = temp;
    }

    bool isLeaf()
    {
        return (left==nullptr && right == nullptr);
    }
    bool isRoot()
    {
        return (parent==nullptr);
    }

    int getSize()
    {
        return 1 +((left == nullptr) ? 0: left->getSize() ) + ((right == nullptr) ? 0 : right->getSize());
    }
    int getHeight()
    {
        return max(((left==nullptr)? 0 : 1 + left->getHeight()), (right==nullptr) ? 0 : 1+ right->getHeight());
    }
    int getDegree()
    {
        if (left == nullptr && right ==nullptr)
        {
            return 0;
        }
        else if ((left == nullptr && right != nullptr) || (left !=nullptr && right ==nullptr))
        {
            return 1;
        }
        else if (left != nullptr && right !=nullptr)
        {
            return 2;
        }
    }
    void display()
    {

        if (left!=nullptr && right!=nullptr)
        {
            cout << "(" << left->getTreeValue() << ")   " << getTreeValue() << "   (" << right->getTreeValue() << ")" << endl;
            left->display();
            right->display();
        }
        else if (left==nullptr && right != nullptr)
        {
            cout << "      " << getTreeValue() << "   (" << right->getTreeValue() << ")" << endl;
            right->display();
        }
        else if (left!=nullptr && right == nullptr)
        {
            cout << "(" << left->getTreeValue() << ")   " << getTreeValue()  << endl;
            left->display();
        }
        else if (left==nullptr && right==nullptr)
        {
            cout << "      " << getTreeValue() << endl;
        }

//        if (ptr != nullptr)
//        {
//            cout << "  " << ptr->getTreeValue();
//            display(ptr->getLeft());
//            display(ptr->getRight());
//
//        }
    }   //ptr needs to point to this

    void detach()
    {
        if (parent ==nullptr)
        {
            return;
        }
        if (parent->getLeft()==this)
        {
            parent->setLeft(nullptr);
        }
        else if (parent->getRight()==this)
        {
            parent->setRight(nullptr);
        }
        parent = nullptr;
    }
    void attach(BinaryTree<T>* tree)  //Attaches subtree "tree" to this.
    {
        if (tree->isRoot() == false)
        {
            tree->detach();
        }

        if (left == nullptr)
        {
            left = tree;
            tree->setParent(this);
        }
        else if (right == nullptr)
        {
            right = tree;
            tree->setParent(this);
        }
        else
        {
            cout << "Both Left and Right are unavailable." << endl;
            return;
        }

    }
    void erase()
    {
        delete left;
        delete right;
        if (parent->getLeft()==this)
        {
            parent->setLeft(nullptr);
        }
        else if (parent->getRight()==this)
        {
            parent->setRight(nullptr);
        }
        parent = nullptr;
        delete parent;
    }

    T top()
    {
        if(this->isRoot()==false)
        {
            return parent->top();

        }
        else
            return getTreeValue();
    }
    void perforateDown()
    {
        if (left==nullptr && right==nullptr)
        {
            erase();
            return;
        }
        else if (left !=nullptr && right != nullptr)
        {
            if (left->getTreeValue() < right->getTreeValue()) {
                setTreeValue(left->getTreeValue());
                left->perforateDown();
            } else {
                setTreeValue(right->getTreeValue());
                right->perforateDown();
            }
        }
        else if (left == nullptr && right != nullptr)
        {
            setTreeValue(right->getTreeValue());
            right->perforateDown();
        }
        else if (left != nullptr && right == nullptr)
        {
            setTreeValue(left->getTreeValue());
            left->perforateDown();
        }

    }
    void perforateUp()
    {
        if ((parent==nullptr) || (parent->getTreeValue() < getTreeValue() || (parent->getTreeValue()==getTreeValue())))
        {
            return;
        }
        else
        {
            T temp = getTreeValue();
            setTreeValue(parent->getTreeValue());
            parent->setTreeValue(temp);
            parent->perforateUp();
        }
    }

    void push(T value)
    {
        if (left == nullptr && right !=nullptr)
        {
            insertLeft(value);
            left->perforateUp();
            return;
        }
        else if (left !=nullptr && right == nullptr)
        {
            insertRight(value);
            right->perforateUp();
            return;
        }
        else if (left == nullptr && right == nullptr)
        {
            insertLeft(value);
            left->perforateUp();
            return;
        }

        if (left->getSize() > right->getSize())
        {
            right->push(value);
        }
        else if ((right->getSize() > left->getSize()) || right->getSize() == left->getSize())
        {
            left->push(value);
        }

    }
    T pop()
    {
        T temp = top();
        perforateDown();
        return temp;
    }

};

#ifndef INC_2021_FALL_WEEK12_ASSIGNMENT11_MOWAHHIDSHAKEEL_BINARYTREE_H
#define INC_2021_FALL_WEEK12_ASSIGNMENT11_MOWAHHIDSHAKEEL_BINARYTREE_H

#endif //INC_2021_FALL_WEEK12_ASSIGNMENT11_MOWAHHIDSHAKEEL_BINARYTREE_H
