#include <iostream>
#include "bpool.h"


int main(){
    bpool bp(4);
    bp.add_task([](){
        std::cout << "hello 1" << std::endl;
    });
    bp.add_task([](){
        std::cout << "hello 2" << std::endl;
    });
    bp.add_task([](){
        std::cout << "hello 3" << std::endl;
    });
    bp.add_task([](){               
        std::cout << "hello 4" << std::endl;
    });
    bp.add_task([](){
        std::cout << "hello 5" << std::endl;
    });
    bp.add_task([](){
        std::cout << "hello 6" << std::endl;
    });
    bp.add_task([](){
        std::cout << "hello 7" << std::endl;
    });

}