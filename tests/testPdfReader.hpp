#include "../src/pdf/PdfReader.hpp"

bool testPdfReader(){
    PdfReader p1("test.pdf");

    PdfReader p2;
    p2.loadFile("test.pdf");
    return true;
}
