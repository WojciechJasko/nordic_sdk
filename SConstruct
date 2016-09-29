import os
import json
from build_tools.env_builder_armgcc import EnvBuilderArmgcc

tools = ['gcc', 'g++', 'ar']

with open('build_tools/envs.json', "r") as f:
    desc = json.load(f)

common_env = Environment(tools = tools, ENV = os.environ)

armgcc_builder = EnvBuilderArmgcc(common_env)

nrf52832_env = armgcc_builder.create(desc['NRF52832'])

nrf52832_env.VariantDir('build', 'core')
env = nrf52832_env
nrf52832_env.SConscript('build/SConscript', exports=['env'])


