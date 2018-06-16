#include"node.hpp"


void test_add(){
    Constant one(1.0);
    auto x = Variable(3.0, "x_0");

    auto result = Add(x, x);
    auto result2 = Add(result, one);
    auto result3 = Add(result2, one);
    
    result3.backward(1.0);
    std::cout << x.get_grad() << std::endl;


    std::cout << result3.forward() << std::endl;
    result3.print();
    // double inc = 1.0;
    std::cout << x.get_grad() << std::endl;
    std::cout << std::endl;
}

void test_pow(){
    auto x = Variable(3.0, "x");
    Constant one(1.0);


    auto result1 = Add(x, one);
    auto result2 = Pow(result1);
    result2.print();
}