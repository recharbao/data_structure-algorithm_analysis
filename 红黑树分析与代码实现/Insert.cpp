#include<iostream>
#include<string.h>
using namespace std;

struct node
{  
    int val;  //节点的值
    struct node*  left;  //左孩子节点
    struct node*  right;  //右孩子节点
    struct node* parent;  //父节点
    string color;  //节点的颜色
};

//创建红黑树
void CreateRBTree(node* &parent,node* &selfNode){ // 引用传入的变量
    int Cval;
    string Ccolor;
    cin >> Ccolor;
    if (Ccolor == "#")
    {
        return;
    }
    else
    {
        cin >> Cval;
        selfNode = new node;
        selfNode -> val = Cval;
        selfNode -> color = Ccolor;
        selfNode -> parent = parent;
        CreateRBTree(selfNode, selfNode -> left);
        CreateRBTree(selfNode, selfNode -> right);
    }
}

//输出树
void CoutRBTree(node* b){
    if (b != NULL)
    {
        cout << "(" << b -> val << "," << b -> color <<")"<<endl;
        CoutRBTree(b -> left);
        CoutRBTree(b -> right);   
    }
    else
    {
        cout << "NULL" << endl;
    }
}


//左旋
void LeftRotate(node* T, node* x)
{
    node* y = x -> right;
    x -> right = y -> left;
    if (y -> left != NULL)
    {
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;
    if (x -> parent == T)
    {
        T -> left = y;
    }
    else if(x == x -> parent -> left)
    {
        x -> parent -> left = y;
    }
    else
    {
        x -> parent -> right = y;
    }
    
    y -> left = x;
    x -> parent =y;
}


//右旋
void RightRotate(node* T, node* x)
{
    node* y = x -> left;
    x -> left = y -> right;
    if (y -> right != NULL)
    {
        y -> right -> parent = x;
    }
    y -> parent = x -> parent;
    if (x -> parent == T)
    {
        T -> left = y;
    }
    else if(x == x -> parent -> left)
    {
        x -> parent -> left = y;
    }
    else
    {
        x -> parent -> right = y;
    }
    y -> right = x;
    x -> parent = y;
}


void RBInsertFixUp(node* T, node* z)
{
    node* y;
    while (z -> parent -> color == "R")
    {
        if (z -> parent == z -> parent -> parent -> left)
        {
            y = z -> parent -> parent -> right;
            if (y -> color == "R")
            {
                z -> parent -> color = "B";
                y -> color = "B";
                z -> parent -> parent -> color = "R";
                z = z -> parent -> parent;
            }
            else if (z == z -> parent -> right)
            {
                z = z -> parent;
                LeftRotate(T,z);
            }
            z -> parent -> color = "B";
            z -> parent -> parent -> color = "R";
            RightRotate(T,z -> parent -> parent);            
        }
        else
        {
            y = z -> parent -> parent -> left;
            if (y -> color == "R")
            {
                z -> parent -> color = "B";
                y -> color = "B";
                z -> parent -> parent -> color = "R";
                z = z -> parent -> parent; 
            }
            else if (z == z -> parent -> left)
            {
                z = z -> parent;
                RightRotate(T,z);
            }
            
            z -> parent -> color = "B";
            z -> parent -> parent -> color = "R";
            LeftRotate(T,z -> parent -> parent);
        }
    }

    T -> left -> color = "B";
}




//插入操作
void RBInsert(node* T, node* z)
{
    node* y = NULL;
    node* x = T ->left;
    while (x != NULL)
    {
        y = x;
        if (z -> val < x -> val)
            x = x -> left;
        else
            x = x -> right;
    }
    z -> parent = y;
    if (y == T)
    {
        T -> left = z;
    }
    else if(z -> val < y -> val)
    {
        y -> left = z;
    }
    else
    {
        y -> right = z;
    }
    z -> left = NULL;
    z -> right = NULL;
    z -> color = "R";
    RBInsertFixUp(T,z);
}


int main(){
    node* root = new node;
    CreateRBTree(root, root -> left);
    cout << "RedBlackTree shape :" << endl << endl;
    CoutRBTree(root -> left);

    cout << endl << endl << endl << "RedBlackTree new shape :" << endl << endl;

    //插入一个节点
    node* t = new node;
    t -> val = 4;
    t -> color = "R";
    RBInsert(root,t);
    CoutRBTree(root -> left);
    cout << endl << endl <<endl;

    return 0;
}




/*
B 11
R 2
B 1
#
#
B 7
R 5
#
#
R 8
#
#
B 14              
#
R 15 
#
#
*/
















