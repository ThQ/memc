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
         if match[0] != "D":
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
      else:
         if "must-not-compile" in self.options:
            if report.return_code == 1:
               report.status = "passed"
            elif report.return_code == 0:
               report.status = "failed"
         else:
            if report.return_code == 0:
               report.status = "passed"
            elif report.return_code == 1:
               report.status = "failed"

      if report.return_code != 0 and report.return_code != 1:
         report.status = "crashed"

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


class TestReport:
   def __init__ (self):
      self.source = ""
      self.return_code = 0
      self.log = ""
      self.path = ""
      self.name = ""
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
               html += "<a class=\"failed\">Failed</a>"

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
         self._logger.logln("HTML report written to " + report_file)

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
      summary += " - Failed: " + str(self._num_failed_tests) + " (" + str(self._percent_failed_tests) + "%)\n"
      summary += " - Passed: " + str(self._num_tests - self._num_failed_tests) + " (" +  str(self._percent_passed_tests) + "%)"
      summary += "\n"
      self._logger.logln(summary)

   def read_file (self, path):
      contents = ""
      fin = open(path, "r")
      if fin:
         contents = fin.read()
         fin.close()
      return contents

   def run (self):
      self.log_section("Running tests for `" + kMEMC + "'...")
      self._logger.logln("Test directory: " + kTEST_DIR)
      self._logger.logln("Reports directory: " + kREPORT_DIR)
      self._logger.logln("")

      self.discover_tests(kTEST_DIR)

      self._logger.logln(str(self._num_tests) + " tests discovered:")

      self.run_tests()

      if self._num_tests != 0:
         self._percent_failed_tests = round(self._num_failed_tests * 100 / self._num_tests, 1)
         self._percent_passed_tests = round(self._num_passed_tests * 100 / self._num_tests, 1)
      else:
         self._percent_failed_tests = 0
         self._percent_passed_tests = 0

   def run_tests (self):
      i = 1
      for test in self._tests:
         progress = str(i).rjust(len(str(self._num_tests))) + "/" + str(self._num_tests)

         log_ln = ("(" + progress + ") Running <" + test.name + ">").ljust(71, ".") + " "
         self._logger.log(log_ln)
         report = test.run()
         self._reports.append(report)

         if report.status == "passed":
            self._logger.logln("OK")
            self._num_passed_tests += 1
         elif report.status == "failed":
            self._logger.logln("FAILED")
            self._num_failed_tests += 1
         else:
            self._logger.logln("CRASHED")
            self._num_failed_tests += 1

         i += 1


runner = TestRunner()
runner.run()
runner.print_summary()
runner.dump_html_report(os.path.join(kREPORT_DIR, "memc-test-report.html"))

if runner._num_tests != runner._num_passed_tests:
    print("\n" + "=" * 80)
    print("")
    print("   Please submit this test report to")
    print("")
    print("      >>> https://github.com/ThQ/memc/issues/new")
    print("")
    print("   You have stumbled upon some bugs we'd like to know.\n")
    print("=" * 80 + "\n")
    sys.exit(1)
