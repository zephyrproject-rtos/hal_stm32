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
   *Missing additional pins for SAI1_FS_A and SAI1_FS_B signals on STM32U3 serie
      - Add the SAI1_FS_A signal name on PB9 and PE4 in the appropriate U3 pinctrl file.
      - Add the SAI1_FS_B signal name on PE9 in the appropriate U3 pinctrl files.
      -Link: https://github.com/STMicroelectronics/STM32_open_pin_data/issues/15
      - Impacted files:
         dts/st/u3/stm32u375*-pinctrl.dtsi
         dts/st/u3/stm32u385*-pinctrl.dtsi

   *Rename "TIM3_REMAP1" on the pin "PB5" to "TIM3_REMAP2"
   of the following GPIO-STM32F103xx.xml files.
      - Impacted files:
         dts/st/f1/stm32f103r(8-b)tx-pinctrl.dtsi
