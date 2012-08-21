import sys

kIN = sys.argv[1]
kOUT = sys.argv[2]

print(kIN)

def make_out_header (kinds):
   out ="#ifndef _LANGMEM__TOKEN_KIND__HPP_\n"
   out += "#define _LANGMEM__TOKEN_KIND__HPP_\n\n"
   out += "// " + ("-" * 76) + "\n"
   out += "// !!! DONT EDIT MANUALLY !!!\n"
   out += "// Generated\n"
   out += "//    by <" + __file__ + ">\n"
   out += "//    from <" + kIN + ">\n"
   out += "// " + ("-" * 76) + "\n"
   out += "\n\n"
   out += "namespace langmem {\n\n"
   out += "typedef enum _TokenKind {\n"
   out += "   T_YACC_END=0,\n"
   out += "   T_YACC_ERROR=1,\n"
   out += "   T_YACC_UNDEFINED=2,\n"

   for i in xrange(0, len(kinds)):
      kind = kinds[i]
      out += "   " + kind[0] + "=" + kind[1] + ",\n"

   out += "} TokenKind;\n\n"
   out += "}\n\n"
   out += "#endif\n"

   return out


in_file = open(kIN)
if in_file:
   yacc_headers = in_file.read()
   kinds = [line.split(" ")[1:]
      for line in yacc_headers.split("\n")
      if line.startswith("#define T_")]
   in_file.close()
   out_file = open(kOUT, "w+")
   if out_file:
      out_file.write(make_out_header(kinds))
      out_file.close()
