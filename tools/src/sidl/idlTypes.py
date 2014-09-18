from collections import namedtuple

class Include():
    def __init__(self,cmd):
        self._cmd = cmd

    def __str__(self):
        return "Include: " + self._cmd

class Argument():
    def __init__(self):
        self._qualifier = None
        self._type = None
        self._isPtr = False
        self._name = None
        self._len = None
        self._tag = []

    def __str__(self):
        return "Argument:" + ' '.join((str(self._qualifier),str(self._type),str(self._isPtr), str(self._name),str(self._len),str(self._tag)))

    def addQualifier(self,qualifier):
        if not self._qualifier:
            self._qualifier = qualifier
        else:
            self._qualifier += qualifier

    def setype(self,type):
        self._type = type

    def setIsPtr(self,isPrt):
        self._isPtr = isPrt

    def setLen(self,len):
        self._len = len

    def setName(self,name):
        self._name = name

    def addTag(self,tag):
        self._tag.append(tag)

    def smartAdd(self,arg):
        if arg == "const":
            self.addQualifier(arg)
        elif arg == "void":
            self.setype(None)
        elif arg == "*":
            self.setIsPtr(True)
        elif arg[0] == '{' and arg[-1] == '}':
            self.addTag(arg[1:-1])
        elif self._type == None:
            self.setype(arg)
        elif self._name == None:
            self.setName(arg)
        else:
            print("smartAdd failed")


class Function():
    def __init__(self):
        self._ret = None
        self._name = None
        self._arguments = []

    def __str__(self):
        ret =  "Function: ret=%s name=%s args=" % ( str(self._ret), self._name)
        for arg in self._arguments:
            ret += "\n      " + str(arg)

        return ret

    def setReturn(self,ret):
        self._ret = ret

    def setName(self,name):
        self._name = name

    def addArgument(self,arg):
        self._arguments.append(arg)

    def getLastArgument(self):
        if len(self._arguments) <= 0:
            return None
        return self._arguments[-1]

