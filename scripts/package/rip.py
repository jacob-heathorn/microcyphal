# #!/usr/bin/env python3
# #
# # Deployment tool.

# import argparse
# import shutil
# import os
# import mimxrt1170evk
# import forge


# PROJECT_ROOT = os.environ.get("PROJECT_ROOT", "")
# MCUX_SOC_SVD_ROOT = os.environ.get("MCUX_SOC_SVD_ROOT", "")
# SERIAL_DEVICE = os.environ.get("SERIAL_DEVICE", "")


# def main():
#   parser = argparse.ArgumentParser(description="Process mimxrt1170evk args.")
#   parser.add_argument('-t', '--ctest', type=str, help='Run ctest with <preset:application>')
#   parser.add_argument('-f0', '--flash_core_0', type=str, help='Flash core 0 <preset:application>')
#   parser.add_argument('-d0', '--debug_core_0', type=str, help='Debug core 0 <preset:application>')
#   parser.add_argument('-d1', '--debug_core_1', type=str, help='Debug core 1 <preset:application>')
#   parser.add_argument('-c', '--clean', action='store_true', help='Clean bin/ directories')
#   parser.add_argument('-s', '--serial', action='store_true', help='Launch serial terminal')
#   parser.add_argument(
#       '-g0',
#       '--generate_core_0',
#       action='store_true',
#       help='Generate core0 (cm4) svd registers')
#   parser.add_argument(
#       '-g1',
#       '--generate_core_1',
#       action='store_true',
#       help='Generate core 1 (cm7) svd register')
#   args = parser.parse_args()

#   # Do serial terminal.
#   if args.serial:
#     serial_terminal = forge.SerialTerminal(SERIAL_DEVICE, 115200)
#     serial_terminal.read_background()

#   # Do clean
#   if args.clean:
#     shutil.rmtree(os.path.join(PROJECT_ROOT, '.bin'), ignore_errors=True)
#     forge.remove_file(os.path.join(PROJECT_ROOT, '.vscode', 'launch.json'))
#     forge.remove_file(os.path.join(PROJECT_ROOT, '.vscode', 'tasks.json'))

#   # Do flash (Core 0 only)
#   if args.flash_core_0:
#     mimxrt1170evk.Core0Application(args.flash_core_0).flash()

#   # Do ctest (Core 0 only)
#   if args.ctest:
#     mimxrt1170evk.ctest.do(mimxrt1170evk.Core0Application(args.ctest))

#   # Do debug
#   if args.debug_core_0:
#     mimxrt1170evk.Core0Application(args.debug_core_0).debug()
#   if args.debug_core_1:
#     mimxrt1170evk.Core1Application(args.debug_core_1).debug()

#   # Do generate core 0 (cm4) registers.
#   if args.generate_core_0:
#     file = os.path.join(MCUX_SOC_SVD_ROOT, 'MIMXRT1176', 'MIMXRT1176_cm4.xml')
#     output_dir = os.path.join(PROJECT_ROOT, 'firmware', 'cm4', 'registers', 'codegen')
#     svd_parser_wrapper = forge.SVDParserWrapper(file, output_dir)
#     svd_parser_wrapper.generate()

#   # Do generate core 1 (cm7) registers.
#   if args.generate_core_1:
#     file = os.path.join(MCUX_SOC_SVD_ROOT, 'MIMXRT1176', 'MIMXRT1176_cm7.xml')
#     output_dir = os.path.join(PROJECT_ROOT, 'firmware', 'cm7', 'registers', 'codegen')
#     svd_parser_wrapper = forge.SVDParserWrapper(file, output_dir)
#     svd_parser_wrapper.generate()


# if __name__ == '__main__':
#   main()
