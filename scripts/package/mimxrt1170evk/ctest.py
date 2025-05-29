import os
import re
import mimxrt1170evk
import forge

# Pull in environment variables
SERIAL_DEVICE = os.environ.get("SERIAL_DEVICE")


def do(test_application: mimxrt1170evk.Core0Application):
  # Create the serial terminal.
  serial_terminal = forge.SerialTerminal(SERIAL_DEVICE, 115200)

  # Flash the test application.
  test_application.flash()

  # Analyze test output.
  suite_passed = True
  while True:
    # Read the next line from UART output.
    line = serial_terminal.readline()

    # Print the line so it is visible in ctest output.
    print(line)

    # If the line contains "ASSERT ERROR", stop the test and report the error.
    if "ASSERT ERROR" in line:
      forge.error("ASSERT ERROR encountered: " + line)

    # Check if any test case failed.
    if "\033[31mFAILED\033[0m" in line:
      suite_passed = False

    # Use regex to check for the summary line to determine if the test suite has completed.
    # The summary line always prints the number of passed tests.
    pattern = r"^\[\s+(\033\[32mPASSED\033\[0m|\033\[31mFAILED\033\[0m)\s+\]\s+(\d+)\s+test\(s\)\.$"
    match = re.match(pattern, line)
    if match:
      if suite_passed:
        return
      else:
        forge.error("Unit tests failed.")
