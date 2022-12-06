#include <iostream>
#include"BigInt.h" 

int main() {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("-876987654323456789098723456789065432345");
    c = BigInt("-876987654323456788111735802330192197791");
    a += b;
    //a = BigInt("*342355342322");
    std::cout << a << '\n';
    std::cout << c;

    return 0;
}