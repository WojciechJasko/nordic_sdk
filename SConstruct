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
                 allowed_values=('release', 'debug'))
)


env = Environment(
    ENV         = os.environ,
    variables   = vars,
    tools       = ['armgcc', 'cmock', 'unity', 'Keil5Project'],
    toolpath    = ['build_tools', 'test_tools', 'project_tools'],
)


env.Append(CPPDEFINES = [
                        env['MCU']
                    ])

if env['BUILD_TYPE'] == "debug":
    env.Append(CPPDEFINES = [
                   "NRF_DEBUG",
                ])


env.VariantDir('_build/libs', 'core', duplicate=0)
env.SConscript('_build/libs/SConscript', exports=['env'])

# env.VariantDir('_build/cmock', 'core', duplicate=0)
# env.SConscript('_build/cmock/SConscript', exports=['env'])