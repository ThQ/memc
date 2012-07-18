import json
import string
import sys

kIN = sys.argv[1] #"./src/mem/log/Errors.in"
kOUT = sys.argv[2] #"./src/mem/log/errors.hpp"

kINDENT = "   "
kTYPES = ["Error", "Warning", "FatalError"]
converters = {
    "int" :           ["%d", "@"],
    "std::string" :   ["%s", "@.c_str()"],
    "st::Symbol*" :   ["%s", "( (@)!=NULL ? @->gQualifiedNameCstr() : \"<?>\")"]
}


class ErrorTypeNotFoundError (Exception):
    pass

class Err:
    def __init__ (self, name):
        self.description = ""
        self.name = name
        self.message = ""
        self.ty = ""
        self.params = {}

    def export_hpp (self):
        out = ""
        out += "class " + self.name + " : public " + self.ty + "\n"
        out += "{\n"

        if len(self.params) > 0:
            for param_id in self.params:
                out += kINDENT + "public: " + self.params[param_id] + " _" + param_id + ";\n"
            out += "\n"

        for param_id in self.params:
            out += kINDENT + "public: inline void s" + param_id + "(" + self.params[param_id] + " " + param_id + ")"
            out += " {_" + param_id + "=" + param_id + ";}\n"

        #out += kINDENT + "public: " + self.name + "();\n"
        out += kINDENT + "public: inline void format() {"
        out += "formatMessage" + self.format_str(self.message) + ";"

        if self.description != "":
            out += "formatDescription" + self.format_str(self.description) + ";"

        out += "}\n"

        out += "};\n\n"

        return out

    def load (self, json):
        self.message = json["message"]
        self.params = json["params"] if ("params" in json) else {}
        self.description = json["description"] if ("description" in json) else ""
        if json["type"] in kTYPES:
            self.ty = json["type"]
        else:
            raise ErrorTypeNotFoundError()


    def format_str (self, s):
        is_param = False
        param_name = ""
        params = ""
        buff = ""

        for c in (s + " "):
            if is_param:
                if c not in string.ascii_letters:
                    buff += converters[self.params[param_name]][0] + c
                    params += ", " + converters[self.params[param_name]][1].replace("@", "_" + param_name)
                    param_name = ""
                    is_param = False
                else:
                    param_name += c
            else:
                if c == "$":
                    is_param = True
                else:
                    buff += c

        return "(\"" + buff + "\"" + params + ")"


src = open(kIN)
src_json = json.load(src)

hpp = ""
hpp += "#ifndef _MEM__LOG__ERRORS__HPP_\n"
hpp += "#define _MEM__LOG__ERRORS__HPP_\n\n\n"
hpp += "// " + ("-" * 76) + "\n"
hpp += "// !!! DONT EDIT MANUALLY !!!\n"
hpp += "// Generated\n"
hpp += "//    by <" + __file__ + ">\n"
hpp += "//    from <" + kIN + ">\n"
hpp += "// " + ("-" * 76) + "\n"
hpp += "\n\n"
hpp += "#include \"mem/log/Message.hpp\"\n\n"
hpp += "namespace mem { namespace log {\n\n\n"

for err_id in src_json:
    err = Err(err_id)
    err.load(src_json[err_id])
    hpp += err.export_hpp()

hpp += "\n\n} }\n"
hpp += "\n\n#endif\n"


fOut = open(kOUT, "w")
fOut.write(hpp)
fOut.close()
