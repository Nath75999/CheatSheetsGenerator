#include "PdfWriter.hpp"

PdfWriter::PdfWriter(std::string_view name) : Pdf(), name(name), pdf(pdf_create_document(ctx)), 
                                              mediabox{0, 0, 595, 842} 
                                              {}

PdfWriter::~PdfWriter(){
    saveFile();
    pdf_drop_document(ctx, pdf);
}


void PdfWriter::writeText(std::string_view text) {
    std::string content = "BT /F1 12 Tf 100 700 Td (" + std::string(text) + ") Tj ET"; //encodage pour pdf
    
    fz_buffer* buffer = fz_new_buffer(ctx, content.size());
    fz_append_data(ctx, buffer, content.data(), content.size());

    pdf_obj* res = pdf_new_dict(ctx, pdf, 1);
    pdf_obj* fonts = pdf_new_dict(ctx, pdf, 1);
    
    pdf_obj* font = pdf_new_dict(ctx, pdf, 4);
    pdf_dict_put_name(ctx, font, PDF_NAME(Type),    "Font");
    pdf_dict_put_name(ctx, font, PDF_NAME(Subtype), "Type1");
    pdf_dict_put_name(ctx, font, PDF_NAME(BaseFont),"Helvetica");
    
    pdf_obj* f1_key = pdf_new_name(ctx, "F1");
    pdf_dict_put(ctx, fonts, f1_key, font);
    pdf_drop_obj(ctx, f1_key);
    pdf_dict_put(ctx, res,   PDF_NAME(Font), fonts);

    pdf_obj* page = pdf_add_page(ctx, pdf, mediabox, 0, res, buffer);
    pdf_insert_page(ctx, pdf, -1, page);

    pdf_drop_obj(ctx, page);
    pdf_drop_obj(ctx, font);
    pdf_drop_obj(ctx, fonts);
    pdf_drop_obj(ctx, res);
    fz_drop_buffer(ctx, buffer);
}


void PdfWriter::saveFile(){
    pdf_write_options opts = {0}; 
    opts.do_compress = 1; 
    opts.do_compress_images = 1; 
    opts.do_garbage = 2; //delete solo objects

    fz_try(ctx) pdf_save_document(ctx, pdf, ("data/output_fiches/" + name + ".pdf").c_str(), &opts);
    fz_catch(ctx) std::cerr << "MuPDF error: " << fz_caught_message(ctx) << std::endl;
}
