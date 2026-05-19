#include "../src/pdf/PdfReader.hpp"
#include <iostream>

bool testPdfReader(){
    // PdfReader p1("test.pdf");
    // std::cout << "File test.pdf:\n" << p1.readFile() <<std::endl;

    PdfReader p2;
    p2.loadFile("smartPointersCpp.pdf");
    std::cout << "File smartPointersCpp.pdf:\n" << p2.readFile() <<std::endl;

    // PdfReader p3;
    // p3.loadFile("projet_recettes.pdf");
    // std::cout << "File projet_recettes.pdf:\n" << p3.readFile() <<std::endl;

    // PdfReader p4; //warning, big file
    // p4.loadFile("microbio3.pdf");
    // std::cout << "File microbio3.pdf:\n" << p4.readFile() <<std::endl;

    return true;
}
