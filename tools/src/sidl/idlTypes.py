from collections import namedtuple

Include = namedtuple('Include', 'cmd')
Function = namedtuple('Function', 'ret name paramters')
Argument = namedtuple('Argument', 'qualifier type isPtr name len')