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
        selfNode = new node;
        selfNode -> val = -1;   //判断空
        selfNode -> color = "B";        //>
        selfNode -> parent = parent;    //>
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
    if (b -> val != -1)  //>
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
    if (y -> left -> val != -1)
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
    if (y -> right -> val != -1)
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


void RBTrans(node* T, node*u, node* v)
{
    if (u -> parent == T)
    {
        T -> left = v;
    }
    else if(u == u -> parent -> left)
    {
        u -> parent -> left = v;
    }
    else
    {
        u -> parent -> right = v;
    }
    
    v -> parent = u -> parent;

}




void RBDeleteFixUp(node* T, node* x)
{
    node* w;   
    while (x != T -> left && x -> color == "B")
    {
        if (x == x -> parent -> left)
        {
            w = x -> parent -> right;

            if (w -> color == "R")
            {
                w -> color = "B";
                x -> parent -> color = "R";
                LeftRotate(T,x -> parent);
                w = x -> parent -> right;
            }
            if (w -> left -> color == "B" && w -> right -> color == "B")
            {
                w -> color = "R";
                x = x -> parent;
            }
            else if(w -> right -> color == "B")
            {
                w -> left -> color = "B";
                w -> color = "R";
                RightRotate(T, w);
                w = x -> parent -> right;
            }

            w -> color = x -> parent ->color;
            x -> parent -> color = "B";
            LeftRotate(T, x -> parent);
            x = T -> left;
        }

        else
        {
            w = x -> parent -> left;

            if (w -> color == "R")
            {
                w -> color = "B";
                x -> parent -> color = "R";
                RightRotate(T,x -> parent);
                w = x -> parent -> left;
            }

            if (w -> left -> color == "B" && w -> right -> color == "B")
            {
                w -> color = "R";
                x = x -> parent;
            }

            else if(w -> left -> color == "B")
            {
                w -> right -> color = "B";
                w -> color = "R";
                LeftRotate(T, w);
                w = x -> parent -> left;
            }

            w -> color = x -> parent ->color;
            x -> parent -> color = "B";
            RightRotate(T, x -> parent);
            x = T -> left; 
        }
    }
   x -> color = "B";
}


//删除操作
void RBDelete(node* T, node* z)
{
    node* x;
    node* y  = z;
    string yOrigColor = y -> color;
    if (z -> left -> val == -1)
    {
        x = z -> right;
        RBTrans(T, z, z -> right);
    }
    else if(z -> right -> val == -1)
    {
        x = z -> left;
        RBTrans(T, z, z -> left);
    }
    //找z节点的后继节点
    else
    {
        y = z -> right;
        while (y -> left -> val != -1)
        {
            y = y -> left;
        }

        yOrigColor = y -> color;
        x = y -> right;
        
        if (y -> parent != z)
        {
            RBTrans(T, y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }
        RBTrans(T, z, y);
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
    }
    if (yOrigColor == "B")
    {
        RBDeleteFixUp(T, x);
    }
}


int main(){
    node* root = new node;
    CreateRBTree(root, root -> left);
    cout << "RedBlackTree shape :" << endl << endl;
    CoutRBTree(root -> left);

    cout << endl << endl << endl << "RedBlackTree new shape :" << endl << endl;

    //删除一个节点
    RBDelete(root,root -> left -> left -> right);
    //RBDelete(root,root -> left -> right);
    //RBDelete(root, root -> left -> left -> left);
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
















