#pragma once

using namespace std;

    struct NodeExpr {
    Token int_lit;
    };
    struct NodeExit{

    };



class Parser{
public:
    inline explicit Parser(vector<Token> tokens)
        :m_token(move(tokens))
    {
    }

private:
    [[nodiscard]] optional<Token> peak(int ahead = 1) const {
        if(m_index + ahead>m_tokens.size())
        {
            return {};
        }
        else
        {
            return m_tokens.at(m_index);
        }
    }
    inline Token consume()
    {
        return m_tokens.at(m_index++);
    }
    const vector<Token> m_tokens;
    size_t m_index=0;
};