import os,sys
__DIR__ = os.path.abspath(os.path.dirname(__file__))

from ply import lex, yacc
DEBUG = 1

from idlTypes import Include,Function,Argument

#lex
states = (
  ('ccode','exclusive'),
  ('comment','exclusive'),
)

reserved = {
    'const': 'CONST',
    'void' : "VOID"
}

tokens = [
    'COMMENT',          # //
    'COMMENT_BEGIN',    # /*
    'COMMENT_END',      # */
    'INCLUDE',          # #include
    'INCLUDEFILE',      # <xxx.h> or "xxx.h"
    'ID',               # anything?
    'TAG',              # [tag]
] + list(reserved.values())

#signal char tokens
literals = '(),*;'

t_ccode_INCLUDE   = r'\#[\t ]*include'

t_ccode_INCLUDEFILE = r'["<][\w\./]*[">]'

t_ANY_ignore_COMMENT = r'//.*'

def t_ccode_ignore_COMMENT_BEGIN(t):
    r'/\*'
    t.lexer.begin('comment')

def t_comment_ignore_COMMENT_BEGIN(t):
    r'/\*'
    raise SyntaxError("'/*' in comment on %d" % (t.lexer.lineno))

def t_comment_ignore_COMMENT_END(t):
    r'\*/'
    t.lexer.begin('ccode')

def t_ccode_ignore_COMMENT_END(t):
    r'\*/'
    raise SyntaxError("'*/' without '/*' on %d" % (t.lexer.lineno))

def t_ccode_ID(t):
    r'[A-Za-z_][A-Za-z0-9_]*'
    t.type = reserved.get(t.value, 'ID')
    return t

def t_ccode_TAG(t):
    r'{[a-z0-9\*]*}'
    t.value = t.value
    return t

# Define a rule so we can track line numbers
def t_ANY_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# A string containing ignored characters (spaces and tabs)
t_ANY_ignore  = ' \t'

# Error handling rule
def t_ccode_error(t):
    raise SyntaxError("Illegal character %r on line %d %d" % (t.value[0], t.lexer.lineno, t.lexer.lexpos ))
    #print "Illegal character '%s'" % t.value[0]
    #t.lexer.skip(1)

def t_comment_error(t):
    t.lexer.skip(1)

def t_error(t):
    return t_ccode_error(t)

lexer = lex.lex(debug=DEBUG)
lexer.begin('ccode')

#yacc
def logyacc(func,p):
    if DEBUG:
        if len(p) == 2:
            print("%s:%s" % (func,str(p[1])))
        else:
            print("%s:%s + %s" % (func,str(p[1]),str(p[2])))

def p_empty(p):
    "empty :"

def p_include(p):
    """
    include : INCLUDE INCLUDEFILE
    """
    logyacc("p_include",p)
    p[0] = Include(p[1] + " " + p[2])

def p_function_ret(p):
    """
    function_ret : CONST 
                 | function_ret CONST
                 | VOID
                 | function_ret VOID
                 | ID
                 | function_ret ID
                 | TAG
                 | function_ret TAG
                 | function_ret '*'
    """
    logyacc("p_function_ret",p)
    if len(p) == 2:
        p[0] = Argument()
        newarg = p[1]
    else:
        p[0] = p[1]
        newarg = p[2]

    p[0].smartAdd(newarg)

def p_function_name(p):
    """
    function_name : function_ret ID '('
    """
    logyacc("p_function_name",p)
    p[0] = Function()
    p[0].setReturn(p[1])
    p[0].setName(p[2])

def p_function_arg(p):
    """
    function_arg : function_name CONST
                 | function_arg CONST
                 | function_name VOID
                 | function_arg VOID
                 | function_name ID
                 | function_arg ID
                 | function_name TAG
                 | function_arg TAG
                 | function_arg '*'
                 | function_name ','
                 | function_arg ','
    """
    logyacc("function_arg1",p)
    p[0] = p[1]
    arg = p[0].getLastArgument()
    if p[2] != "void":
        if arg == None or p[2] == ',':
            arg = Argument()
            p[0].addArgument(arg)
        if p[2] != ',':
             arg.smartAdd(p[2])
    logyacc("function_arg2",p)

def p_function(p):
    """
    function : function_name ')' ';'
             | function_arg  ')' ';'
    """
    logyacc("p_function",p)
    p[0] = p[1]

def p_spec(p):
    """
    spec : spec include
         | spec function
         | empty
    """
    if len(p) == 2:
        p[0] = []
    else:
        p[0] = p[1] + [p[2]]

def p_error(p):
    if p:
        print("Syntax error at '%s'" % p)
    else:
        print("Syntax error at EOF")

start = 'spec'
parser = yacc.yacc(outputdir=__DIR__, debug=DEBUG, write_tables=False)

def parse(f):
    idl = f.read()

    if DEBUG:
        lexer.input(idl)
        for tok in lexer:
            print tok
        print("------------\n\n")

    ret = parser.parse(idl)
    parser.restart()
    if DEBUG:
      print("------------\n\n")
      for r in ret:
        print(r)

    return ret


