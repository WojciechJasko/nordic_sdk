import os

# Setup Command Line
vars = Variables()
vars.AddVariables(
    EnumVariable('MCU',
                 'Set MCU',
                 'NRF51422',
                 allowed_values=('NRF52832', 'NRF51822', 'NRF51422')),
    EnumVariable('BUILD_TYPE',
                 'Set build type',
                 'release',
                 allowed_values=('release', 'debug')),
)

unknown = vars.UnknownVariables()
if unknown:
    print "Unknown variables:", unknown.keys()
    Exit(1)


# Create Environments
armgcc_env = Environment(
    ENV         = os.environ,
    name        = 'armgcc',
    type        = 'build',
    variables   = vars,
    tools       = ['manager', 'armgcc_build'],
    toolpath    = ['tools', 'tools/build'],
)

keilv5_env = Environment(
    ENV         = os.environ,
    name        = 'keilv5',
    type        = 'build',
    variables   = vars,
    tools       = ['manager', 'keilv5_build', 'keilv5_project'],
    toolpath    = ['tools', 'tools/build', 'tools/project'],
)

unittest_env = Environment(
    ENV         = os.environ,
    name        = 'unittest',
    type        = 'unittest',
    variables   = vars,
    tools       = ['manager', 'unittest'],
    toolpath    = ['tools', 'tools/test'],
)

envs = [keilv5_env]

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
                exports     = 'env',
                variant_dir ='_build/core/{}/{}/{}'.format(env['name'], env['MCU'], env['BUILD_TYPE']),
                duplicate   = 0)
    SConscript('examples/SConscript',
                exports='env')
