import os
import json
from build_tools.env_builder_armgcc import EnvBuilderArmgcc

tools = ['gcc', 'g++', 'ar']

common_env   = Environment(tools = tools, ENV = os.environ)

with open('build_tools/envs.json', "r") as f:
    targets = json.load(f)

env_builders = {
    'armgcc': EnvBuilderArmgcc
}

for toolchain, env_builder in env_builders.iteritems():
    for name, target in targets.iteritems():
        env = env_builder.build(common_env, target)

        path = 'build/core/{target_name}/{toolchain}/{build_type}'.format(target_name    = name,
                                                                          toolchain      = toolchain,
                                                                          build_type     = 'release')
        env.VariantDir(path, 'core', duplicate=0)
        env.SConscript(path + '/SConscript', exports=['env'])
