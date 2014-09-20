import re
import sys,os
import tempfile
import parser

from idlTypes import Include,Function,Argument

def usage():
    print("""INPUT required
usage: %s INPUT
generate .h and .cpp files for binder from standalone binder interface descript langurage.(sidl) 

INPUT:
   An sidl interface file.""" % os.path.basename(sys.argv[0]))   

def err(msg,code=-1):
    print(msg)

    if code < 0:
        exit(code)


def gen_one_file(templatefile,outfile,locals):
    #print(outfile)

    tfd = open(templatefile,"r")
    template = tfd.read()
    tfd.close()

    for local in locals:
        strfrom = "%="+local+"%"
        #print(strfrom)
        template = template.replace(strfrom,str(locals[local]))

    if os.path.exists(outfile):
        os.rename(outfile,outfile+".bak")
    ofd = open(outfile,"w")
    locals["output"] = ofd.write

    #print(template)
    temp = tempfile.NamedTemporaryFile(delete=True)
    #print(temp.name)
    temp.write("from idlTypes import Include,Function,Argument\n")

    last = 0
    reobj = re.compile(r"/\*py(.*?)py\*/", re.DOTALL)
    for m in reobj.finditer(template):
        code = template[last:m.start()]
        code = code.replace("\\","\\\\")
        temp.write('output("""' + code + '""")\n')

        temp.write(m.group(1))

        last = m.end()

    code = template[last:]
    code = code.replace("\\","\\\\")
    temp.write('output("""' + code + '""")\n')
    temp.flush()

    #eval can`t work for mulielines python code
    execfile(temp.name,{},locals)

    temp.close()
    ofd.close()


def gen_c_files(sidlcontext,inputfile):
    basepath = os.path.split(os.path.realpath(__file__))[0]
    #print(basepath)

    basename,extname = os.path.splitext(os.path.basename(inputfile))
    extname = extname[1:]
    #print(basename)
    #print(extname)

    locals = {}
    locals["sidl_filename"] = inputfile
    locals["sidl_basename"] = basename
    locals["sidl_extname"] = extname
    locals["sidl_context"] = sidlcontext
    #print(locals)

    templatefilename = basepath+os.sep+"templates/remote_template.h"
    outfilename = os.getcwd()+os.sep+basename+".h"
    gen_one_file(templatefilename,outfilename,locals)

    templatefilename = basepath+os.sep+"templates/remote_template.cpp"
    outfilename = os.getcwd()+os.sep+basename+".cpp"
    gen_one_file(templatefilename,outfilename,locals)


def gen(inputfile):
    sidlfd = open(inputfile)
    sidlcontext = parser.parse(sidlfd)

    if sidlcontext == None:
        err("Parse %s failed" % (inputfile))

    gen_c_files(sidlcontext,inputfile)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        INPUT  = sys.argv[1]
    else:
        usage()
        exit(-1)

    gen(INPUT)


