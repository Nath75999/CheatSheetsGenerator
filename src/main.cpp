#include "../tests/testPdfReader.hpp"
#include "../tests/testPdfWriter.hpp"

int main(int argc, char* argv[]){
    bool test = true;
    // test = testPdfReader();
    test = testPdfWriter();
    
    return test;

    return 0;
}
