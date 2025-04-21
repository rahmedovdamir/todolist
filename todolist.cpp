#include <iostream>
#include <string>
#include "func.h"
int main(){
    while(true){
        show_menu();
        int choice;
        std::cin >> choice;
        switch(choice){
            case 1:
                show_task();
                break;
            case 2:
                add_task();
                break;
            case 3:
                add_note();
                break;
            case 5:
                delete_task();
                break;
            case 6:
                std::cout<< "Выход\n" ;
                return 0;
            default:
                std::cout<< "Ошибочный ввод\n" ;
                break;
        }
    }
}