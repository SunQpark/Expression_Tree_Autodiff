#include"node.hpp"
#include"op_overload.hpp"
#include"taylor.hpp"

void test_add(){
    auto one = Constant(1.0);
    // one.print();
    auto x = Variable(3.0, "x");
    auto result = Add(x, 3.0);
    auto result2 = Add(result, one);
    auto result3 = Add(result2, one);
    result2.print();
    result3.backward(1.0);
    std::cout << x.get_grad() << std::endl;


    // std::cout << result3.forward() << std::endl;
    // result3.print();
    // // double inc = 1.0;
    // std::cout << x.get_grad() << std::endl;
    // std::cout << std::endl;
}

void test_pow(){
    string str = "string";
    auto one = Constant(1.0);
    auto x = Variable(3.0, "x");

    auto result1 = Subtract(x, one);
    auto result2 = Pow(result1);
    auto result3 = Mul(result2, x);
    // auto result3 = Subtract(result2, one);
    result3.print();
    cout << endl << result3.forward() << endl;

    result3.backward(1.0);
    cout << x.get_grad() << endl;
}


void test_mult(){
    string str = "string";
    
    auto x = Variable(2.0, "x");
    auto y = Variable(4.0, "y");

    // auto p = Pow(x, 3.0);
    auto p = x^3;
    // auto q = Add(5.0, p);
    auto q = p + x;
    auto target = q / y;
    
    target.print();
    cout << endl << target.forward() << endl;

    target.backward(1);

    cout << "dL/dx" << x.get_grad() << endl;
    cout << "dL/dy" << y.get_grad() << endl;
    target.zero_grad();
    target.backward(0.01);
    cout << "dL/dx" << x.get_grad() << endl;
    cout << "dL/dy" << y.get_grad() << endl;
}


void test_diff(){
    auto x = Variable(0.0, "x");
    auto y = Variable(1.0, "y");

    auto x1 = x^2;
    auto y1 = y^3;
    auto y2 = y^2;

    auto H_ = x1 + y1;
    auto H = H_ - y2;
    cout << H.forward() << endl;

    H.backward(1.0);
    cout << "dH/dx at "<< x.cache << " :\t" << x.get_grad() << endl;
    cout << "dH/dy at "<< y.cache << " :\t" << y.get_grad() << endl;
}

void test_diff_eq(){
    unsigned n = 10;
    ring eps = 0.25;
    auto deriv_x = simple_taylor(n, eps);
    
    ring appr_x = 0.0;
    double fact_k = 1.0;
    for (unsigned k = 0; k<n; k++){
        
        if (k != 0){
            fact_k *= k; 
        }
        
        appr_x +=  deriv_x[k] * pow(eps, k) / fact_k;
        std::cout << endl << appr_x;
    }
}