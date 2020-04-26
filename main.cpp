#include "src/Experimentator.h"

int main()
{
    Experimentator h = Experimentator();

    //getting the overall picture

    h.setOutput(R"(C:\Users\vultu\CLionProjects\multiplication-workshop\results\overview_opti.csv)");
    h.conduct_experiment(20100, 3, true);

    //finding the intersection of karatsuba and school

//    h.setOutput(R"(C:\Users\vultu\CLionProjects\multiplication-workshop\results\intersection.csv)");
//    std::set<std::string> algorithms_to_test = {"karatsuba", "school"};
//    h.setAlgorithms(algorithms_to_test);
//    h.conduct_experiment(100001, 3, false);

}
