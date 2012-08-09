import os
import os.path
import subprocess

kCWD=os.getcwd()
kTEST_DIR = kCWD + "/tests"
kMEMC = "memc"
kBIN = kCWD + "/build/memt"
kMEM_SRC=os.getcwd() + "/build/test.mem"
kREPORT_DIR = kCWD + "/build/test-reports"


class TextOutsideOfSectionError (Exception):
   pass

class TestFile:
   def __init__ (self):
      self.sections = {}
      self.content = ""
      self.name = ""
      self.path = ""
      self.out_path = ""

   def parse (self):
      self.sections = {}
      section_name = ""

      for line in self.content.split("\n"):
         if len(line) >= 4 and line[0:3] == "###":
            section_name = line[4:].strip()
            self.sections[section_name] = ""
         else:
            if section_name == "":
               raise TextOutsideOfSectionError()
            self.sections[section_name] += line + "\n"

   def open (self, path):
      self.content = ""
      self.name = os.path.splitext(os.path.basename(path))[0]
      self.out_path = kMEM_SRC
      self.path = path
      fin = open(path, "r")
      if fin:
         self.content = fin.read()
         fin.close()
         self.parse ()
         self.write_test_source()

   def run (self):
      args = [kMEMC, "--log-level=debug", "--log-formatter=xml", "--output=" + kBIN, str(self.out_path)]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      data = memc.communicate()[0]
      retcode = int(memc.returncode)

      if retcode:
         report = open(kREPORT_DIR + "/" + self.name, "w+")
         if report:
            report.write(data)
            report.close()
      return retcode

   def write_test_source (self):
      if "file" in self.sections:
         f = open(self.out_path, "w+")
         if f:
            f.write(self.sections["file"])
            f.close()

class TestRunner:
   def __init__ (self):
      self._failed_tests = []
      self._num_tests = 0

   def print_section (self, name):
      print "=" * 79
      print " " + name
      print "=" * 79
      print ""

   def print_summary (self):
      print ""
      self.print_section("Summary")
      print "", self._num_tests, "tests run"
      print " * Failed:", len(self._failed_tests), "(" + str(1.0 * len(self._failed_tests)/self._num_tests*100) + "%)"
      print " * Succeeded:", self._num_tests - len(self._failed_tests), "(" + str(100-(1.0 * len(self._failed_tests)/self._num_tests)*100) + "%)"
      print ""

   def read_file (self, path):
      contents = ""
      fin = open(path, "r")
      if fin:
         contents = fin.read()
         fin.close()
      return contents

   def run_test_file (self, path, name):
      memt = self.read_file(path)
      out = open(kMEM_SRC, "w+")
      ret_code = 0
      if out:
         out.write(memt)
         out.close()

         ret_code = self.run(path, name)
      return ret_code

   def run_all (self):
      self.print_section("Running tests...")
      self._num_tests = len(os.listdir(kTEST_DIR))

      i = 1
      items = os.listdir(kTEST_DIR)
      items.sort()
      line = ""
      for item in items:
         test = TestFile()
         test.open(os.path.join(kTEST_DIR + "/" + item))

         line = ""
         line += "[" + str(int(1.0*i/self._num_tests*100)).rjust(3) + "%]"
         line += " Running " + test.name + " "

         ret_code = test.run()
         if ret_code == 0:
            line += "." * (79 - len(line) - 3) + " OK"
         elif ret_code == 1:
            self._failed_tests.append(item)
            line += "." * (79 - len(line) - 7) + " FAILED"
         else:
            self._failed_tests.append(item)
            line += "." * (79 - len(line) - 8) + " CRASHED"
         i += 1
         print line

runner = TestRunner()
runner.run_all()
runner.print_summary()


