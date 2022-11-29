#include "lexer.hpp"
#include <iostream>
#include "token.hpp"

// build a lexer for an input file using
namespace ARM
{
    namespace Lexer
    {
        Lexer::Lexer(std::istream &input) : in(&input)
        {
            line = 1;
            position = 0;
            advance();
        }
        void Lexer::advance() { current_token = next_token(); }
        Tokens::Token Lexer::next_token()
        {
            int c;
            while ((c = in->get()) != EOF)
            {
                if (c == '\n')
                {
                    line++;
                    position = 0;
                }
                else if (c == ' ' || c == '\t')
                {
                    position++;
                }
                else if (c == ';')
                {
                    while ((c = in->get()) != EOF && c != '\n')
                        ;
                    if (c == '\n')
                    {
                        line++;
                        position = 0;
                    }
                }
                else if (c == ':')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::COLON);
                }
                else if (c == ',')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::COMMA);
                }
                else if (c == '[')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::L_BRACKET);
                }
                else if (c == ']')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::R_BRACKET);
                }
                else if (c == 'w0')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W0);
                }
                else if (c == 'w1')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W1);
                }
                else if (c == 'w2')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W2);
                }
                else if (c == 'w3')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W3);
                }
                else if (c == 'w4')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W4);
                }
                else if (c == 'w5')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W5);
                }
                else if (c == 'w6')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W6);
                }
                else if (c == 'w7')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W7);
                }
                else if (c == 'w8')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W8);
                }
                else if (c == 'w9')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W9);
                }
                else if (c == 'w10')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W10);
                }
                else if (c == 'w11')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W11);
                }
                else if (c == 'w12')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W12);
                }
                else if (c == 'w13')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W13);
                }
                else if (c == 'w14')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W14);
                }
                else if (c == 'w15')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W15);
                }
                else if (c == 'w16')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W16);
                }
                else if (c == 'w17')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W17);
                }
                else if (c == 'w18')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W18);
                }
                else if (c == 'w19')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W19);
                }
                else if (c == 'w20')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W20);
                }
                else if (c == 'w21')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W21);
                }
                else if (c == 'w22')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W22);
                }
                else if (c == 'w23')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W23);
                }
                else if (c == 'w24')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W24);
                }
                else if (c == 'w25')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W25);
                }
                else if (c == 'w26')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W26);
                }
                else if (c == 'w27')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W27);
                }
                else if (c == 'w28')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W28);
                }
                else if (c == 'w29')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W29);
                }
                else if (c == 'w30')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::W30);
                }
                else if (c == 'wzr')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::WZR);
                }
                else if (c == 'wsp')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::WSP);
                }
                else if (c == 'x0')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X0);
                }
                else if (c == 'x1')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X1);
                }
                else if (c == 'x2')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X2);
                }
                else if (c == 'x3')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X3);
                }
                else if (c == 'x4')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X4);
                }
                else if (c == 'x5')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X5);
                }
                else if (c == 'x6')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X6);
                }
                else if (c == 'x7')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X7);
                }
                else if (c == 'x8')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X8);
                }
                else if (c == 'x9')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X9);
                }
                else if (c == 'x10')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X10);
                }
                else if (c == 'x11')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X11);
                }
                else if (c == 'x12')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X12);
                }
                else if (c == 'x13')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X13);
                }
                else if (c == 'x14')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X14);
                }
                else if (c == 'x15')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X15);
                }
                else if (c == 'x16')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X16);
                }
                else if (c == 'x17')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X17);
                }
                else if (c == 'x18')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X18);
                }
                else if (c == 'x19')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X19);
                }
                else if (c == 'x20')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X20);
                }
                else if (c == 'x21')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X21);
                }
                else if (c == 'x22')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X22);
                }
                else if (c == 'x23')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X23);
                }
                else if (c == 'x24')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X24);
                }
                else if (c == 'x25')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X25);
                }
                else if (c == 'x26')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X26);
                }
                else if (c == 'x27')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X27);
                }
                else if (c == 'x28')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X28);
                }
                else if (c == 'x29')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X29);
                }
                else if (c == 'x30')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::X30);
                }
                else if (c == 'xzr')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::XZR);
                }
                else if (c == 'sp')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::SP);
                }
                else if (c == 'pc')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::PC);
                }
                else if (c == 'lr')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::LR);
                }
                else if (c == 'spsr')
                {
                    position++;
                    return Tokens::Token(Tokens::Token::SPSR);
                }
                    
            }

        }
    }
}

