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

# Create Environments
armgcc_env = Environment(
    ENV         = os.environ,
    name        = 'armgcc',
    type        = 'build',
    variables   = vars,
    tools       = ['armgcc'],
    toolpath    = ['build_tools'],
)

keilv5_env = Environment(
    ENV         = os.environ,
    name        = 'keilv5',
    type        = 'build',
    variables   = vars,
    tools       = ['keilv5'],
    toolpath    = ['build_tools'],
)

unittest_env = Environment(
    ENV         = os.environ,
    name        = 'unittest',
    type        = 'unittest',
    variables   = vars,
    tools       = ['unittest'],
    toolpath    = ['test_tools'],
)

envs = [armgcc_env, keilv5_env, unittest_env]

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
    SConscript('core/SConscript', exports='env', variant_dir='_build/core/' + env['name'], duplicate=0)

    # SConscript('boards/SConscript', exports='env', variant_dir='_build/boards/' + env['name'], duplicate=0)

    # SConscript('examples/SConscript', exports='env', variant_dir='_build/examples/' + env['name'], duplicate=0)

