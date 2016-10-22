import os
import json

# Setup Command Line
AddOption('--mcu',
          default   = 'NRF51422',
          choices   = ['NRF52832', 'NRF51822', 'NRF51422'],
          help      = 'Set mcu type.')

AddOption('--build_type',
          default   = 'release',
          choices   = ['release', 'debug'],
          help      = 'Set build type.')

AddOption('--toolchain',
          default   = 'armgcc',
          action    = "append",
          choices   = ['armgcc', 'keilv5', 'unittest'],
          help      = 'Append toolchain type.')

path = os.path.join(Dir("#").abspath, 'mcu_config.json')
with open(path, 'r') as f:
    mcu_config = json.load(f)[GetOption('mcu')]

# Create Environments
envs = list()

# for toolchain in GetOption('toolchain'):
#     for mcu in GetOption('mcu'):
#         if toolchain == 'unittest':
#             type = 'unittest'
#         else:
#             type = 'build'


if 'armgcc' in GetOption('toolchain'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'armgcc',
            mcu         = GetOption('mcu'),
            mcu_config  = mcu_config,
            build_type  = GetOption('build_type'),
            tools       = ['manager', 'armgcc_build', 'armgcc_linker'],
            toolpath    = ['tools', 'tools/build', 'tools/linker'],
        ))

if 'keilv5' in GetOption('toolchain'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'keilv5',
            mcu         = GetOption('mcu'),
            mcu_config  = mcu_config,
            build_type  = GetOption('build_type'),
            tools       = ['manager', 'keilv5_build', 'keilv5_project', 'keilv5_linker'],
            toolpath    = ['tools', 'tools/build', 'tools/project', 'tools/linker'],
        ))

if 'unittest' in GetOption('toolchain'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'unittest',
            mcu         = GetOption('mcu'),
            mcu_config  = mcu_config,
            tools       = ['manager', 'unittest'],
            toolpath    = ['tools', 'tools/test'],
        ))

# Setup Environments
for env in envs:
    env.Append(CPPDEFINES = [
                            env['mcu']
                        ])

    if env['build_type'] == "debug":
        env.Append(CPPDEFINES = [
                       "NRF_DEBUG",
                    ])

# Build Core
for env in envs:
    SConscript('core/SConscript',
               exports      = 'env',
               variant_dir  = '_build/core/' + env['name'],
               duplicate    = 0)
    SConscript('examples/SConscript',
                exports     = 'env')
