import os
import subprocess
import forge

MIMXRT1170EVK_ROOT = os.environ.get("MIMXRT1170EVK_ROOT", "")
LINK_SERVER = os.environ.get("LINK_SERVER", "")
ARM_GDB = os.path.join(os.environ.get("ARM_GCC_TOOLCHAIN_PATH", ""), 'arm-none-eabi-gdb')


class Core0Flasher():
  """
  Flashes core 0.
  """

  def __init__(self):
    pass

  def flash(self, application: str):
    print("Killing any existing LinkServers... ", end="", flush=True)
    args = ['pkill', 'LinkServer']
    subprocess.call(args)
    print(f"{forge.helpers.GREEN_CHECK}", flush=True)

    # NOTE: This hacky commented code doesn't appear necessary anymore, can delete it?
    # When I removed the ncacheable region form linker script and startup it was fixed.

    # # This part is kind of a hack. We need to reset the target first, otherwise if we flash with
    # # LinkServer right away, it will sometimes fail and the LinkServer does not appear to expose a
    # # command to reset the target directly. So we launch the GDB server and reset the target with
    # # GDB first, then flash in a separate command.
    # #
    # # Launch the gdb server in the background.
    # print("Launching GDB Server... ", end="", flush=True)
    # args = [
    #     LINK_SERVER,
    #     "gdbserver",
    #     "--no-boot",
    #     "MIMXRT1176xxxxx:MIMXRT1170-EVK",
    #     "--gdb-port",
    #     "2400",
    #     "-c",
    #     "cm7"]
    # gdb_server = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    # print(f"{forge.helpers.GREEN_CHECK}", flush=True)

    # # Connect gdb and reset the target.
    # print("Resetting the target with GDB... ", flush=True)
    # args = [
    #     ARM_GDB,
    #     "-x",
    #     os.path.join(MIMXRT1170EVK_ROOT, "scripts", 'gdb_reset_commands.txt')
    # ]
    # subprocess.check_call(args)
    # print(f"Reset complete {forge.helpers.GREEN_CHECK}", flush=True)

    # # Kill the GDB server.
    # print("Killing GDB Server... ", end="", flush=True)
    # gdb_server.terminate()
    # print(f"{forge.helpers.GREEN_CHECK}", flush=True)

    # Now use LinkServer to flash core0.
    print("Flashing... ", flush=True)
    args = [
        LINK_SERVER,
        "flash",
        "--no-boot",
        "MIMXRT1176xxxxx:MIMXRT1170-EVK",
        "load",
        application]
    subprocess.check_call(args)
    print(f"Flash complete {forge.helpers.GREEN_CHECK}", flush=True)
