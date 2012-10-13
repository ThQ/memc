import argparse
import os
import os.path

kTAB = "   "
args_parser = argparse.ArgumentParser(description='Generate utilities for simple Run-Time Type Informations')
args_parser.add_argument("--template", required=True)
args_parser.add_argument("--namespace", required=True)
args_parser.add_argument("--output-hpp-file", required=True)
args_parser.add_argument("--output-cpp-file", required=True)
args_parser.add_argument("--klass", required=True)
args = args_parser.parse_args()


class RttiType:
    def __init__ (self):
        self.name = ""
        self.parent = None
        self.children = []

    def get_all_children (self):
        children = []
        for child in self.children:
            children.append(child)
            children.extend(child.get_all_children())
        return children

    def get_cpp_name (self):
        return "".join([part[0] + part[1:].lower() for part in self.name.split("_")])

    def to_string (self):
        s = '[' + self.name + ']'
        if len(self.children) > 0:
            s += "{"
            for child in self.children:
                s += child.to_string()
            s += "}"
        return s

class RttiParser:
    def __init__ (self):
        self.source_file = None
        self.types = []
        self.namespace = ""
        self.root_ty = None
        self.hpp_file_path = ""
        self.klass = ""

    def generate_cpp (self):
        namespaces = self.namespace.upper().split(".")

        cpp = '#include "' + self.hpp_file_path + '"\n\n'

        for ns in namespaces:
            cpp += "namespace " + ns.lower() + " {"
        cpp += "\n\n"

        cpp += "const char* kKIND_NAMES[] = {\n"
        cpp += kTAB + (",\n" + kTAB).join(['"' + ty.name + '"' for ty in self.types])
        cpp += "\n};\n\n"

        cpp += "bool canCast (int source_kind, int dest_kind)\n"
        cpp += "{\n"
        cpp += kTAB + "switch (dest_kind)\n"
        cpp += 2*kTAB + "{\n"
        for ty in self.types:
            cpp += "case " + self.klass + "::" + ty.name + ": return canCastTo" + ty.get_cpp_name() + "(source_kind);\n"
        cpp += 2*kTAB + "}\n"
        cpp += kTAB + "return false;\n"
        cpp += "}\n\n"

        for ty in self.types:
            children = ty.get_all_children()
            cpp += "bool canCastTo" + ty.get_cpp_name() + " (int k)\n"
            cpp += "{\n"
            if len(children) > 0:
                cpp += kTAB + "switch (k)\n"
                cpp += kTAB + "{\n"
                cpp += 2 * kTAB + "case " + self.klass + "::" + ty.name + ":\n"
                for child in children:
                    cpp += 2 * kTAB + "case " + self.klass + "::" + child.name + ":\n"
                cpp += 3*kTAB + "return true;\n"
                cpp += kTAB + "}\n"
                cpp += kTAB + "return false;\n"
            else:
                cpp += kTAB + "return k == " + self.klass + "::" + ty.name + ";\n"
            cpp += "}\n\n"

        cpp += len(namespaces) * "}" + "\n"

        return cpp

    def generate_hpp (self):
        hpp = ""
        namespaces = self.namespace.upper().split(".")

        hpp_id = "_" + "__".join(namespaces) + "_"


        hpp += "#ifndef " + hpp_id + "_KIND_\n"
        hpp += "#define " + hpp_id + "_KIND_\n\n"

        for ns in namespaces:
            hpp += "namespace " + ns.lower() + " {"

        hpp += "\n\n"

        hpp += "class " + self.klass + " { public: enum _KindEnum {\n" + kTAB
        hpp += (",\n" + kTAB).join([ty.name for ty in self.types])
        hpp += "\n};};\n\n"

        hpp += "extern const char* kKIND_NAMES[];\n\n"

        hpp += "bool canCast(int source_kind, int dest_kind);\n"


        for ty in self.types:
            children = ty.get_all_children()
            hpp += "bool canCastTo" + ty.get_cpp_name() + " (int k);\n"

        hpp += len(namespaces) * "}" + "\n"
        hpp += "#endif\n"
        return hpp

    def parse_file (self, file_path):
        self.source_file = open(file_path, "r")
        if not self.source_file:
            return None
        buff = ""
        contents = self.source_file.read()

        stack = ""
        self.root_ty = RttiType()
        cur_ty= self.root_ty

        for c in contents:
            if c.isalpha() or c == "_":
                stack += c
            elif c == "{" or c.isspace():
                if len(stack) > 0:
                    new_ty = RttiType()
                    new_ty.name = stack
                    new_ty.parent = cur_ty
                    self.types.append(new_ty)
                    cur_ty.children.append(new_ty)
                    stack = ""
                if c == "{":
                    cur_ty = new_ty
            elif c == "}":
                cur_ty = cur_ty.parent

parser = RttiParser()
parser.namespace = args.namespace
parser.parse_file(args.template)
parser.hpp_file_path = args.output_hpp_file
parser.klass = args.klass

kOUT_HPP_DIR = os.path.dirname(args.output_hpp_file)
kOUT_CPP_DIR = os.path.dirname(args.output_cpp_file)

if not os.path.isdir(kOUT_HPP_DIR):
   os.makedirs(kOUT_HPP_DIR)

if not os.path.isdir(kOUT_CPP_DIR):
   os.makedirs(kOUT_CPP_DIR)

hpp_file = open(args.output_hpp_file, "w")
if hpp_file:
    hpp_file.write(parser.generate_hpp())

cpp_file = open(args.output_cpp_file, "w")
if cpp_file:
    cpp_file.write(parser.generate_cpp())
