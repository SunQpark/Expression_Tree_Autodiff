#pragma once
#include<vector>
#include"node.hpp"
#include"op_overload.hpp"


vector<ring> simple_taylor(unsigned n, ring eps){
    // computes derivatives of H = x^2 + y^3 - y^2 according to x, y to the n'th order.
    vector<ring> deriv_x(n);
    vector<ring> deriv_y(n);

    auto x = Variable(0.0, "x");
    auto y = Variable(1.0, "y");

    auto x1 = x^2;
    auto y1 = y^3;
    auto y2 = y^2;

    auto H_ = x1 + y1;
    auto H = H_ - y2;

    for (unsigned k = 0; k < n; k++){
        cout << "evaluation: " << H.forward() << endl;

        H.backward(eps / (k + 1));

        x.assign(x.data - y.get_grad());
        y.assign(y.data + x.get_grad());
        H.zero_grad();
        cout << "x: " << x.data << "\ty: " << y.data << endl;
        deriv_x[k] = x.data;
    }
    return deriv_x;

}

