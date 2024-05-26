#include <iostream>
using namespace std;

typedef int KeyType;
typedef char InfoType;

typedef struct node
{
    KeyType key;
    InfoType data;
    struct node *lchild;
    struct node *rchild;
} BSTNode;

// 1)二叉顺序树的插入和排序
BSTNode *InsertBST(BSTNode *bt, KeyType k)
{
    if (bt == NULL)
    {
        bt = new BSTNode;
        bt->key = k;
        bt->rchild = NULL;
        bt->lchild = NULL;
    }
    else if (k < bt->key)
    {
        bt->lchild = InsertBST(bt->lchild, k);
    }
    else if (k > bt->key)
    {
        bt->rchild = InsertBST(bt->rchild, k);
    }
    return bt;
}

BSTNode *CreateBST(KeyType a[], int n)
{
    BSTNode *bt = NULL;
    int i = 0;
    while (i < n)
    {
        bt = InsertBST(bt, a[i]);
        i++;
    }
    return bt;
}

// 2)二叉顺序树的查找
BSTNode *SearchBST(BSTNode *bt, KeyType k)
{
    // 查找递归算法
    if (bt == NULL || bt->key == k)
    {
        return bt;
    }
    if (k < bt->key)
    {
        return SearchBST(bt->lchild, k);
    }
    else
    {
        return SearchBST(bt->rchild, k);
    }
}

BSTNode *Search1(BSTNode *bt, KeyType k)
{
    // 查找非递归算法
    BSTNode *p = bt;
    while (p != NULL)
    {
        if (p->key == k)
        {
            break;
        }
        else if (k < p->key)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }
    return p;
}

// 3)二叉排序树的删除
BSTNode *DeleteBST(BSTNode *bt, KeyType k)
{
    if (bt == NULL)
    {
        return bt;
    }

    BSTNode *p = bt;
    BSTNode *f = NULL;

    while (p != NULL)
    {
        if (p->key == k)
        {
            break;
        }
        f = p;
        if (k < p->key)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }

    if (p == NULL)
    {
        // 没有找到被删除结点p
        return bt;
    }

    if (p->lchild == NULL && p->rchild == NULL)
    {
        // p为叶子结点
        if (p == bt)
        {
            bt = NULL;
        }
        else
        {
            if (f->lchild == p)
            {
                f->lchild = NULL;
            }
            else
            {
                f->rchild = NULL;
            }
        }
    }

    else if (p->rchild == NULL)
    {
        // 只有左子树
        if (f == NULL)
        {
            bt = bt->lchild;
        }
        else
        {
            if (f->lchild == p)
            {
                f->lchild = p->lchild;
            }
            else
            {
                f->rchild = p->lchild;
            }
        }
        free(p);
    }

    else if (p->lchild == NULL)
    {
        // 只有右子树
        if (f == NULL)
        {
            bt = bt->rchild;
        }
        else
        {
            if (f->lchild == p)
            {
                f->lchild = p->rchild;
            }
            else
            {
                f->rchild = p->rchild;
            }
        }
    }

    else
    {
        // 有左右子树
        BSTNode *q = p->lchild;
        f = p;
        while (q->rchild != NULL)
        {
            f = q;
            q = q->lchild;
        }
        p->key = q->key;
        if (q == f->lchild)
        {
            f->lchild = q->lchild;
        }
        else
        {
            f->rchild = q->lchild;
        }
        free(q);
    }

    return bt;
}