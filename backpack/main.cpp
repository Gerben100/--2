#include <iostream>
#include "LinkedList.hpp"
#include "LinkedListSequence.hpp"
#include "DynamicArray.hpp"
#include "ArraySequence.hpp"
#include "Sequence.hpp"

template<typename T>
bool comp(const T &first, const T &second) {
    return first <= second;
}

template<typename T>
T plus(T first, T second) {
    return first + second;
}

template<typename T>
void backpack(ArraySequence<ArraySequence<T> *> *A, ArraySequence<T> *W, ArraySequence<T> *P, int w, int n, T s) {
    for (int i = 0; i <= w; i++) A->Get(0)->Set(i, 0);
    for (int i = 0; i <= n; i++) A->Get(i)->Set(0, 0);
    T s0 = 1;
    int j = 1;

    for (int k = 1; k <= n; k++) {
        while (comp(s0, w)) {
            if (comp(W->Get(k), s0)) {
                A->Get(k)->Set(j, std::max(A->Get(k - 1)->Get(j), A->Get(k - 1)->Get(j - W->Get(k) / s) + P->Get(k)));
                j++;
            } else {
                A->Get(k)->Set(j, A->Get(k - 1)->Get(j));
                j++;
            }
            s0 = plus<T>(s0, s);

        }
        j = 1;
        s0 = 1;
    }
}

template<typename T>
int findAns(ArraySequence<ArraySequence<T> *> *A, int k, int w, ArraySequence<T> *W, int n) {
    n++;
    if (n > 0) {
        if (A->Get(k - 1)->Get(w) == A->Get(k)->Get(w)) {
            std::cout << k << "\t" << 0 << std::endl;
            findAns(A, k - 1, w, W, n);
        } else
            std::cout << k << "\t" << 1 << std::endl;
        findAns(A, k - 1, (w - W->Get(k)), W, n);
    }
}



int main() {
    int w, n, k;
    std::cin >> w >> n >> k;


    ArraySequence<int> *W = new ArraySequence<int>(k + 1);
    ArraySequence<int> *P = new ArraySequence<int>(k + 1);

    ArraySequence<ArraySequence<int> *> *A = new ArraySequence<ArraySequence<int> *>(n + 1);

    for (int i = 0; i < n + 1; i++) {
        ArraySequence<int> *temporary = new ArraySequence<int>(w + 1);
        A->Set(i, temporary);
    }


    W->Set(1, 3);
    P->Set(1, 1);

    W->Set(2, 4);
    P->Set(2, 6);

    W->Set(3, 5);
    P->Set(3, 4);

    W->Set(4, 8);
    P->Set(4, 7);

    W->Set(5, 9);
    P->Set(5, 6);


    int s = 1;
    backpack<int>(A, W, P, w, n, s);


    for (int k = 0; k <= n; k++) {
        for (int j = 1; j <= w; j++) {
            std::cout << A->Get(k)->Get(j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    findAns(A, k, w, W, 0);

    return 0;
}
