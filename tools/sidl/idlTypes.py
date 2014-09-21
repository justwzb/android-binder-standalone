from collections import namedtuple

class Include():
    def __init__(self,cmd):
        self._cmd = cmd

    def __str__(self):
        return "Include: " + self._cmd

    def output(self):
        return str(self._cmd)

class Argument():
    def __init__(self):
        self._qualifier = ""
        self._type = []
        self._isPtr = False
        self._name = ""
        self._len = ""
        self._tag = []

    def __str__(self):
        return "Argument:" + ' '.join((str(self._qualifier),str(self._type),str(self._isPtr), str(self._name),str(self._len),str(self._tag)))

    def addQualifier(self,qualifier):
        if not self._qualifier:
            self._qualifier = qualifier + " "
        else:
            self._qualifier += qualifier + " "

    def getQualifier(self):
        return self._qualifier

    def getType(self):
        if len(self._type) > 0:
            return " ".join(self._type)
        else:
            return "void"

    def setIsPtr(self,isPrt):
        self._isPtr = isPrt

    def isPtr(self):
        return self._isPtr

    def setLen(self,len):
        self._len = len

    def setName(self,name):
        self._name = name

    def getName(self):
        return self._name

    def addTag(self,tag):
        self._tag.append(tag)

    def getTags(self):
        return self._tag

    def hasInFlag(self):
        tags = self._tag
        return "in" in tags or "inout" in tags

    def hasOutFlag(self):
        tags = self._tag
        return "out" in tags or "inout" in tags

    def getPtrLen(self):
        tags = self._tag
        for tag in tags:
            if tag[0:4] == "len:":
                return tag[4:]

        return None

    def smartAdd(self,arg):
        if arg == "const":
            self.addQualifier(arg)
        elif arg == "void":
            self._type = []
        elif arg == "*":
            self.setIsPtr(True)
        elif arg[0] == '{' and arg[-1] == '}':
            self.addTag(arg[1:-1])
        elif arg == ",":
            if self._name == "":
                self._name = self._type.pop()
        else:
            self._type.append(arg)


class Function():
    def __init__(self):
        self._ret = None
        self._name = ""
        self._arguments = []

    def __str__(self):
        ret =  "Function: ret=%s name=%s args=" % ( str(self._ret), self._name)
        for arg in self._arguments:
            ret += "\n      " + str(arg)

        return ret

    def setReturn(self,ret):
        self._ret = ret

    def getReturn(self):
        return self._ret

    def setName(self,name):
        self._name = name

    def getName(self):
        return self._name

    def addArgument(self,arg):
        self._arguments.append(arg)

    def getArgument(self,idx):
        if len(self._arguments) <= 0:
            return None
        return self._arguments[idx]

    def getArguments(self):
        return self._arguments

