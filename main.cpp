#include "src2/Experimentator.h"
//#include "src/Multiplicator.h"

int main()
{
//    Multiplicator m = Multiplicator();

//    m.conduct_experiment(100,10,10,R"(C:\Users\vultu\CLionProjects\multiplication-workshop\results\experiment_1.csv)");
//
    Experimentator h = Experimentator();
    h.setOutput(R"(C:\Users\vultu\CLionProjects\multiplication-workshop\results\experiment_2.csv)");
    h.conduct_experiment(1000, 5, 10);

    //    Number r1;
    //    Number r2;
    //    r1.generate_random(50, 1);
    //    r2.generate_random(50, 2);
    //    r1.print();
    //    r2.print();

    //    auto start1 = std::chrono::high_resolution_clock::now();
    //    auto c = calculator.karatsuba_mult(r1, r2);
    //    auto end1 = std::chrono::high_resolution_clock::now();
    //    auto start2 = std::chrono::high_resolution_clock::now();
    //    auto d = calculator.school_mult(r1, r2);
    //    auto end2 = std::chrono::high_resolution_clock::now();
    //    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    //
    //    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    //    std::cout<<duration1.count()<<std::endl<<duration2.count();
    //    auto c = calculator.karatsuba_mult(r1, r2);
    //    auto d = calculator.school_mult(r1, r2);
    //    c.print();
    //    d.print();
}
