#include <iostream>

int main() {
    uint input = 312051 - 9; 
    uint line_lenght = 3; 
    uint circle = 1;
    while( true ) {
        circle++; 
        line_lenght = circle * 2 - 1 ; 
        if (input < line_lenght * 4 + 4)
            break; 
        input -= line_lenght * 4 + 4; 
        std::cout << "Circlenumber: " << circle << "\t" << line_lenght *  4 + 4 << "\t remaning " << input << std::endl; 
    }

    int x = circle; 
    int y = circle - 1;

    std::cout << "Linelength " << line_lenght <<std::endl;

    std::cout << "X is " << x << std::endl; 
    std::cout << "Y is " << y << std::endl;
    std::cout << "Input is " << input << std::endl;
    std::cout << "-------------------------" << std::endl; 

    if (input != 0 && input > line_lenght) {
        y -= line_lenght; 
        input -= line_lenght;
    } else {
        y -= input;
    }
    std::cout << "X is " << x << std::endl; 
    std::cout << "Y is " << y << std::endl;
    std::cout << "Input is " << input << std::endl;
    std::cout << "-------------------------" << std::endl; 
    if (input != 0 && input > line_lenght + 1 ) {
        x -= line_lenght + 1 ; 
        input -= line_lenght + 1 ;
    } else {
        x -= input;
    }
    std::cout << "X is " << x << std::endl; 
    std::cout << "Y is " << y << std::endl;
    std::cout << "Input is " << input << std::endl;
    std::cout << "-------------------------" << std::endl; 
    if (input != 0 &&  input > line_lenght + 1) {
        y += line_lenght + 1; 
        input -= line_lenght + 1 ;
    } else {
        y += input;
    }
    std::cout << "X is " << x << std::endl; 
    std::cout << "Y is " << y << std::endl;
    std::cout << "Input is " << input << std::endl;
    std::cout << "-------------------------" << std::endl; 
    if (input != 0 && input > line_lenght + 2 ) {
        x += line_lenght + 2; 
        input -= line_lenght + 2;
    } else {
        x += input; 
    }
    std::cout << "X is " << x << std::endl; 
    std::cout << "Y is " << y << std::endl;
    std::cout << "Input is " << input << std::endl;
    std::cout << "Manhattan distance is " << abs(x) + abs(y) << std::endl; 

    return 0; 
}