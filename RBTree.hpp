#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_
#include <iostream>
#define black 0
#define red 1
template<typename T>
class RBTNode 
{
public:
    int color;
    T key;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    RBTNode(int color, T key, RBTNode* left, RBTNode* right, RBTNode* parent):
        color(color), key(key), left(left), right(right), parent(parent) {}
};
template<typename T>
class RBTree
{
private:
    RBTNode<T> *mRoot;

public:
    RBTree();
    ~RBTree();
    //前序遍历
    void preorder();
    //中序遍历
    void inorder();
    //后序遍历
    void postorder();

    //查找键值为key的节点
    RBTNode<T>* search(T key);

    // 查找最小结点：返回最小结点的键值。
    T minimum();
    // 查找最大结点：返回最大结点的键值。
    T maximum();

    // 将结点(key为节点键值)插入到红黑树中
    void insert(T key);
    
    void printTopColor()
    {
        std::cout << this->mRoot->color;
    }
    // 删除结点(key为节点键值)
    void remove(T key);
    // 打印红黑树
    void printTree();
    void destroy();
private:
    void preorder(RBTNode<T>* node) const;
    void inorder(RBTNode<T>* node) const;
    void postorder(RBTNode<T>* node) const;

    RBTNode<T>* search(RBTNode<T>* root, T key) const;

    RBTNode<T>* minimum(RBTNode<T>* root) const;
    RBTNode<T>* maximum(RBTNode<T>* root) const;

    void leftRotate(RBTNode<T>*& root, RBTNode<T>* node);
    void rightRotate(RBTNode<T>*& root, RBTNode<T>* node);
    void insert(RBTNode<T>*& root, RBTNode<T>* node);
    void afterInsert(RBTNode<T>*& root, RBTNode<T>* node);
    void remove(RBTNode<T>*& root, RBTNode<T>* node);
    void afterRemove(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
    void destroy(RBTNode<T>* &tree);
    void print(RBTNode<T>* tree, int direction);

};

template<typename T>
RBTree<T>::RBTree()
{
    this->mRoot = nullptr;
}
template<typename T>
RBTree<T>::~RBTree()
{
    destroy(this->mRoot);
    std::cout << "\nThe red black tree has been destroyed";
}

template<typename T>
void RBTree<T>::preorder(RBTNode<T>* root) const 
{
    if(root == nullptr)
        return;
    // std::cout<< root->key << " ";
    std::string color = (root->color == black) ? "black":"red";
    std::cout<< root->key << "(" << color <<") ";
    preorder(root->left);
    preorder(root->right);
}
template<typename T>
void RBTree<T>::preorder()
{
    preorder(this->mRoot);
}

template<typename T>
void RBTree<T>::inorder(RBTNode<T>* root) const 
{
    if(root == nullptr)
        return;
    
    inorder(root->left);
    // std::cout<< root->key << " ";
    std::string color = (root->color == black) ? "black":"red";
    std::cout<< root->key << "(" << color <<") ";
    inorder(root->right);
}
template<typename T>
void RBTree<T>::inorder()
{
    // std::cout << "inorder" << std::endl;
    inorder(this->mRoot);
}

template<typename T>
void RBTree<T>::postorder(RBTNode<T>* root) const 
{
    if(root == nullptr)
        return;
    
    postorder(root->left);
    postorder(root->right);
    std::string color = (root->color == black) ? "black":"red";
    std::cout<< root->key << "(" << color <<") ";
}
template<typename T>
void RBTree<T>::postorder()
{
    postorder(this->mRoot);
}
template<typename T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* root, T key) const
{
    if(root == nullptr || root->key == key)
        return root;
    if(key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}
template<typename T>
RBTNode<T>* RBTree<T>::search(T key)
{
    return search(this->mRoot, key);
}

template<typename T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* root) const
{
    if(root == nullptr)
        return nullptr;
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}
template<typename T>
T RBTree<T>::minimum()
{
    RBTNode<T>* ans = nullptr;
    ans = minimum(this->mRoot);
    if (ans != nullptr)
        return ans->key;
    else
        return (T)nullptr;
}

template<typename T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* root) const
{
    if(root == nullptr)
        return nullptr;
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root;
}
template<typename T>
T RBTree<T>::maximum()
{
    RBTNode<T>* ans = nullptr;
    ans = maximum(this->mRoot);
    if (ans != nullptr)
        return ans->key;
    else
        return (T)nullptr;
}

/* 
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y                
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry     
*     /   \                       /  \
*    ly   ry                     lx  ly  
*
*
*/
template<typename T>
void RBTree<T>::leftRotate(RBTNode<T>*& root, RBTNode<T>* x)
{
    RBTNode<T> *y = x->right;
    x->right = y->left;
    if(y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if(x->parent == nullptr)
        root = y;
    if(x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/* 
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x                  
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y  
*       / \                                   / \                   #
*      lx  rx                                rx  ry
* 
*/
template<typename T>
void RBTree<T>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y)
{
    RBTNode<T>* x = y->left;
    y->left = x->right;
    if(y->parent == nullptr)
        root = x;
    else
    {
        if(y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    x->parent = y->parent;
    x->right = y;
    y->parent = x;
}

template<typename T>
void RBTree<T>::afterInsert(RBTNode<T>*& root, RBTNode<T>* node)
{
    RBTNode<T> *parent, *gparent;
    while (1)
    {
        parent = node->parent;
        if(parent && parent->color == black)
            break;
        if(!parent)
            break;
        gparent = parent->parent;

        RBTNode<T> *uncle = (gparent->left == parent) ? gparent->right:gparent->left;
        if (uncle && uncle->color == red)
        {
            /*uncle color is red*/
            // std::cout << " uncle color is red ";
            parent->color = black;
            uncle->color = black;
            gparent->color = red;
            node = gparent;
            continue;
        }
        if (!uncle || (uncle && uncle->color == black))
        {
            /*uncle color is black or uncle not exist*/
            // std::cout << " 456sa4d56as4d56asd54 ";
            // std::cout << (int)(!uncle);
            // std::cout << (int)(uncle && uncle->color == black);
            if (node == parent->left && parent == gparent->left)
            {
                /*parent is left child and cur is left child*/
                /*change color and right rotate*/
                parent->color = black;
                gparent->color = red;
                rightRotate(root, gparent);

            }
            else if (node == parent->right && parent == gparent->right)
            {
                /*right child and right child*/
                /*change color and left rotate*/
                parent->color = black;
                gparent->color = red;
                // std::cout << "test " << node->key << std::endl;
                leftRotate(root, parent);
            }
            else if (node == parent->left && parent == gparent->right)
            {
                /*parent is right child and cur is left child*/
                /*RL  change color and right rotate then left rotate*/
                node->color = black;
                gparent->color = red;
                parent->color = red;
                rightRotate(root, parent);
                leftRotate(root, gparent);
            }
            else
            {
                /*LR*/
                node->color = black;
                gparent->color = red;
                parent->color = red;
                leftRotate(root, parent);
                rightRotate(root, gparent);
            }

            node = gparent;
        }
        // std::cout << "1231";
        root->color = black;
        // std::cout << "1231";
        // /*uncle存在*/
        // if (gparent->left && gparent->right)
        // { 
        //     RBTNode<T> *uncle = (gparent->left == parent) ? gparent->right:gparent->left;
        //     if (uncle->color == red)
        //     {
        //         /*uncle color is red*/
        //         parent->color = black;
        //         uncle->color = black;
        //         gparent->color = black;
        //         node = gparent;
        //     }
        //     else
        //     {
        //         /*uncle color is black*/

        //         if (node == parent->left && parent == gparent->left)
        //         {
        //             /*parent is left child and cur is left child*/
        //             /*change color and right rotate*/
        //             parent->color = black;
        //             gparent->color = red;
        //             rightRotate(root, gparent);

        //         }
        //         else if (node == parent->right && parent == gparent->right)
        //         {
        //             /*right child and right child*/
        //             /*change color and left rotate*/
        //             parent->color = black;
        //             gparent->color = red;
        //             leftRotate(root, gparent);
        //         }
        //         else if (node == parent->left && parent == gparent->right)
        //         {
        //             /*parent is right child and cur is left child*/
        //             /*RL  change color and right rotate then left rotate*/
        //             node->color = black;
        //             gparent->color = red;
        //             parent->color = red;
        //             rightRotate(root, parent);
        //             leftRotate(root, gparent);
        //         }
        //         else
        //         {
        //             /*LR*/
        //             node->color = black;
        //             gparent->color = red;
        //             parent->color = red;
        //             leftRotate(root, parent);
        //             rightRotate(root, gparent);
        //         }
        //     }
        // }
    }
    

}

template<typename T>
void RBTree<T>::insert(RBTNode<T>*& root, RBTNode<T>* node)
{
    node->color = red;
    RBTNode<T> *y = nullptr;
    RBTNode<T> *x = root;
    while (x != nullptr)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else if (node->key > x->key)
            x = x->right;
        else
            return;
    }
    node->parent = y;
    if (y != nullptr)
    {
        if(node->key < y->key)
            y->left = node;
        else 
            y->right = node;
    }
    else
        root = node;
    root->color = black;
    // std::cout<<"\n"<<node->key<<" ";
    // if(node->parent)
    //     std::cout << node->parent->key << " ";
    afterInsert(root, node);
}

template<typename T>
void RBTree<T>::insert(T key)
{
    RBTNode<T>* node = new RBTNode<T>(red, key, nullptr, nullptr, nullptr);
    insert(this->mRoot,node);
}


template<typename T>
void RBTree<T>::afterRemove(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    /*https://segmentfault.com/a/1190000022278733*/
    while(1)
    {
        RBTNode<T>* brother = nullptr;
        if(node == root)
            break;
        if(node && node->color == red)
            break;
        
        if(node == parent->left)
        {
            
            // if(brother->color == black && brother->right->color == red)
            // {
            //     brother->color = parent->color;
            //     brother->right->color = black;
            //     parent->color = black;
            //     leftRotate(root, parent);
            //     node = root;

            // }
            // else if (brother->color == black && brother->left->color == red && brother->right->color == black)
            // {

            // }
            // else if((!brother->left ||brother->left->color == black) && (!brother->right || brother->right->color == black))
            // {
            //     brother->color = red;
            //     node = parent;
            //     parent = parent->parent;
            // }
            // else
            // {

            // }

            brother = parent->right;
            if(brother->color == red)
            {
                /*2.1*/
                /*2.1 -> 2.4*/
                parent->color = red;
                brother->color = black;
                leftRotate(root, parent);
                brother = parent->right;
            }

            if((!brother->left || brother->left->color == black) && (!brother->right || brother->right->color == black))
            {
                /*2.4*/
                brother->color = red;
                node = parent;
                parent = parent->parent;
            }
            else
            {
                if(brother->color == black && brother->left->color == red && brother->right->color == black)
                {
                    /*2.3*/
                    /*2.3 -> 2.2*/
                    brother->color = red;
                    brother->left->color = black;
                    rightRotate(root, brother);
                    brother = parent->right;
                }

                /*2.2*/
                /*brother->color == black && brother->right->color == red*/
                /*end,the red-black tree is balanced*/
                brother->color = parent->color;
                brother->right->color = black;
                parent->color = black;
                leftRotate(root, parent);
                break;

            }
            
        }
        else
        {
            brother = parent->left;
            if(brother->color = red)
            {
                /*3.1*/
                /*3.1 -> 3.4*/
                parent->color = red;
                brother->color = black;
                rightRotate(root, parent);
                brother = parent->left;
            }

            if((!brother->left || brother->left->color == black) && (!brother->right || brother->right->color == black))
            {
                /*3.4*/
                brother->color = red;
                node = parent;
                parent = parent->parent;
            }
            else
            {
                if(brother->color == black && (brother->right->color == red) && (brother->left->color == black || !brother->left))
                {
                    /*3.3*/
                    /*3.3 -> 3.2*/
                    brother->color = red;
                    brother->right->color = black;
                    leftRotate(root, brother);
                    brother = parent->left;

                }
                /*3.2*/
                /*brother->color == black && brother->left->color == red*/
                /*end,the red-black tree is balanced*/
                brother->color = parent->color;
                brother->left->color = black;
                parent->color = black;
                rightRotate(root, parent);
                break;
            }

        }
        
    }
    /*root color must be black*/
    if(root)
        root->color = black;
}

template<typename T>
void RBTree<T>::remove(RBTNode<T>*& root, RBTNode<T>* node)
{
    RBTNode<T> *child, *parent;
    int color;
    if (node->left && node->right)
    {
        /*have two children*/
        /*The replacement node uses the successor node, which is the leftmost node of the right subtree*/
        RBTNode<T>* replace = nullptr;
        replace = node->right;
        while(replace->left != nullptr)
            replace = replace->left;
        
        if (node->parent)
        {
            if (node == node->parent->left)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else 
        {
            root = replace;
        }

        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        if (parent == node)
        {
            parent == replace;
            replace->color = node->color;
            replace->parent = node->parent;
            replace->left = node->left;
            node->left->parent = replace;
        }
        else
        {
            if (child)
                child->parent = parent;
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
            replace->color = node->color;
            replace->parent = node->parent;
            replace->left = node->left;
            node->left->parent = replace;
        }

        /*if replacement node color is black, we should repair BRtree*/
        /*if color is red, the child and parent node must be black or null, no effect on BRTree*/
        if (color == black)
            afterRemove(root, child, parent);

        delete node;
        return;

    }
    else if ((node->left && node->right == nullptr) || (node->left == nullptr && node->right))
    {
        /*one child, the replacement node is the child*/
        RBTNode<T>* replace = nullptr;
        replace = (node->left) ? node->left : node->right;
        color = node->color;
        parent = node->parent;
        child = replace;

        if (child)
            child->parent = parent;

        if (parent)
        {
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
        }
        else
            root = child;
        
        if(color == black)
            afterRemove(root, child, parent);
        delete node;
        return;
    }
    else
    {
        /*no child*/
        color = node->color;
        child = nullptr;
        parent = node->parent;

        if(parent)
        {
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
        }
        else
            root = child;
        
        if(color == black)
            afterRemove(root, child, parent);
        delete node;
        return;
    }   
}

template<typename T>
void RBTree<T>::remove(T key)
{
    RBTNode<T>* node = search(key);
    if(node != nullptr)
        remove(this->mRoot, node);
    return;
}

template<typename T>
void RBTree<T>::destroy(RBTNode<T>* &root)
{
    if(root == nullptr)
        return;

    destroy(root->left);
    destroy(root->right);

    delete root;
    root = nullptr;
    return;
}

template<typename T>
void RBTree<T>::destroy()
{
    destroy(this->mRoot);
}




template<typename T>
void RBTree<T>::printTree()
{
    
}
/*
                117(b)     
                /   \
            47(r) 163(b)
            /   \ /   \
        15(b) 76(b) 133(r) 185(r)
        / \     /\  /\      /\
            62(r) 98(r)


               



*/
#endif
