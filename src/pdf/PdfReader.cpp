#include "PdfReader.hpp"

PdfReader::PdfReader(std::string_view path) : Pdf(path), stext_page(nullptr) {}

PdfReader::~PdfReader() {if (stext_page) fz_drop_stext_page(ctx, stext_page);}


std::string PdfReader::readPage(int id){
    std::string result = "";
    fz_stext_options opts = {};
    opts.flags = FZ_STEXT_PRESERVE_WHITESPACE;

    if (stext_page) fz_drop_stext_page(ctx, stext_page);

    fz_try(ctx) stext_page = fz_new_stext_page_from_page(ctx, pages[id], &opts);
    fz_catch(ctx) return result;
    
    for (fz_stext_block* block = stext_page->first_block; block != nullptr; block = block->next){ //blocks
        if (block->type == FZ_STEXT_BLOCK_TEXT){ //text block
            for (fz_stext_line* line = block->u.t.first_line; line != nullptr; line = line->next){ //lines of the block
                for (fz_stext_char* ch = line->first_char; ch != nullptr; ch = ch->next){ //char of the line
                    char buff[5]; //need 5 bytes (4 bytes for char and \0), but can use 6 bytes or more if preferred
                    int len = fz_runetochar(buff, ch->c); //convert to UTF 8 (1 to 4 bytes)
                    buff[len] = '\0';
                    result += buff;
                }

                result += '\n';
            }

            result += '\n';
        }
    }

    return result;
}

std::string PdfReader::readFile(){
    std::string result = "";
    int id = 0;

    for (auto& page : pages){
        result += readPage(id) + '\n';
        ++id;
    }

    return result;
}
