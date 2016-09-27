import os
import json
from build_tools.env_builder import EnvBuilder

tools = ['gcc', 'g++', 'ar']

common_env = Environment(tools=tools,ENV = os.environ)

common_env['CCFLAGS']       = list()
common_env['LINKFLAGS']     = list()
common_env['CPPDEFINES']    = list()


env_builder = EnvBuilder("build_tools/config")

with open('build_tools/envs.json', "r") as f:
    desc = json.load(f)

nrf52832_env = common_env.Clone()

print nrf52832_env.Dump()
print('')
print('')
print('')
env_builder.update(nrf52832_env, desc['NRF52832'])
print('')
print('')
print('')
print nrf52832_env.Dump()
# env_builder.dump()
