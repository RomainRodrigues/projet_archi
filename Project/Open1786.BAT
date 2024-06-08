SET PATH=C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\ProgramData\chocolatey\bin;C:\Program Files\PowerShell\7-preview\preview;C:\Program Files\PowerShell\7\;C:\Program Files\PuTTY\;C:\Users\rodri\AppData\Local\Microsoft\WindowsApps;C:\Users\rodri\AppData\Local\Programs\Microsoft VS Code\bin;C:\MinGW\bin;
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=Open1786
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmAsm" --Via ".\output\startup_lpc17xx._ia"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\system_lpc17xx.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_clkpwr.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_gpio.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_pinsel.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_timer.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_exti.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_nvic.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_ssp.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lpc17xx_i2c.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\main.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\ili_lcd_general.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\lcd_api.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\english_16x8.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\affichagelcd.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmCC" --Via ".\output\touch_panel.__i"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\ArmLink" --Via ".\Output\Project.lnp"
"C:\Keil_v5\ARM\ARM_Compiler_5.06u7\Bin\fromelf.exe" ".\Output\Project.axf" --i32combined --output ".\Output\Project.hex"
