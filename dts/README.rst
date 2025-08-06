*-pinctrl.dtsi generated files
##############################

Origin:
   Generated

Status:
   Generated using STM32 Open Pin Data

Purpose:
   SoC package specific -pintrl.dtsi files

Description:
   This directory contains *-pcintrl.dtsi files generated using generation
   script (available under scripts/genpinctrl) along with inputs from
   STM32 Open Pin Data database.
   Each file matches a STM32 SoC package and contains, for each pin of the
   package the exhaustive list of pinctrl configurations depending on its
   capabilities and the various pin configurations described in
   scripts/genpinctrl/stm32*-pinctrl-config.yaml files.
   New set of files could be generated based on:
   - new version of STM32 Open Pin Data
   - new version of stm32*-pinctrl-config.yaml files

Dependencies:
    * STM32 Open Pin Data
    * Generation script available in current repo under scripts/genpinctrl
      and configuration files.

URL:
   https://github.com/STMicroelectronics/STM32_open_pin_data

Commit:
   5e641448dc7df619ee46bb0c91796b7626005929

Maintained-by:
   External

License:
   Generated files fall under license Apache-2.0

License Link:
   https://www.apache.org/licenses/LICENSE-2.0

Patch List:
   None