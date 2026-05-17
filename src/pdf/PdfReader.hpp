#pragma once

#include "mupdf/fitz.h"

#include <string_view>
#include <string>
#include <vector>

#include "Pdf.hpp"

class PdfReader: public Pdf{
    public:
        PdfReader(std::string_view path = "");


        std::string readPage(int id);

        std::string readFile();
};
