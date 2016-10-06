import os

vars = Variables()
vars.AddVariables(
    EnumVariable('MCU',
                 'Set MCU',
                 'NRF52832',
                 allowed_values=('NRF52832', 'NRF51822')),
    EnumVariable('BUILD_TYPE',
                 'Set build type',
                 'release',
                 allowed_values=('release', 'debug')),
)


env = Environment(
    ENV         = os.environ,
    variables   = vars,
    tools       = ['armgcc', 'cmock', 'unity', 'keil5project'],
    toolpath    = ['build_tools', 'test_tools', 'project_tools'],
)


env.Append(CPPDEFINES = [
                        env['MCU']
                    ])

if env['BUILD_TYPE'] == "debug":
    env.Append(CPPDEFINES = [
                   "NRF_DEBUG",
                ])


core = env.SConscript('core/SConscript', exports='env', variant_dir='_build', duplicate=0)
env.Install('cmock',    core['cmocks'])
env.Install('libs',     core['library'])

env.SConscript('examples/SConscript', exports='env core')