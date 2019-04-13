#include <iostream>

#include "Array.h"

template <class T>
void Menu(Array<T>&);

int main()
{
    Array<double> a(10);
    Menu(a);
    return 0;
}

template <class T>
void Menu(Array<T> & a)
{
    int n;
    while (true){
        std::cout << "0 - Exit\n1 - Push back element\n2 - Insert element at position\n3 - Drop element at position\n4 - Add element to array\n5 - Multiply array by an element\n6 - Write array\n";
        std::cin >> n;
        switch (n){
            case 0: return;

            case 1: {
                T k;
                std::cout << "Enter element you want to push: ";
                std::cin >> k;
                a.push_back(k);
                break;
            }

            case 2: {
                T k;
                int pos;
                std::cout << "Enter element and then position: ";
                std::cin >> k >> pos;
                a.insert(k,pos);
                break;
            }

            case 3:{
                int pos;
                std::cout << "Enter position: ";
                std::cin >> pos;
                a.drop(pos);
                break;
            }

            case 4:{
                int val;
                std::cout << "Enter addend: ";
                std::cin >> val;
                a += val;
                break;
            }

            case 5:{
                int val;
                std::cout << "Enter multiplicand: ";
                std::cin >> val;
                a *= val;
                break;
            }
            case 6: {
                std::cout << a;
                break;
            }
        }
    }
}
