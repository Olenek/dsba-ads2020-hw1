#include <memory>
#include "src2/Experimentator.h"
//#include "src/Multiplicator.h"

int main()
{
    Experimentator h = Experimentator();
    h.setOutput(R"(C:\Users\vultu\CLionProjects\multiplication-workshop\results\intersection.csv)");
    std::set<std::string>  algorithms_to_test = {
            "karatsuba",
            "school"};
    h.setAlgorithms(algorithms_to_test);
    h.conduct_experiment(75000, 3);

//
//    Number r1 = Number();
//    Number r2 = Number();
//    r1.generate_random(70000, 1);
//    r2.generate_random(70000, 2);
//    std::unique_ptr<MultiplicatorV> a = std::make_unique<SchoolMultiplicator>();
//    std::unique_ptr<MultiplicatorV> b = std::make_unique<KaratsubaMultiplicator>();
//    std::unique_ptr<MultiplicatorV> c = std::make_unique<CaesarMultiplicator>();
//    std::cout<<"School "<< (measure_time([&](const Number&, const Number&){
//        return a->multiply(r1, r2); }, r1, r2)) << '\n';
//    std::cout<<"Karatsuba "<< (measure_time([&](const Number&, const Number&){
//        return b->multiply(r1, r2); }, r1, r2)) << '\n';
////
//    auto res1 =  a->multiply(r1, r2);
//    auto res2 =  c->multiply(r1, r2);
//    res1.print();
//    res2.print();



    //    Number r1;
    //    Number r2;
    //    r1.generate_random(50, 1);
    //    r2.generate_random(50, 2);
    //    r1.print();
    //    r2.print();

//        auto start1 = std::chrono::high_resolution_clock::now();
//        auto c = calculator.karatsuba_mult(r1, r2);
//        auto end1 = std::chrono::high_resolution_clock::now();
//        auto start2 = std::chrono::high_resolution_clock::now();
//        auto d = calculator.school_mult(r1, r2);
//        auto end2 = std::chrono::high_resolution_clock::now();
//        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    //
    //    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    //    std::cout<<duration1.count()<<std::endl<<duration2.count();
    //    auto c = calculator.karatsuba_mult(r1, r2);
    //    auto d = calculator.school_mult(r1, r2);
    //    c.print();
    //    d.print();
}
