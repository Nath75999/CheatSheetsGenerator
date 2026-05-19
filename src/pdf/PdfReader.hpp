#pragma once

#include <mupdf/pdf.h>

#include <string_view>
#include <string>
#include <vector>

#include "Pdf.hpp"

class PdfReader: public Pdf{
    public:
        PdfReader(std::string_view path = "");

        ~PdfReader();


        std::string readPage(int id);

        std::string readFile();
    
    private:
        fz_stext_page* stext_page;
};
