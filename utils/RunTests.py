import argparse
import cgi
import os
import os.path
import re
import subprocess
import sys

args_parser = argparse.ArgumentParser(description='Test a memc executable')
args_parser.add_argument("--memc-exe", required=True)
args_parser.add_argument("--test-dir", required=True)
args_parser.add_argument("--report-dir", required=True)
args_parser.add_argument("--data-dir", required=True)
args = args_parser.parse_args()

kCWD=os.getcwd()
kDATA_DIR = args.data_dir
kTEST_DIR = args.test_dir
kMEMC = args.memc_exe
kREPORT_DIR = args.report_dir

if not os.path.isdir(kREPORT_DIR):
   os.makedirs(kREPORT_DIR)

kBIN = os.path.join(kREPORT_DIR, "memt")
kMEM_SRC = os.path.join(kREPORT_DIR, "test.mem")

gLOG_LINE_RE = re.compile("\(([DIWEF])\) ([a-z-]+)", re.MULTILINE)

class TextOutsideOfSectionError (Exception):
   pass

class TestFile:
   def __init__ (self):
      self.command = ""
      self.sections = {}
      self.content = ""
      self.name = ""
      self.path = ""
      self.out_path = ""
      self.options = {}
      self.output_log = []
      self.expected_output_log = []

   def parse (self):
      self.sections = {}
      section_name = ""

      for line in self.content.splitlines():
         if len(line) >= 4 and line[0:3] == "###":
            section_name = line[4:].strip()
            self.sections[section_name] = ""
         else:
            if section_name == "":
               raise TextOutsideOfSectionError()
            self.sections[section_name] += line + "\n"

      if "options" in self.sections:
         self.parse_options(self.sections["options"])

      if "log" in self.sections:
         self.parse_log_section(self.sections["log"])

   def parse_options (self, options_str):
      lines = [line.strip() for line in options_str.splitlines()]
      for line in lines:
         if line != "":
            colon_pos = line.find(":")
            if colon_pos != -1:
               self.options[line[0:colon_pos]] = line[colon_pos:]
            else:
               self.options[line] = ""

   def parse_log_section (self, expected_logs):
      lines = [line.strip() for line in expected_logs.splitlines() if line != ""]
      self.expected_output_log = [line.split(":") for line in lines]

   def parse_output (self, data):
      matches = gLOG_LINE_RE.findall(str(data))
      for match in matches:
         if match[0] != "D" and match[0] != "I":
            self.output_log.append([match[0], match[1]])

   def open (self, path):
      self.content = ""
      self.name = path[len(kTEST_DIR) + 1:-5]
      self.out_path = kMEM_SRC
      self.path = path
      fin = open(path, "r")
      if fin:
         self.content = fin.read()
         fin.close()
         self.parse ()

   def run (self):
      self.write_test_source()

      args = [kMEMC, "--log-level=debug", "--color=no", "--log-formatter=\"test-friendly\"", "--output=" + kBIN, str(self.out_path)]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      data = memc.communicate()[0]
      retcode = int(memc.returncode)

      self.parse_output(data)

      report = TestReport()
      report.return_code = retcode
      report.command = " ".join(args)
      report.log = data.decode()
      report.path = self.path
      report.name = self.name
      report.source = self.content

      if len(self.expected_output_log) > 0 and self.output_log != self.expected_output_log:
         report.status = "failed"
         report.reason = "Logs differ"
      else:
         if "must-not-compile" in self.options:
            if report.return_code == 1:
               report.status = "passed"
            elif report.return_code == 0:
               report.reason = "Should not have compiled"
               report.status = "failed"
         else:
            if report.return_code == 0:
               report.status = "passed"
            elif report.return_code == 1:
               report.reason = "Should have compiled"
               report.status = "failed"

      if report.return_code != 0 and report.return_code != 1:
         report.status = "crashed"
         report.reason = "Crashed"

      return report

   def write_test_source (self):
      if "file" in self.sections:
         f = open(self.out_path, "w+")
         if f:
            f.write(self.sections["file"])
            f.close()


class TestLogger:

   def log (self, msg):
      print (msg, end="")

   def logln (self, msg):
      print (msg)

   def log_default_color (self):
      print ("\033[0m", end="")

   def log_blue (self, text, bold=False):
      print ("\033[" + ("1" if bold else "0") + ";34m" + text + "\033[0m", end="")

   def log_green (self, text, bold=False):
      print ("\033[" + ("1" if bold else "0") + ";32m" + text + "\033[0m", end="")

   def log_section (self, name):
      self.logln("")
      self.logln(" " + ("=" * 78))
      self.log("| ")
      self.log_blue(name.ljust(76), bold=True)
      self.logln(" |")
      self.logln(" " + ("-" * 78))


   def log_red (self, text, bold=False):
      print ("\033[" + ("1" if bold else "0") + ";31m" + text + "\033[0m", end="")


class TestReport:
   def __init__ (self):
      self.source = ""
      self.return_code = 0
      self.log = ""
      self.path = ""
      self.name = ""
      self.reason = ""
      self.status = ""


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
      self._tests = []

   def discover_tests (self, dir_path):
      i = 1
      items = os.listdir(dir_path)
      items.sort()
      line = ""
      for item in items:
         full_path = os.path.join(dir_path, item)
         if item.endswith(".memt"):
            self._num_tests += 1
            test = TestFile()
            test.open(full_path)
            self._tests.append(test)
         elif os.path.isdir(full_path):
            self.discover_tests(full_path)

   def dump_html_report (self, report_file):
      css_file = open(os.path.join(kDATA_DIR, "test", "report.css"))
      css = ""
      if css_file:
         css = css_file.read()

      html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"
      html += "<html xmlns=\"http://www.w3.org/1999/xhtml\">"
      html += "<head>"
      html += "<title>memc test report</title>"
      html += "<style type=\"text/css\">" + css + "</style>"
      html += "</head>"
      html += "<body>"


      html += "<h1><a name=\"top\"></a> Test report</h1>"
      html += "<ul id=\"toc\">"
      html += "<li><a href=\"#summary\">Summary</a></li>"
      html += "<li><a href=\"#memc\">memc</a></li>"
      html += "<li><a href=\"#tests\">Tests</a></li>"
      html += "</ul>"

      if self._num_failed_tests > 0:
         html += "<p id=\"submit-box\">"
         html += "Please <strong>submit this report</strong> to our <a href=\"https://github.com/ThQ/memc/issues/new?title=Failing+tests\">issue tracker</a>."
         html += " You have stumbled upon some bugs that we'd like to know about."
         html += "</p>"

      html += "<table id=\"summary\">"
      html += "<tr><th>Failed</th><th>Passed</th></tr>"
      html += "<tr>"
      html += "<td>" + str(round(self._percent_failed_tests,1)) + "%</td>"
      html += "<td>" + str(round(self._percent_passed_tests,1)) + "%</td>"
      html += "<tr>"
      html += "<tr>"
      html += "<td>" + str(self._num_failed_tests) + "</td>"
      html += "<td>" + str(self._num_passed_tests) + "</td>"
      html += "<tr>"
      html += "</table>"

      html += "<h2><a name=\"summary\">#</a> Summary</h2>"
      html += "<table>"
      html += "<tr><th>Test</th><th>Status</th><th>Return code</th></tr>"

      for report in self._reports:
         html += "<tr>"
         html += "<td>" + cgi.escape(report.name) + "</td>"
         if report.status != "passed":
            html += "<td><a href=\"#" + cgi.escape(report.name) + "\">" + cgi.escape(report.status) + "</a></td>"
         else:
            html += "<td>Passed</td>"
         html += "<td>" + cgi.escape(str(report.return_code)) + "</td>"
         html += "</tr>"
      html += "</table>"

      html += "<h2><a name=\"memc\">#</a> memc</h2>"
      html += "<pre class=\"code\">" + cgi.escape(self.get_memc_version_string()) + "</pre>"

      html += "<h2><a name=\"tests\">#</a> Tests (" + str(self._num_tests) + ")</h2>"

      html += "<h3><a name=\"failed-tests\">##</a> Failed (" + str(self._num_failed_tests) + ")</h3>"
      html += "<div class=\"tests\">"
      html += "<ul>"
      for report in self._reports:
         if report.status != "passed":
            html += "<li class=\""
            html += "\">"
            html += "<h4>"
            html += "<a name=\"" + cgi.escape(report.name) + "\" />" + cgi.escape(report.name)
            if report.status == "passed":
               html += "<a class=\"passed\">Passed</a>"
            else:
               html += "<a class=\"failed\">" + cgi.escape(report.reason) + "</a>"

            html += "</h4>"

            html += "<p>Command:</p>"
            html += "<pre class=\"code\">" + cgi.escape(report.command) + "</pre>"

            html += "<p>Source:<p>"
            html += "<pre class=\"code\">" + cgi.escape(report.source) + "</pre>"

            html += "<p>Output:</p>"
            html += "<pre class=\"code\">" + cgi.escape(report.log) + "</pre>"
            html += "</li>"

      html += "</ul>"
      html += "</div>"

      html += "</body>"
      html += "</html>"

      f = open(report_file, "w+")
      if f:
         f.write(html)
         f.close()
         self._logger.logln("HTML report: " + report_file)

   def get_memc_version_string (self):
      args = [kMEMC, "--version"]
      memc = subprocess.Popen(args, shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      return memc.communicate()[0].decode()

   def print_summary (self):
      percent_failed = int(round(1.0 * len(self._failed_tests)/self._num_tests*100, 0))
      percent_passed = int(round(100-(1.0 * len(self._failed_tests)/self._num_tests)*100, 0))
      self._logger.logln("")
      self._logger.log_section("Summary")
      summary =  "   Tests run: " + str(self._num_tests) + " (100%)\n"
      summary += "Tests passed: " + str(self._num_tests - self._num_failed_tests).rjust(len(str(self._num_tests))) + " (" +  str(self._percent_passed_tests) + "%)\n"
      summary += "Tests failed: " + str(self._num_failed_tests).rjust(len(str(self._num_tests))) + " (" + str(self._percent_failed_tests) + "%)"
      self._logger.logln(summary)

      for report in self._reports:
         if report.status != "passed":
            self._logger.logln("              * " + report.name + " (" + report.reason + ")")

      if self._num_tests != self._num_passed_tests:
         self._logger.log_section("/!\ Please submit this report")
         self._logger.logln("You have stumbled upon some bugs that we would like to know about.")
         self._logger.logln("Please submit this report to\n>>> https://github.com/ThQ/memc/issues/new")
         self._logger.logln("")

   def read_file (self, path):
      contents = ""
      fin = open(path, "r")
      if fin:
         contents = fin.read()
         fin.close()
      return contents

   def run (self):
      self._logger.log_red("Black box test suite".center(80) + "\n", bold=True)

      uname = os.uname()
      self._logger.log_section("Environment")
      self._logger.logln("Platform".rjust(11) + ": " + sys.platform)
      self._logger.logln("System name".rjust(11) + ": " + uname[0])
      self._logger.logln("Node name".rjust(11) + ": " + uname[1])
      self._logger.logln("Release".rjust(11) + ": " + uname[2])
      self._logger.logln("Version".rjust(11) + ": " + uname[3])
      self._logger.logln("Machine".rjust(11) + ": " + uname[4])
      self._logger.logln("")

      self.discover_tests(kTEST_DIR)

      self._logger.log_section("Running tests")
      self._logger.logln("Executable".rjust(17) + ": " + kMEMC)
      self._logger.logln("Test directory".rjust(17) + ": " + kTEST_DIR)
      self._logger.logln("Reports directory".rjust(17) + ": " + kREPORT_DIR)
      self._logger.logln("Tests discovered".rjust(17) + ": " + str(self._num_tests))
      self._logger.logln("")

      self.run_tests()

      self._logger.logln("")

      if self._num_tests != 0:
         self._percent_failed_tests = round(self._num_failed_tests * 100 / self._num_tests, 1)
         self._percent_passed_tests = round(self._num_passed_tests * 100 / self._num_tests, 1)
      else:
         self._percent_failed_tests = 0
         self._percent_passed_tests = 0


   def run_tests (self):
      i = 1
      str_num_tests_len = len(str(self._num_tests))
      tests_per_line = 80 - str_num_tests_len * 2 - 3 - 1
      for test in self._tests:

         if (i-1) % tests_per_line == 0:
            progress = str(i).rjust(str_num_tests_len)
            progress += "-"
            progress += str(min(self._num_tests, i + tests_per_line - 1)).rjust(str_num_tests_len)

            self._logger.log("[" + progress + "] ")

         report = test.run()
         self._reports.append(report)

         if report.status == "passed":
            self._logger.log(".")
            self._num_passed_tests += 1
         elif report.status == "failed":
            self._logger.log_red("!", bold=True)
            self._num_failed_tests += 1
         else:
            self._logger.log_red("#", bold=True)
            self._num_failed_tests += 1

         if i % tests_per_line == 0:
            self._logger.log("\n")
         i += 1


runner = TestRunner()
runner.run()
runner.print_summary()
runner.dump_html_report(os.path.join(kREPORT_DIR, "memc-test-report.html"))

if runner._num_tests != runner._num_passed_tests:
   sys.exit(1)
