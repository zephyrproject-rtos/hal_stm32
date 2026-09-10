STM32 PSA Crypto Drivers library
################################

Origin:
  STMicroelectronics
  Release in STMicroelectronics Github account is under construction

Status:
  Draft-v0.1

Purpose:
  This library interfaces TF PSA Crypto Drivers framework with the STM32
  HAL drivers for the various STM32 SoCs and product lines.

Description:
  This library provides TF PSA Crypto drivers dispatcher, configuration
  and drivers.

  config/ directory contains the TF PSA crypto drivers configuration file.

  dispatch/ directory contains the TF PSA crypto drivers dispatcher source
  and header files, generated from a TF PSA Crypto filetree modified to take
  into account the integration of the STM32 HAL PSA crypto drivers. TF PSA
  crypto dispatcher original implementation is provided under dual alternate
  licenses Apache v2.0 or GPL v2.0. There are release here under the
  Apache v2.0 license terms.

  include/ directory contains a STM32 HAL header wrapper file that includes
  the right HAL main header file accoring to the target SoC.

  stm32_psa_transparent_drivers/ directory contains the STM32 HAL PSA
  crypto drivers implementation.

Maintained-by:
  External

Licence:
  Apache-2.0

License Link:
  https://opensource.org/license/Apache-2.0
