import argparse
import os
import os.path
import subprocess
import sys

args_parser = argparse.ArgumentParser(description='Test a memc executable')
args_parser.add_argument("--memc-exe", required=True)
args_parser.add_argument("--test-dir", required=True)
args_parser.add_argument("--report-dir", required=True)
args = args_parser.parse_args()

kCWD=os.getcwd()
kTEST_DIR = args.test_dir
kMEMC = args.memc_exe
kREPORT_DIR = args.report_dir

if not os.path.isdir(kREPORT_DIR):
   os.makedirs(kREPORT_DIR)

kBIN = os.path.join(kREPORT_DIR, "memt")
kMEM_SRC = os.path.join(kREPORT_DIR, "test.mem")

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
            report.write(str(data))
            report.close()
      return retcode

   def write_test_source (self):
      if "file" in self.sections:
         f = open(self.out_path, "w+")
         if f:
            f.write(self.sections["file"])
            f.close()

class TestLogger:
   def log (self, msg):
      print (msg,)
   def logln (self, msg):
      print (msg)

class TestRunner:
   def __init__ (self):
      self._failed_tests = []
      self._num_tests = 0
      self._logger = TestLogger()

   def log_section (self, name):
      section = "=" * 79 + "\n"
      section += " " + name + "\n"
      section += "-" * 79
      self._logger.logln(section)

   def print_summary (self):
      percent_failed = int(round(1.0 * len(self._failed_tests)/self._num_tests*100, 0))
      percent_passed = int(round(100-(1.0 * len(self._failed_tests)/self._num_tests)*100, 0))
      print ("")
      self.log_section("Summary")
      summary = str(self._num_tests) + " tests run\n"
      summary += " - Failed: " + str(len(self._failed_tests)) + " (" + str(percent_failed) + "%)\n"
      summary += " - Passed: " + str(self._num_tests - len(self._failed_tests)) + " (" +  str(percent_passed) + "%)"
      self._logger.logln(summary)

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
      self.log_section("Running tests for `" + kMEMC + "'...")
      print("Test directory: " + kTEST_DIR)
      print("Reports directory: " + kREPORT_DIR)
      print("")
      self._num_tests = len(os.listdir(kTEST_DIR))

      i = 1
      items = os.listdir(kTEST_DIR)
      items.sort()
      line = ""
      for item in items:
         if item.endswith(".memt"):
            test = TestFile()
            test.open(os.path.join(kTEST_DIR + "/" + item))

            line = ""
            line += "[" + str(int(1.0*i/self._num_tests*100)).rjust(3) + "%]"
            line += " " + test.name + " "

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
            print (line)

runner = TestRunner()
runner.run_all()
runner.print_summary()


