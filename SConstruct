import os

env = Environment(
    ENV         = os.environ,
    MCU         = 'NRF52832',
    BUILD_TYPE  = 'release',
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


print env.SConscript('core/SConscript',  exports=['env'], variant_dir='_build', duplicate=0)
