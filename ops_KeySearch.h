#include <iostream>
using namespace std;

typedef int KeyType;
typedef char InfoType;

typedef struct
{
    KeyType key;
    InfoType data;
} RecType;

int SeqSearch(RecType R[], int n, KeyType k)
{
    // 顺序查找
    int i = 0;
    while (i < n && R[i].key != k)
    {
        i++;
    }
    if (i >= n)
    {
        return 0;
    }
    else
    {
        return i + 1;
    }
}

int SeqSearch1(RecType R[], int n, KeyType k)
{
    // 带哨兵的顺序查找
    // 存在数组越界访问的风险
    int i = 0;
    R[n].key = k;
    while (R[i].key != k)
    {
        i++;
    }
    if (i == n)
    {
        return 0;
    }
    else
    {
        return i + 1;
    }
}

int BinSearch(RecType R[], int n, KeyType k)
{
    // 折半查找
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (k == R[mid].key)
        {
            return mid + 1;
        }
        if (k < R[mid].key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return 0;
}

int BinSearch1(RecType R[], int n, KeyType k)
{
    // 求出第一个大于或等于k的元素位置
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (k <= R[mid].key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return high + 1;
}

#define MAXV1 100

typedef struct
{
    KeyType key;
    int link;
} IdxType;

int IdxSearch(IdxType I[], int b, RecType R[], int n, KeyType k)
{
    // 分块查找
    int s = (n + b - 1) / b; // 每块的元素个数
    int low = 0, high = b - 1, mid, i;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (I[mid].key >= k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    i = I[high + 1].link;
    while (i <= I[high + 1].link + s - 1 && R[i].key != k)
    {
        i++;
    }
    if (i < I[high + 1].link + s - 1)
    {
        return i + 1;
    }
    else
    {
        return 0;
    }
}