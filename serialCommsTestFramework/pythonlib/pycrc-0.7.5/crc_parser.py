# -*- coding: Latin-1 -*-

#  pycrc -- parametrisable CRC calculation utility and C source code generator
#
#  Copyright (c) 2006-2010  Thomas Pircher  <tehpeh@gmx.net>
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.


"""
Macro Language parser for pycrc.
use as follows:

    from crc_opt import Options
    from crc_parser import MacroParser

    opt = Options("0.6")
    opt.parse(sys.argv)
    mp = MacroParser(opt)
    if mp.parse(out):
        print(mp.out_str)


This file is part of pycrc.
"""

from crc_symtable import SymbolTable
from crc_lexer import LangLexer, ExpLexer
import sys


# Class ParseError
###############################################################################
class ParseError(Exception):
    """
    The exception class for the parser
    """

    # Class constructor
    ###############################################################################
    def __init__(self, reason):
        self.reason = reason

    # function __str__
    ###############################################################################
    def __str__(self):
        return self.reason


# Class MacroParser
###############################################################################
class MacroParser(object):
    """
    The macro language parser and code generator class
    """
    opt = None
    sym = None
    lex = LangLexer()
    explex = ExpLexer()

    mPrintMask      = 1
    mDoPrint        = 2
    mEvalElse       = 4


    # Class constructor
    ###############################################################################
    def __init__(self, opt):
        self.opt = opt
        self.sym = SymbolTable(opt)

    # function parse
    #
    # the used grammar (more or less correctly) in Wirth Syntax Notation:
    #
    # DATA = { LITERAL | CONTROL } .
    # CONTROL = IF | "{%" LITERAL "%}" .
    # IF = "{%" "if" EXPRESSION "%}" "{:" { DATA } ":}"
    #       { "{%" "elif" EXPRESSION "%}" "{:" { DATA } ":}" }
    #       [ "{%" "else" "%}" "{:" { DATA } ":}" ]
    #       .
    # STRING = """" LITERAL """" .
    # ID = "{%" LITERAL "%}" .
    # LITERAL = letter { letter } .
    #
    # EXPRESSION = TERM { "or" TERM } .
    # TERM = FACTOR { "and" FACTOR } .
    # FACTOR = ( EXPRESSION ) | TERMINAL OP TERMINAL .
    # TERMINAL = ID | STRING | LITERAL .
    # OP = "==" | ">" | "<" | "<=" | "=>" | "!=" .
    #
    ###############################################################################
    def parse(self, str):
        """
        parse a string
        """
        self.lex.set_str(str)
        self.out_str = ""
        self.if_stack = [ self.mPrintMask | self.mDoPrint ]
        return self.__parse_data()


    # function __parse_data
    ###############################################################################
    def __parse_data(self):
        """
        parse data
        """
        tok = self.lex.peek()
        while tok != self.lex.tok_EOF:
            if tok == self.lex.tok_text:
                if (self.if_stack[0] & self.mDoPrint) == self.mDoPrint:
                    self.out_str += self.lex.text
                self.lex.advance(skip_nl = False)
            elif tok == self.lex.tok_control:
                if not self.__parse_control(self.lex.text):
                    return False
            elif tok == self.lex.tok_block_end:
                return True
            else:
                sys.stderr.write("%s: error: wrong token %s\n" % (sys.argv[0], self.lex.text))
                return False
            tok = self.lex.peek()
        return True


    # function __parse_control
    ###############################################################################
    def __parse_control(self, str):
        """
        parse a control structure
        """
        tok = self.lex.peek()
        if tok == self.lex.tok_control:
            if self.lex.text.startswith("if "):
                if not self.__parse_if(self.lex.text) or \
                    not self.__parse_block_start() or \
                    not self.__parse_data() or \
                    not self.__parse_block_end():
                    return False
                tok = self.lex.peek()
                while self.lex.text.startswith("elif "):
                    if not self.__parse_elif(self.lex.text) or \
                        not self.__parse_block_start() or \
                        not self.__parse_data() or \
                        not self.__parse_block_end():
                        return False
                    tok = self.lex.peek()
                if self.lex.text == "else":
                    if not self.__parse_else(self.lex.text) or \
                        not self.__parse_block_start() or \
                        not self.__parse_data() or \
                        not self.__parse_block_end():
                        return False
                self.if_stack.pop(0)
                return True
            elif self.lex.text == "else" or self.lex.text.startswith("elif "):
                sys.stderr.write("%s: error: unmatched %s clause\n" % (sys.argv[0], self.lex.text[:4]))
                return False
            else:
                if not self.__parse_literal(self.lex.text):
                    return False
                return True
        sys.stderr.write("%s: %error: unknown token in control\n" % sys.argv[0])
        return False


    # function __parse_if
    ###############################################################################
    def __parse_if(self, str):
        """
        parse a if operation
        """
        exp = str[3:].strip()
        try:
            condition = self.__parse_expression(exp)
        except ParseError:
            sys.stderr.write("%s: %error: parsing expression %s failed\n" % (sys.argv[0], str))
            return False

        stack_state = self.if_stack[0]
        if (stack_state & self.mDoPrint) == self.mDoPrint:
            if condition:
                stack_state = self.mPrintMask | self.mDoPrint
            else:
                stack_state = self.mPrintMask | self.mEvalElse
        else:
            stack_state = 0
        self.if_stack.insert(0, stack_state)
        self.lex.advance(skip_nl = True)
        return True


    # function __parse_elif
    ###############################################################################
    def __parse_elif(self, str):
        """
        parse a elif operation
        """
        stack_state = self.if_stack[0]
        if (stack_state & (self.mPrintMask | self.mEvalElse)) == (self.mPrintMask | self.mEvalElse):
            exp = str[5:].strip()
            try:
                condition = self.__parse_expression(exp)
            except ParseError:
                sys.stderr.write("%s: error: parsing of expression %s failed\n" % (sys.argv[0], str))
                return False

            if condition:
                stack_state = self.mPrintMask | self.mDoPrint
            else:
                stack_state = self.mPrintMask | self.mEvalElse
        else:
            stack_state = 0

        self.if_stack[0] = stack_state
        self.lex.advance(skip_nl = True)
        return True


    # function __parse_else
    ###############################################################################
    def __parse_else(self, str):
        """
        parse a if operation
        """
        stack_state = self.if_stack[0]
        if (stack_state & (self.mPrintMask | self.mEvalElse)) == (self.mPrintMask | self.mEvalElse):
            stack_state = self.mPrintMask | self.mDoPrint
        else:
            stack_state = 0
        self.if_stack[0] = stack_state
        self.lex.advance(skip_nl = True)
        return True


    # function __parse_block_start
    ###############################################################################
    def __parse_block_start(self):
        """
        parse a begin of a control block
        """
        tok = self.lex.peek()
        if tok != self.lex.tok_block_start:
            sys.stderr.write("%s: error: begin block expected, at %s\n" % (sys.argv[0], self.lex.text))
            return False
        self.lex.advance(skip_nl = True)
        return True


    # function __parse_block_end
    ###############################################################################
    def __parse_block_end(self):
        """
        parse a end of a control block
        """
        tok = self.lex.peek()
        if tok != self.lex.tok_block_end:
            sys.stderr.write("%s: error: end block expected, at %s\n" % (sys.argv[0], self.lex.text))
            return False
        self.lex.advance(skip_nl = True)
        return True


    # function __parse_literal
    ###############################################################################
    def __parse_literal(self, str):
        """
        parse a literal
        """
        try:
            data = self.sym.getTerminal(str)
        except LookupError:
            sys.stderr.write("%s: error: unknown terminal %s\n" % (sys.argv[0], self.lex.text))
            return False
        self.lex.advance(skip_nl = False)
        if (self.if_stack[0] & self.mDoPrint) == self.mDoPrint:
            self.lex.prepend(data)
        return True


    # function __parse_expression
    ###############################################################################
    def __parse_expression(self, str):
        """
        parse an expression
        """
        self.explex.set_str(str)
        try:
            ret = self.__parse_exp_exp()
        except ParseError:
            raise ParseError("Exp parsing failed")
        if self.explex.peek() != self.explex.tok_EOF:
            raise ParseError("extra characters after expression");
        return ret


    # function __parse_exp_exp
    ###############################################################################
    def __parse_exp_exp(self):
        """
        parse an expression
        """
        ret = False

        while True:
            ret = self.__parse_exp_term() or ret

            tok = self.explex.peek()
            if tok == self.explex.tok_EOF:
                return ret
            if tok != self.explex.tok_or:
                print("expecting 'or' and not '%s'" % self.explex.text)
                raise ParseError("Unexpected token")
            self.explex.advance(skip_nl = False)

        return False


    # function __parse_exp_term
    ###############################################################################
    def __parse_exp_term(self):
        """
        parse a term
        """
        ret = True

        while True:
            ret = self.__parse_exp_factor() and ret
            tok = self.explex.peek()

            if tok != self.explex.tok_and:
                return ret
            self.explex.advance(skip_nl = False)

        return False


    # function __parse_exp_factor
    ###############################################################################
    def __parse_exp_factor(self):
        """
        parse a term
        """
        ret = True

        tok = self.explex.peek()

        if tok == self.explex.tok_par_open:
            self.explex.advance(skip_nl = False)
            ret = self.__parse_exp_exp()
            tok = self.explex.peek()
            if tok != self.explex.tok_par_close:
                print("missing ')' before '%s'" % self.explex.text)
                raise ParseError("missing ')' before '%s'" % self.explex.text)
            self.explex.advance(skip_nl = False)
            self.explex.peek()
            return ret

        val1_str = self.explex.text
        val1 = self.__parse_exp_terminal()
        tok = self.explex.peek()
        if tok != self.explex.tok_op:
            print("operator expected and not '%s' before '%s'" % (self.explex.text, self.explex.str))
            raise ParseError("operator expected and not '%s'" % self.explex.text)
        op_text = self.explex.text
        self.explex.advance(skip_nl = False)
        self.explex.peek()
        val2_str = self.explex.text
        val2 = self.__parse_exp_terminal()
        if val1 == None or val2 == None:
            if op_text == "==":
                if (val1 == None and val2 == "Undefined") or (val1 == "Undefined" and val2 == None):
                    return True
            elif op_text == "!=":
                if (val1 == None and val2 == "Undefined") or (val1 == "Undefined" and val2 == None):
                    return False
            if val1 == None:
                text = val1_str
            else:
                text = val2_str
            print("undefined parameter '%s'" % text)
            raise ParseError("undefined parameter")

        val1_num = val2_num = None
        if val1 != None:
            if self.explex.is_int(val1):
                val1_num = int(val1)
            if self.explex.is_hex(val1):
                val1_num = int(val1, 16)
        if val2 != None:
            if self.explex.is_int(val2):
                val2_num = int(val2)
            if self.explex.is_hex(val2):
                val2_num = int(val2, 16)

        if val1_num != None and val2_num != None:
            val1 = val1_num
            val2 = val2_num

        if op_text == "<":
            return val1 < val2
        if op_text == "<=":
            return val1 <= val2
        if op_text == "==":
            return val1 == val2
        if op_text == "!=":
            return val1 != val2
        if op_text == ">=":
            return val1 >= val2
        if op_text == ">":
            return val1 > val2
        else:
            print("unknown operator '%s'" % op_text)
            raise ParseError("unknown operator")


    # function __parse_exp_terminal
    ###############################################################################
    def __parse_exp_terminal(self):
        """
        parse a terminal
        """
        tok = self.explex.peek()
        if tok == self.explex.tok_id:
            if self.explex.text == "Undefined":
                ret = "Undefined"
            else:
                try:
                    ret = self.sym.getTerminal(self.explex.text)
                except LookupError:
                    ret = None
        elif tok == self.explex.tok_str:
            ret = self.explex.text
        else:
            print("unexpected terminal '%s' before '%s'" % (self.explex.text, self.explex.str))
            raise ParseError("unexpected terminal '%s'" % self.explex.text)
        self.explex.advance(skip_nl = False)
        return ret
