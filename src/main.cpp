#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>
#include "./parser.h"
#include"./tokenization.h"
#include "generation.h"

using namespace std;






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
    Parser parser(move(tokens));
    optional<NodeExit> tree=parser.parse();
    if(!tree.has_value())
    {
        cerr<<"No exit statement found"<<endl;
        exit(EXIT_FAILURE);
    }
    Generator generator(tree.value());
    {
        fstream file("out.asm",ios::out);
        file<<generator.generate();
    }
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    return EXIT_SUCCESS;
//cout<<"hello"<<endl;
return 0;
}