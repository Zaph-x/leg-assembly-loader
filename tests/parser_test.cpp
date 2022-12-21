#include <filesystem>
#include "doctest.h"
#include "parser.hpp"

const std::string test_file = R"(	.arch armv8-a
	.file	"madd.c"
	.text
	.align	2
	.global	multi_add
	.type	multi_add, %function
multi_add:
.LFB0:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, 12]
	str	w1, [sp, 8]
	str	w2, [sp, 4]
	ldr	w1, [sp, 8]
	ldr	w0, [sp, 4]
	mul	w1, w1, w0
	ldr	w0, [sp, 12]
	add	w0, w1, w0
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	multi_add, .-multi_add
	.align	2
	.global	main
	.type	main, %function
main:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	mov	x29, sp
	mov	w2, 3
	mov	w1, 2
	mov	w0, 1
	bl	multi_add
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
)";

TEST_CASE("Parser can parse small programs") {
    SUBCASE("Empty program") {
        std::string path = "./test_files/empty_program.s";
        ARM::Parser::Parser parser;
        parser.set_up(path);

        parser.assign_program();
        CHECK(parser.get_program()->get_architecture() == "");
        CHECK(parser.get_program()->get_file_name() == "");
    }

    SUBCASE("Can parse architecture") {
        std::string line(test_file);
        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        ARM::Parser::Parser parser;
        parser.set_up(lexer);

        parser.assign_program();

        CHECK(parser.get_program()->get_architecture() == "armv8-a");
        std::cout << parser.get_program()->get_architecture() << std::endl;
    }

    SUBCASE("Can parse file name") {
        std::string line(test_file);

        std::stringstream ss(line);
        ARM::Lexer::Lexer lexer(ss);
        ARM::Parser::Parser parser;
        parser.set_up(lexer);

        parser.assign_program();

        CHECK(parser.get_program()->get_file_name() == "\"madd.c\"");
    }



    SUBCASE("Par"){
        std::fstream file;
        const std::string path = "./test_files/function.s";

        std::filesystem::path p(path);
        CHECK(std::filesystem::exists(p));

        file.open(path);
        std::string ir((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        std::stringstream ss(ir);

        ARM::Lexer::Lexer lexer(ss);
        lexer.run();
        ARM::Parser::Parser parser;
        parser.set_up(lexer);

        parser.assign_program();
        CHECK(parser.get_program()->get_file_name() == "\"function.c\"");
    }
}