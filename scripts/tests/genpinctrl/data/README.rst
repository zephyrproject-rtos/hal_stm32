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

Generation:
   HAL1 based series are generated with scripts/genpinctrl/genpinctrl.py
   using the STM32 Open Pin Data repository and commit listed below.

   HAL2 based series are generated with scripts/genpinctrl/genpinctrl_hal2.py
   using STM32Cube package DFP pinout files. The STM32Cube package URL and
   commit used to resolve each DFP repository and commit are documented in the
   corresponding stm32cube/*/README file.

URL:
   https://github.com/STMicroelectronics/STM32_open_pin_data

Commit:
   TEST

Maintained-by:
   External

License:
   Generated files fall under license Apache-2.0

License Link:
   https://www.apache.org/licenses/LICENSE-2.0

Patch List:
   None
