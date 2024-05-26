#include <iostream>
using namespace std;

typedef int KeyType;

typedef struct node
{
    KeyType key;
    struct node *next;
} NodeType;

typedef struct
{
    NodeType *firstp;
} HashTable;

// 1)插入集建表算法
void InsertHT(HashTable ha[], int &n, int m, KeyType k)
{
    int adr;
    adr = k % m;
    NodeType *q;
    q = new NodeType;
    q->key = k;
    q->next = NULL;
    if (ha[adr].firstp == NULL)
    {
        ha[adr].firstp = q;
    }
    else
    {
        q->next = ha[adr].firstp;
        ha[adr].firstp = q;
    }
    n++;
}

void CreateHT(HashTable ha[], int &n, int m, KeyType keys[], int total)
{
    for (int i = 0; i < m; i++)
    {
        ha[i].firstp = NULL;
    }
    n = 0;
    for (int i = 0; i < total; i++)
    {
        InsertHT(ha, n, m, keys[i]);
    }
}

// 2)删除算法
bool DeleteHT(HashTable ha[], int &n, int m, KeyType k)
{
    int adr;
    adr = k % m;
    NodeType *q, *preq;
    q = ha[adr].firstp;
    if (q == NULL)
    {
        return false;
    }
    if (q->key == k)
    {
        // 处理首结点（preq无法在while循环中处理）
        ha[adr].firstp = q->next;
        free(q);
        n--;
        return true;
    }
    preq = q;
    q = q->next;
    while (q != NULL && q->key != k)
    {
        preq = q;
        q = q->next;
    }
    if (q != NULL)
    {
        preq->next = q->next;
        free(q);
        n--;
        return true;
    }
    else
    {
        return false;
    }
}

// 3)查找算法
void SearchHT(HashTable ha[], int m, KeyType k)
{
    int cnt = 0, adr;
    adr = k % m;
    NodeType *q;
    q = ha[adr].firstp;
    while (q != NULL)
    {
        cnt++;
        if (q->key == k)
        {
            break;
        }
        q = q->next;
    }
    if (q != NULL)
    {
        printf("成功!:关键字%d比较%d次\n", k, cnt);
    }
    else
    {
        printf("失败!:关键字%d比较%d次\n", k, cnt);
    }
}

// 4)查找性能分析
void ASL(HashTable ha[], int n, int m)
{
    int succ = 0, unsucc = 0, s;
    NodeType *q;
    for (int i = 0; i < m; i++)
    {
        s = 0;
        q = ha[i].firstp;
        while (q != NULL)
        {
            q = q->next;
            s++;
            succ += s;
        }
        unsucc += s;
    }
    printf("成功的情况下ASL(%d)=%g\n", n, succ * 1.0 / n);
    printf("不成功的情况下ASL(%d)=%g\n", n, unsucc * 1.0 / m);
}