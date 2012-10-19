import argparse
import cgi
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

REPORT_CSS = """
html {
   padding:0;
   margin:0;
}
body {
   font-size:0.9em;
   padding:0;
   margin:0 10px 0 250px;
}
#toc {
   border-right:5px solid #DADADA;
   position:fixed;
   left:0;
   top:0;
   width:200px;
   background:#E6E6E6;
   margin:0;
   padding:10px 10px 10px 20px;
   list-style-type:square;
   font-family:"Open Sans","Helvetica Neue",Helvetica,Arial,sans-serif;
   height:100%;
   font-size:0.8em;
}
#toc li {
   margin:2px 0 2px 0;
}
#toc a:link, #toc a:visited, #toc a:hover {
   color:#1C44B3;
}

h1 {
   font-family:Roboto,arial,sans-serif;
   font-weight:normal;
}
h2 {
   font-family:Georgia,arial,sans-serif;
   font-weight:normal;
}
h3 {
   font-family:Georgia,arial,sans-serif;
   font-weight:normal;
}
h4 {
   font-family:arial,sans-serif;
   font-size:1em;
   font-weight:none;
   border-bottom:1px solid #D0D0D0;
   padding:10px;
   background:#FFFFFF;
   margin:0 0 10px 0;
   border-top-left-radius:5px;
   border-top-right-radius:5px;
}
code {
   display:block;
   border:1px solid #D0D0D0;
   border-radius:5px;
   background:#FFFFFF;
   color:#333333;
   font-family:'Droid Sans Mono', sans-mono;
   font-size:0.9em;
   padding:5px;
   margin:20px;
}
.tests ul {
   list-style-type:none;
   padding:0;
   margin:5px 0 5px 0;
}
.summary {
   font-size:0.8em;
}
.tests li {
   padding: 0;
   border:1px solid #D0D0D0;
   border-radius:5px;
   background:#F0F0F0;
   margin:0 0 20px 0;
}
a.passed {
   color:#FFFFFF;
   padding:3px;
   font-size:0.8em;
   font-weight:none;
   background:#7C8A31;
   border-radius:3px;
   margin:0 0 0 10px;
}
a.failed {
   color:#FFFFFF;
   padding:3px;
   font-size:0.8em;
   font-weight:none;
   background:#B62B15;
   border-radius:3px;
   margin:0 0 0 10px;
}

li.passed {
}
li.failed {
}
"""


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
      args = [kMEMC, "--log-level=debug", "--output=" + kBIN, str(self.out_path)]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      data = memc.communicate()[0]
      retcode = int(memc.returncode)

      report = TestReport()
      report.return_code = retcode
      report.log = data.decode()
      report.path = self.path
      report.name = self.name

      return retcode, report

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


class TestReport:
   def __init__ (self):
      self.return_code = 0
      self.log = ""
      self.path = ""
      self.name = ""


class TestRunner:

   def __init__ (self):
      self._failed_tests = []
      self._num_tests = 0
      self._num_failed_tests = 0
      self._num_passed_tests = 0
      self._percent_failed_tests = 0
      self._percent_passed_tests = 0
      self._logger = TestLogger()
      self._reports = []

   def dump_html_report (self, report_file):
      html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"
      html += "<html xmlns=\"http://www.w3.org/1999/xhtml\">"
      html += "<head>"
      html += "<title>memc test report</title>"
      html += "<style type=\"text/css\">" + REPORT_CSS + "</style>"
      html += "</head>"
      html += "<body>"


      html += "<h1><a name=\"top\"></a> Test report</h1>"
      html += "<ul id=\"toc\">"
      html += "<li><a href=\"#summary\">Summary</a></li>"
      html += "<li><a href=\"#memc\">memc</a></li>"
      html += "<li><a href=\"#tests\">Tests</a></li>"
      html += "</ul>"

      html += "<h2><a name=\"summary\">#</a> Summary</h2>"
      html += "<table>"
      html += "<tr><td>" + str(self._num_failed_tests) + " failed</td>"
      html += "<td>" + str(self._num_passed_tests) + " passed </td></tr>"
      html += "</table>"

      html += "<h2><a name=\"memc\">#</a> memc</h2>"
      html += "<code>" + cgi.escape(self.get_memc_version_string()).replace("\n", "<br/>") + "</code>"

      html += "<h2><a name=\"tests\">#</a> Tests (" + str(self._num_tests) + ")</h2>"

      html += "<h3><a name=\"failed-tests\">##</a> Failed (" + str(self._num_failed_tests) + ")</h3>"
      html += "<div class=\"tests\">"
      html += "<ul>"
      for report in self._reports:
         if report.return_code != 0:
            html += "<li class=\""
            html += "\">"
            html += "<h4>"
            html += "<a name=\"" + cgi.escape(report.name) + "\" />" + cgi.escape(report.name)
            if report.return_code == 0:
               html += "<a class=\"passed\">Passed</a>"
            else:
               html += "<a class=\"failed\">Failed</a>"

            html += "</h4>"
            html += "<code>" + cgi.escape(report.log).replace("\n", "<br />").replace("\t", "&nbsp;"*3) + "</code>"
            html += "</li>"

      html += "</ul>"
      html += "</div>"

      html += "</body>"
      html += "</html>"

      f = open(report_file, "w+")
      if f:
         f.write(html)
         f.close()

   def get_memc_version_string (self):
      args = [kMEMC, "--version"]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      return memc.communicate()[0].decode()

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

   def run_all (self):
      self.log_section("Running tests for `" + kMEMC + "'...")
      self._logger.logln("Test directory: " + kTEST_DIR)
      self._logger.logln("Reports directory: " + kREPORT_DIR)
      self._logger.logln("")
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

            ret_code, report = test.run()
            self._reports.append(report)

            if ret_code == 0:
               self._num_passed_tests += 1
               line += "." * (79 - len(line) - 3) + " OK"
            elif ret_code == 1:
               self._num_failed_tests += 1
               self._failed_tests.append(item)
               line += "." * (79 - len(line) - 7) + " FAILED"
            else:
               self._num_failed_tests += 1
               self._failed_tests.append(item)
               line += "." * (79 - len(line) - 8) + " CRASHED"
            i += 1
            print (line)

      self._percent_failed_tests = self._num_failed_tests * 100 / self._num_tests
      self._percent_passed_tests = self._num_passed_tests * 100 / self._num_tests

runner = TestRunner()
runner.run_all()
runner.print_summary()
runner.dump_html_report(os.path.join(kREPORT_DIR, "memc-compilation-report.html"))


