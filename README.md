# Nordic open source SDK

see: https://github.com/thomasdavis/best-practices

Tested with compilers:
 - gcc-arm-none-eabi 5.4 q3 (Windows, Linux)
 - MDK-ARM Lite 5.21 (ARM Compiler 5.06 update 3 (build 300) (Windows)

### Directory Structure
```
Nordic_SDK/
+-- SConstruct
+-- build_tools
    +-- armgcc.py
    +-- keil5.py
    +-- default_config.json
+-- project_tools
    +-- templates
    ¦   +-- uvprojx.xml
    +-- Keil5Project.py
+-- test_tools
    +-- cmock
    +-- unity
    +-- cmock.py
    +-- unity.py
+-- core
+-- drivers
+-- examples
```
