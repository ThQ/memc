import argparse
import os
import os.path
import sys


args_parser = argparse.ArgumentParser(description='Generate C++ header and source files describing AST node kinds')
args_parser.add_argument("--template", required=True)
args_parser.add_argument("--output-cpp-file", required=True)
args_parser.add_argument("--output-hpp-file", required=True)
args = args_parser.parse_args()

kOUT_HPP_DIR = os.path.dirname(args.output_hpp_file)
kOUT_CPP_DIR = os.path.dirname(args.output_cpp_file)

if not os.path.isdir(kOUT_HPP_DIR):
   os.makedirs(kOUT_HPP_DIR)

if not os.path.isdir(kOUT_CPP_DIR):
   os.makedirs(kOUT_CPP_DIR)

src = open(args.template)

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
   hpp += "#endif\n"

   cpp = "#include \"" + args.output_hpp_file + "\"\n"
   cpp += "namespace mem { namespace ast { namespace node {\n"
   cpp += "const char* kKIND_NAMES[] = {\n"
   cpp += "   \"UNKNOWN\",\n   \""
   cpp += "\",\n   \"".join(lines)
   cpp += "\"\n};\n"
   cpp += "} } }\n"

   dest = open(args.output_hpp_file, "w+")
   if dest:
      dest.write(hpp)
      dest.close()

   dest = open(args.output_cpp_file, "w+")
   if dest:
      dest.write(cpp)
      dest.close()

