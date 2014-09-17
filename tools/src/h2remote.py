from __future__ import print_function
from pycparser import c_parser, c_ast, parse_file
import re
import sys,os
import tempfile

class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self,filename):
        self._filename = filename
        self._funcList = []

    def getFuncList(self):
        return self._funcList;

    def visit_FuncDef(self, node):
        print('%s at %s' % (node.decl.name, node.decl.coord))

    def visit_Decl(self,node,no_type=False):
        #print("visit_Decl" + str(node.type))
        if type(node.type) != c_ast.FuncDecl:
            return False

        coord = str(node.coord)
        #print(coord)
        #print(self._filename)
        if not self._filename or not coord or coord.find(self._filename) < 0:
            return False

        name = node.name if node.name else "unknown"
        #print(name)

        FuncDecl = node.type

        #parse paramters
        if FuncDecl.args:
            paramters = [(self._expand_decl(paramter),paramter.name) for paramter in FuncDecl.args.params]
        else:
            paramters = []
        #int func(void)
        if paramters == [('void', None)]:
            paramters = []
        #print(paramters)

        RetDecl = FuncDecl.type
        ret = self._expand_decl(RetDecl)
        #print(ret)

        func = {}
        func["name"] = name
        func["ret"] = ret
        func["paramters"] = paramters
        self._funcList.append(func)

    def _expand_decl(self,decl):
        """ Converts the declaration into a nested list.
        """
        typ = type(decl)
        #print(typ)

        #TODO: only debuged for some typ
        if typ == c_ast.TypeDecl:
            quals = ' '.join(decl.quals) + ' ' if decl.quals else ''
            return quals + self._expand_decl(decl.type)
        elif typ == c_ast.Typename or typ == c_ast.Decl:
            return self._expand_decl(decl.type)
        elif typ == c_ast.IdentifierType:
            #print("@@@"+ str(decl.names))
            return ' '.join(decl.names)
        elif typ == c_ast.PtrDecl:
            quals = ' '.join(decl.quals) + ' ' if decl.quals else ''
            return quals + self._expand_decl(decl.type) + "*"
        elif typ == c_ast.ArrayDecl:
            arr = 'array'
            if decl.dim: arr += '[%s]' % decl.dim.value
            
            return arr + " of " + self._expand_decl(decl.type)
            
        elif typ == c_ast.FuncDecl:
            if decl.args:
                params = [_expand_decl(param) for param in decl.args.params]
                args = ', '.join(params)
            else:
                args = ''
            
            return ('function(%s) returning ' % (args) +
                    _expand_decl(decl.type))

def parse_header(filename):
    # Note that cpp is used. Provide a path to your own cpp or
    # make sure one exists in PATH.

    defautl_defines = [
        r"-D__attribute__(x)= ",
        r"-D__builtin_va_start(v,l)=va_start",
        #r"-D__GNUC_VA_LIST",
        r"-D__const=",
    ]

    ast = parse_file(filename, use_cpp=True , cpp_args=defautl_defines)

    v = FuncDefVisitor(filename)
    v.visit(ast)

    return v.getFuncList();

def gen_one_file(templatefile,outfile,locals):
    print(outfile)

    tfd = open(templatefile,"r")
    template = tfd.read()
    tfd.close()

    for local in locals:
        strfrom = "%="+local+"%"
        #print(strfrom)
        template = template.replace(strfrom,str(locals[local]))

    ofd = open(outfile,"w")
    locals["print"] = ofd.write

    #print(template)
    temp = tempfile.NamedTemporaryFile(delete=False)    #
    print(temp.name)
    last = 0
    reobj = re.compile(r"/\*py(.*?)py\*/", re.DOTALL)
    for m in reobj.finditer(template):
        code = template[last:m.start()]
        code = code.replace("\\","\\\\")
        temp.write('print("""' + code + '""")\n')

        temp.write(m.group(1))

        last = m.end()

    code = template[last:]
    code = code.replace("\\","\\\\")
    temp.write('print("""' + code + '""")\n')
    temp.flush()

    #eval can`t work for mulielines python code
    execfile(temp.name,{},locals)

    temp.close()

def gen_c_files(funclist,filename):
    basepath = os.path.split(os.path.realpath(__file__))[0]
    #print(basepath)

    basename,extname = os.path.splitext(filename)
    extname = extname[1:]
    #print(basename)
    #print(extname)

    locals = {}
    locals["filename"] = filename
    locals["basename"] = basename
    locals["extname"] = extname
    locals["functionslist"] = funclist
    #print(locals)

    templatefilename = basepath+os.sep+"templates/remote_template.h"
    outfilename = os.getcwd()+os.sep+"remote_"+basename+".h"
    gen_one_file(templatefilename,outfilename,locals)

    templatefilename = basepath+os.sep+"templates/remote_template.cpp"
    outfilename = os.getcwd()+os.sep+"remote_"+basename+".cpp"
    gen_one_file(templatefilename,outfilename,locals)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename  = sys.argv[1]
    else:
        print("Usage: " + sys.argv[0] + " headerFile")

    funclist = parse_header(filename)
    #print(funclist)

    basename = os.path.basename(filename)
    gen_c_files(funclist,basename)

    tab = "                "
    for func in funclist:
        code = ""
        argname = []
        i = 0
        for paramter in func["paramters"]:
            print(paramter)
            unknownCnt = 1
            argname.append(paramter[1])
            if argname[i] == None:
                argname[i] = "_arg" + str(unknownCnt)
                unknownCnt += 1

            if paramter[0] == "int" or paramter[0] == "int32_t":
                code += "%(tab)s%(type)s %(name)s = data.readInt32();  //%(type)s as input paramter\r\n" % {"tab":tab,"type":paramter[0],"name":argname[i]}
            elif paramter[0] == "int*" or paramter[0] == "int32_t*":
                code += "%(tab)s%(type)s %(name)s = data.readInt32();  //%(type)s as input paramter\r\n" % {"tab":tab,"type":paramter[0],"name":argname[i]}

            i += 1

        print(code)


