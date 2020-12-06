#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;

int main() {
    Complex z1, z2;
    int n;
    while (true) {
        cout << "Input complex numbers z1, z2:" << endl;
        cin >> z1 >> z2;
        if (!cin.good())
            break;
        cout << "z1 + z2 = " << z1 + z2 << endl;
        cout << "z1 * z2 = " << z1 * z2 << endl;
        cout << "z1 / z2 = " << z1 / z2 << endl;

        cout << "Input integer n for n-th roots: ";
        cin >> n;
        if (!cin.good() || n <= 0)
            break;
        Complex* root = new Complex[n];
        z1.roots(n, root);

        cout << "n-th roots of " << z1 << endl;
        for (int i = 0; i < n; ++i)
            cout << root[i] << endl;
        delete[] root;
    }
    return 0;
}
