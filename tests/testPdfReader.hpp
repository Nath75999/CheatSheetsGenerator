#include "../src/pdf/PdfReader.hpp"
#include <iostream>

bool testPdfReader(){
    //PdfReader p1("test.pdf");
    //std::cout << "File test.pdf:\n" << p1.readFile() <<std::endl;

    PdfReader p2;
    p2.loadFile("smartPointersCpp.pdf");
    std::cout << "File smartPointersCpp.pdf:\n" << p2.readFile() <<std::endl;

    return true;
}
