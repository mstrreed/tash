#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include"./tokenization.h"
#include "./parser.h"
using namespace std;




string tokens_to_asm(const vector<Token>& tokens){
    stringstream output;
    output<<"global _start\n_start:\n";
    for(int i=0;i<tokens.size();i++) {
        const Token &token = tokens.at(i);
        if (token.type == TokenType::exit) {
            if (i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::int_lit) {
                if (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semi) {
                    output << "  mov rax, 60\n";
                    output << "  mov rdi, " << tokens.at(i + 1).value.value() << "\n";
                    output << "  syscall";
                }
            }
        }
    }
return output.str();

}
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        cerr<<"Incorrect Usage. Correct usage is ..... "<<endl;
        cerr<< "tash <input.ts>"<<endl;
        return EXIT_FAILURE;
    }
    string contents;
    {
        stringstream contents_stream;
        fstream input(argv[1],ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();

    }
    Tokenizer tokenizer(move(contents));
        vector<Token> tokens= tokenizer.tokenize();
    //cout<<tokens_to_asm(tokens)<<endl;

    {
        fstream file("out.asm",ios::out);
        file<<tokens_to_asm(tokens);
    }
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    return EXIT_SUCCESS;
//cout<<"hello"<<endl;
return 0;
}