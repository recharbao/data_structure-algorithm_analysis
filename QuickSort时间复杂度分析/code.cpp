#include<iostream>
#include<ctime>
using namespace std;

void RandomQuickSort(int a[], int l, int r);

int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];
    srand(time(NULL));

    RandomQuickSort(a, 0, n - 1);

    for(int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}


void RandomQuickSort(int a[], int l, int r)
{
    if(l >= r) return;

    int pivot = a[l + rand() % (r - l + 1)];
    int i = l, j = r, mov = l;

    while (mov <= j)
        if(a[mov] > pivot) swap(a[mov], a[j--]);
        else if(a[mov] < pivot) swap(a[mov++], a[i++]);
        else mov++;
    
    RandomQuickSort(a, l, i);
    RandomQuickSort(a, i + 1, r);

    return;
}



/*

23
2 4 1 2 1 0 6 13 2 2 2 0 0 9 8 1 16 11 12 12 5 5 6

*/
