import os
import json
from build_tools.env_builder_armgcc import EnvBuilderArmgcc

tools = ['gcc', 'g++', 'ar']

common_env = Environment(tools = tools, ENV = os.environ)

armgcc_builder = EnvBuilderArmgcc(common_env)

with open('build_tools/envs.json', "r") as f:
    desc = json.load(f)

nrf52832_env = armgcc_builder.create(desc)
print nrf52832_env.Dump()