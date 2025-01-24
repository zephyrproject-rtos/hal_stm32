*-pinctrl.dtsi generated files
##############################

Origin:
   Generated

Status:
   Generated using external database:
        STM32 Open Pin Data
        STM32Cube package pinouts files

Purpose:
   SoC package specific -pinctrl.dtsi files

Description:
   This directory contains *-pinctrl.dtsi files generated using generation
   script (available under scripts/genpinctrl) along with inputs from
    - STM32 Open Pin Data database.
    - STM32Cube package Device Family Pack (DFP) pinouts database
   Each file matches a STM32 SoC package and contains, for each pin of the
   package the exhaustive list of pinctrl configurations depending on its
   capabilities and the various pin configurations described in
   scripts/genpinctrl/stm32*-pinctrl-config.yaml files.
   New set of files could be generated based on:
   - new version of STM32 Open Pin Data / STM32 Cube DFP pinouts
   - new version of stm32*-pinctrl-config.yaml files

Dependencies:
    * STM32 Open Pin Data / STM32 Cube package DFP pinouts
    * Generation script available in current repo under scripts/genpinctrl
      and configuration files.

URL:
   https://github.com/STMicroelectronics/STM32_open_pin_data

Commit:
   d2ca9b5ed0b35ad3aa92e91984ec7addae58bf7e

Maintained-by:
   External

License:
   Generated files fall under license Apache-2.0

License Link:
   https://www.apache.org/licenses/LICENSE-2.0

Patch List:
   *Missing additional pins for SAI1_FS_A and SAI1_FS_B signals on STM32U3 serie
      - Add the SAI1_FS_A signal name on PB9 and PE4 in the appropriate U3 pinctrl file.
      -Link: https://github.com/STMicroelectronics/STM32_open_pin_data/issues/15
      - Impacted files:
         dts/st/u3/stm32u385rgtxq-pinctrl.dtsi
