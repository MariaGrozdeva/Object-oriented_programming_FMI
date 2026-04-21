#include <iostream>
#include "ComplexNVector.h"

int main()
{
    ComplexNVector v1(3);
    v1[0] = ComplexNumber(1, 2);  // 1 + 2i
    v1[1] = ComplexNumber(3, 4);  // 3 + 4i
    v1[2] = ComplexNumber(5, 6);  // 5 + 6i

    ComplexNVector v2(3);
    v2[0] = ComplexNumber(2, -1); // 2 - 1i
    v2[1] = ComplexNumber(0, 3);  // 0 + 3i
    v2[2] = ComplexNumber(1, -2); // 1 - 2i

    std::cout << "v1 = " << v1 << "\n";
    std::cout << "v2 = " << v2 << "\n\n";

    // Copy constructor
    ComplexNVector v3(v1);
    std::cout << "v3 (copy of v1) = " << v3 << "\n\n";

    // Copy assignment
    ComplexNVector v4(3);
    v4 = v2;
    std::cout << "v4 (assigned from v2) = " << v4 << "\n\n";

    // operator+
    ComplexNVector sum = v1 + v2;
    std::cout << "v1 + v2 = " << sum << "\n";

    // operator-
    ComplexNVector diff = v1 - v2;
    std::cout << "v1 - v2 = " << diff << "\n\n";

    // operator* (scalar)
    ComplexNumber scalar(2, 0); // real scalar 2
    ComplexNVector scaled = v1 * scalar;
    std::cout << "v1 * 2 = " << scaled << "\n";

    ComplexNVector scaled2 = scalar * v1; // commutative
    std::cout << "2 * v1 = " << scaled2 << "\n\n";

    // dot product (Hermitian inner product)
    ComplexNumber dotResult = v1.dot(v2);
    std::cout << "v1 · v2 (dot) = " << dotResult << "\n\n";

    // operator|= (perpendicular)
    ComplexNVector perp1(2);
    perp1[0] = ComplexNumber(1, 0);
    perp1[1] = ComplexNumber(0, 0);

    ComplexNVector perp2(2);
    perp2[0] = ComplexNumber(0, 0);
    perp2[1] = ComplexNumber(1, 0);

    std::cout << "perp1 = " << perp1 << "\n";
    std::cout << "perp2 = " << perp2 << "\n";
    std::cout << "perp1 |= perp2 (perpendicular)? " << (operator|=(perp1, perp2) ? "yes" : "no") << "\n";
    std::cout << "v1 |= v2 (perpendicular)? "        << (operator|=(v1, v2)       ? "yes" : "no") << "\n\n";

    // operator+= and operator-=
    ComplexNVector v5(v1);
    v5 += v2;
    std::cout << "v1 += v2 -> " << v5 << "\n";

    ComplexNVector v6(v1);
    v6 -= v2;
    std::cout << "v1 -= v2 -> " << v6 << "\n\n";

    // cin >> 
    ComplexNVector v7(2);
    std::cout << "Enter 2 complex numbers (real im) for v7:\n";
    std::cin >> v7;
    std::cout << "v7 = " << v7 << "\n";

    return 0;
}
