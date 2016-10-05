import os

env = Environment(
    ENV         = os.environ,
    MCU         = 'NRF52832',
    BUILD_TYPE  = 'release',
    tools       = ['default', 'armgcc', 'cmock', 'unity', 'Keil5Project'],
    toolpath    = ['build_tools', 'test_tools', 'project_tools'],
)


env.Append(CPPDEFINES = [
                        env['MCU']
                    ])

if env['BUILD_TYPE'] == "debug":
    env.Append(CPPDEFINES = [
                   "NRF_DEBUG",
                ])


path = '_build/'
env.VariantDir(path, 'core', duplicate=0)
env.SConscript(path + '/SConscript', exports=['env'])
