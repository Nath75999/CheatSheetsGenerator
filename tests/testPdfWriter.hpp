#include "../src/pdf/PdfWriter.hpp"
#include <iostream>

bool testPdfWriter(){
    PdfWriter p2;
    p2.writeText("This a test\non mulltiple lines.");

    return true;
}
