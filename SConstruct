import os
import json

# Setup Command Line
AddOption('--mcu',
          dest='mcu_with_package',
          default   = ['nrf51422_xxAC'],
          choices   = ['nrf51422_xxAA',
                       'nrf51422_xxAB',
                       'nrf51422_xxAC',
                       'nrf51822_xxAA',
                       'nrf51822_xxAB',
                       'nrf51822_xxAC',
                       'nRF52832_xxAA'],
          help      = 'Set mcu type.')

AddOption('--build_type',
          default   = 'release',
          choices   = ['release', 'debug'],
          help      = 'Set build type.')

AddOption('--toolchain',
          default   = ['keilv5'],
          action    = "append",
          choices   = ['armgcc', 'keilv5', 'unittest'],
          help      = 'Append toolchain type.')

path = os.path.join(Dir("#").abspath, 'mcu_config.json')
with open(path, 'r') as f:
    mcu_config = json.load(f)

# Create Environments
envs = list()
for toolchain in GetOption('toolchain'):
    for mcu_with_package in GetOption('mcu_with_package'):
        tools = list()
        if toolchain == 'armgcc':
            tools = ['manager', 'armgcc_build', 'armgcc_linker']

        elif toolchain == 'keilv5':
            tools = ['manager', 'keilv5_build', 'keilv5_project', 'keilv5_linker']

        elif toolchain == 'unittest':
            tools = ['manager', 'unittest']

        mcu = mcu_with_package[:-5]
        env = Environment(
                ENV         = os.environ,
                name        = toolchain,
                mcu         = mcu,
                mcu_config  = mcu_config[mcu_with_package],
                build_type  = GetOption('build_type'),
                tools       = tools,
                toolpath    = ['tools', 'tools/build', 'tools/project', 'tools/linker', 'tools/test'],
            )

        # Setup Environment
        env.Append(CPPDEFINES = env['mcu'].upper())

        if env['build_type'] == "debug":
            env.Append(CPPDEFINES = "NRF_DEBUG")

        envs.append(env)


# Build Core
for env in envs:
    SConscript('core/SConscript',
               exports      = 'env',
               variant_dir  = '_build/core/' + env['name'],
               duplicate    = 0)
    SConscript('examples/SConscript',
                exports     = 'env')
