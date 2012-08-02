import os
import subprocess

kCWD=os.getcwd()
kTEST_DIR = kCWD + "/tests"
kMEMC = kCWD + "/mem_compile"
kBIN = kCWD + "/build/memt"
kMEM_SRC=os.getcwd() + "/build/test.mem"
kREPORT_DIR = kCWD + "/build/test-reports"


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
      print " * Failed:", len(self._failed_tests), "(" + str(len(self._failed_tests)/self._num_tests*100) + "%)"
      print " * Succeeded:", self._num_tests - len(self._failed_tests), "(" + str(100-(len(self._failed_tests)/self._num_tests)*100) + "%)"
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

   def run (self, path, name):
      args = [kMEMC, "--log-level=debug", "--log-formatter=xml", "--output=" + kBIN, str(path)]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE)
      data = memc.communicate()[0]
      retcode = int(memc.returncode)

      if retcode:
         report = open(kREPORT_DIR + "/" + name, "w+")
         if report:
            report.write(data)
            report.close()
      return retcode

   def run_all (self):
      self.print_section("Running tests...")
      self._num_tests = len(os.listdir(kTEST_DIR))

      i = 1
      items = os.listdir(kTEST_DIR)
      items.sort()
      line = ""
      for item in items:
         line = ""
         test_file = kTEST_DIR + "/" + item

         line += "("
         line += str(i)
         line += "/"
         line += str(self._num_tests)
         line += ") Running " + item

         ret_code = self.run_test_file(test_file, item)
         if ret_code != 0:
            self._failed_tests.append(item)
            line += "." * (79 - len(line) - 7) + " FAILED"
         else:
            line += "." * (79 - len(line) - 3) + " OK"
         i += 1
         print line

runner = TestRunner()
runner.run_all()
runner.print_summary()


