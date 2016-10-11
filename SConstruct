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

# Setup Environment
env = Environment(
    ENV         = os.environ,
    variables   = vars,
    tools       = ['armgcc', 'cmock', 'unity'],
    toolpath    = ['build_tools', 'test_tools', 'project_tools'],
)

env.Append(CPPDEFINES = [
                        env['MCU']
                    ])

if env['BUILD_TYPE'] == "debug":
    env.Append(CPPDEFINES = [
                   "NRF_DEBUG",
                ])


# Build Core
core = env.SConscript('core/SConscript', exports='env', variant_dir='_build', duplicate=0)
env.Install('cmock',    core['cmocks'])
env.Install('libs',     core['library'])
env.Append( LIBS = core['library'])

env.SConscript('examples/SConscript', exports='env core')
