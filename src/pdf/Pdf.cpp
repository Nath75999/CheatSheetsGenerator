#include "Pdf.hpp"

Pdf::Pdf(std::string_view path) : ctx(fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED)){
    fz_register_document_handlers(ctx);

    if (!path.empty()) loadFile(path);
    else doc = nullptr;
}

Pdf::~Pdf(){
    for (auto& page : pages) fz_drop_page(ctx, page);

    if (doc) fz_drop_document(ctx, doc);

    fz_drop_context(ctx);
}


void Pdf::loadFile(std::string_view path){
    fz_try(ctx){
        doc = fz_open_document(ctx, ("data/input_pdfs/" + std::string(path)).c_str());
        
        int nbPages = fz_count_pages(ctx, doc);
        for (int i = 0; i < nbPages; ++i) pages.push_back(loadPage(i));
    }
    fz_catch(ctx) std::cerr << "ERROR: Pdf recieved a wrong path when loading a pdf, got: " << path << std::endl;
}


fz_page* Pdf::loadPage(int id) {return fz_load_page(ctx, doc, id);}
