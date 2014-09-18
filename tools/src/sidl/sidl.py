import sys
import parser

filename  = sys.argv[1]
fidl = open(filename)

parser.parse(fidl)