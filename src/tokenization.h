#pragma once
#include<string>
#include<vector>
using namespace std;
enum class TokenType{
    exit,
    int_lit,
    semi
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};
class Tokenizer
{
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }
    inline vector<Token> tokenize() {
        vector<Token> tokens;
        string buf;
        while (peak().has_value()) {
            if (isalpha(peak().value())) {
                buf.push_back(consume());
                while (peak().has_value() && isalnum(peak().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                } else {
                    cerr << "YOU MESSED UP" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (isdigit(peak().value())) {
                buf.push_back(consume());
                while (peak().has_value() && isdigit(peak().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            } else if (peak().value() == ';') {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            } else if (isspace(peak().value())) {
                consume();
                continue;
            } else {
                cerr << "YOU MESSED UP" << endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index=0;
        return tokens;
    }
private:
   [[nodiscard]] optional<char> peak(int ahead = 1) const {
        if(m_index + ahead>m_src.length())
        {
            return {};
        }
        else
        {
            return m_src.at(m_index);
        }
    }
    char consume()
    {
        return m_src.at(m_index++);
    }
    const string m_src;
    size_t m_index=0;
};