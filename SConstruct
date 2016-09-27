import os
import json
from build_tools.env_updater import EnvUpdater

tools = ['gcc', 'g++', 'ar']

common_env = Environment(tools=tools,ENV = os.environ)

common_env['CCFLAGS']       = list()
common_env['LINKFLAGS']     = list()
common_env['CPPDEFINES']    = list()


toolchain_updater   = EnvUpdater("build_tools/config/armgcc")
common_updater      = EnvUpdater("build_tools/config/common")

with open('build_tools/envs.json', "r") as f:
    desc = json.load(f)

nrf52832_env = common_env.Clone()
toolchain_updater.update(nrf52832_env, desc['NRF52832'])
common_updater.update(nrf52832_env, {'build_type': 'debug'})
print nrf52832_env.Dump()