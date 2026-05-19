#pragma once

#include <mupdf/pdf.h>

#include <string_view>
#include <string>
#include <vector>

#include "Pdf.hpp"

class PdfWriter: public Pdf{
    public:
        PdfWriter(std::string_view name = "result");

        ~PdfWriter();


        //void writeTitle(std::string_view title);

        void writeText(std::string_view text);

        
        void saveFile();
    
    private:
        std::string name;
        pdf_document* pdf;
        fz_rect mediabox;
};
