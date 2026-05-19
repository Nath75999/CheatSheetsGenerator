#pragma once

#include <mupdf/pdf.h>

#include <iostream>

#include <string_view>
#include <string>
#include <vector>

class Pdf{
    public:
        Pdf(std::string_view path = "");

        ~Pdf();


        void loadFile(std::string_view path);

        fz_page* loadPage(int id);

    protected:
        fz_context* ctx;
        fz_document* doc;
        std::vector<fz_page*> pages;

};
