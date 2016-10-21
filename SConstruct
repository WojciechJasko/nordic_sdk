import os

# Setup Command Line
AddOption('--mcu',
          dest      = 'MCU',
          default   = 'NRF51422',
          choices   = ['NRF52832', 'NRF51822', 'NRF51422'],
          help      = 'Set MCU type.')

AddOption('--build_type',
          dest      = 'BUILD_TYPE',
          default   = 'release',
          choices   = ['release', 'debug'],
          help      = 'Set build type.')

AddOption('--toolchain',
          dest      = 'TOOLCHAIN',
          default   = 'armgcc',
          action    = "append",
          choices   = ['armgcc', 'keilv5', 'unittest'],
          help      = 'Append toolchain type.')

# Create Environments
envs = list()

if 'armgcc' in GetOption('TOOLCHAIN'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'armgcc',
            type        = 'build',
            MCU         = GetOption('MCU'),
            BUILD_TYPE  = GetOption('BUILD_TYPE'),
            tools       = ['manager', 'armgcc_build', 'armgcc_linker'],
            toolpath    = ['tools', 'tools/build', 'tools/linkgen'],
        ))

if 'keilv5' in GetOption('TOOLCHAIN'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'keilv5',
            type        = 'build',
            MCU         = GetOption('MCU'),
            BUILD_TYPE  = GetOption('BUILD_TYPE'),
            tools       = ['manager', 'keilv5_build', 'keilv5_project', 'keilv5_linker'],
            toolpath    = ['tools', 'tools/build', 'tools/project', 'tools/linkgen'],
        ))

if 'unittest' in GetOption('TOOLCHAIN'):
    envs.append(
        Environment(
            ENV         = os.environ,
            name        = 'unittest',
            type        = 'unittest',
            MCU         = GetOption('MCU'),
            tools       = ['manager', 'unittest'],
            toolpath    = ['tools', 'tools/test'],
        ))

# Setup Environments
for env in envs:
    env.Append(CPPDEFINES = [
                            env['MCU']
                        ])

    if env['BUILD_TYPE'] == "debug":
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
