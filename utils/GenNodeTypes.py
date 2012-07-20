import sys


kIn = sys.argv[1]
kOut = sys.argv[2]
src = open(kIn)

if src:
   content = src.read()
   src.close()
   lines = [line for line in content.split("\n") if len(line)!=0]
   out = ""

   hpp = "#ifndef _MEM__AST__NODE__KIND__HPP_\n"
   hpp += "#define _MEM__AST__NODE__KIND__HPP_\n\n\n"
   hpp += "namespace mem { namespace ast { namespace node {\n"
   hpp += "class Kind {public: enum _Kind {\n"
   hpp += "   UNKNOWN=0,\n   "
   hpp += ",\n   ".join(lines)
   hpp += "\n};};\n"
   hpp += "extern const char* kKIND_NAMES[];\n"
   hpp += "} } }\n"
   hpp += "#endif"

   cpp = "#include \"" + kOut + "\"\n"
   cpp += "namespace mem { namespace ast { namespace node {\n"
   cpp += "const char* kKIND_NAMES[] = {\n"
   cpp += "   \"UNKNOWN\",\n   \""
   cpp += "\",\n   \"".join(lines)
   cpp += "\"\n};\n"
   cpp += "} } }"

   dest = open(kOut, "w")
   if dest:
      dest.write(hpp)
      dest.close()

   dest = open(kOut.replace(".hpp", ".cpp"), "w")
   if dest:
      dest.write(cpp)
      dest.close()

