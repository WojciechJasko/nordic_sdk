import os

env = Environment(
    ENV         = os.environ,
    MCU         = 'NRF52832',
    tools       = ['armgcc', 'cmock', 'unity'],
    toolpath    = ['build_tools', 'test_tools'],
)

path = '_build/'
env.VariantDir(path, 'core', duplicate=0)
env.SConscript(path + '/SConscript', exports=['env'])
