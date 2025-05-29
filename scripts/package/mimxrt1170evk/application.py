import forge
import mimxrt1170evk


class Core0Application(forge.Application):
  """
  Provides commands for a mimxrt1170evk:core0 application. The cmake build preset must be a cm7
  variant (e.g. cm7-debug).
  """

  def __init__(self, preset_application: str):
    super().__init__(preset_application)
    if not self.preset_name.startswith("cm7"):
      forge.error(f"Core0 is cortex-m7 architecture, preset<{self.preset_name}> is not.")

  def run(self):
    forge.error("The run() method is not supported, use flash().")

  def flash(self):
    flasher = mimxrt1170evk.Core0Flasher()
    flasher.flash(self.application_fullfile)

  def debug(self):
    debugger = mimxrt1170evk.Mimxrt1170Debugger()
    debugger.generate_core0(self.application_fullfile)


class Core1Application(forge.Application):
  """
  Provides commands for a mimxrt1170evk:core1 application. The cmake build preset must be a cm7
  variant (e.g. cm7-debug).
  """

  def __init__(self, preset_application: str):
    super().__init__(preset_application)
    if not self.preset_name.startswith("cm4"):
      forge.error(f"Core1 is cortex-m4 architecture, preset<{self.preset_name}> is not.")

  def run(self):
    forge.error("The run() method is not supported, use flash().")

  def debug(self):
    debugger = mimxrt1170evk.Mimxrt1170Debugger()
    debugger.generate_core1(self.application_fullfile)
