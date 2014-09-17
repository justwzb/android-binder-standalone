import os,sys
__DIR__ = os.path.abspath(os.path.dirname(__file__))

from ply import lex, yacc
DEBUG = 0

import idlTypes

#lex
states = (
  ('ccode','exclusive'),
  ('comment','exclusive'),
)

tokens = (
    'COMMENT',          # //
    'COMMENT_BEGIN',    # /*
    'COMMENT_END',      # */
    'INCLUDE',          # #include
    'INCLUDEFILE',      # <xxx.h> or "xxx.h"
    'ID',               # anything?
    'TAG',              # [tag]
)

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
    #t.type = reserved.get(t.value, 'ID')
    return t

def t_ccode_TAG(t):
    r'\[[a-z0-9\*]*\]'
    t.value = t.value[1:-1]
    return t

# Define a rule so we can track line numbers
def t_ANY_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# A string containing ignored characters (spaces and tabs)
t_ANY_ignore  = ' \t'

# Error handling rule
def t_ccode_error(t):
    raise SyntaxError("Illegal character %r on %d" % (t.value[0], t.lexer.lineno))
    #print "Illegal character '%s'" % t.value[0]
    #t.lexer.skip(1)

def t_comment_error(t):
    t.lexer.skip(1)

def t_error(t):
    return t_ccode_error(t)

lexer = lex.lex(debug=DEBUG)
lexer.begin('ccode')

#yacc
def p_empty(p):
    "empty :"

def p_include(p):
    """
    Include : INCLUDE INCLUDEFILE
    """
    p[0] = idlTypes.Include(p[1] + " " + p[2])
    print("INCLUDE found " + str(p[0]))

def p_spec(p):
    """
    spec : spec Include
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


filename  = sys.argv[1]
idl = open(filename).read()

if 0:
    lexer.input(idl)
    for tok in lexer:
        print tok
    print("------------")

result = parser.parse(idl)
print(result)
