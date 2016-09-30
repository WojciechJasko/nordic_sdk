import os
import json
import subprocess
from build_tools.env_builder_armgcc import EnvBuilderArmgcc

def _cmock_emitter(target, source, env): 
    # directory, file_name = os.path.split(str(target[0]))
    base    = str(target[0])
    target  = list()
    for s in source:
        file            = os.path.basename(str(s))
        file_name, ext  = os.path.splitext(file)
        target.append(base + '_cmock\cmock_' + file_name + '.h')
        target.append(base + '_cmock\cmock_' + file_name + '.c')
    return target, source

def _cmock_actions(target, source, env):
    directory = os.path.dirname(str(target[0]))

    args = list()
    args.append('ruby')
    args.append('test_tools/cmock/lib/cmock.rb')
    args.extend([str(s) for s in source])
    args.append('--mock_path={}'.format(directory))
    args.append('--plugins=return_thru_ptr;ignore_arg;ignore;callback;array')
    args.append('--mock_prefix="cmock_"')
    
    return subprocess.call(args)

tools = ['gcc', 'g++', 'ar']
bld = Builder(action        = _cmock_actions,
              src_suffix    = '.h',
              emitter       = _cmock_emitter)
common_env   = Environment(tools = tools, ENV = os.environ, BUILDERS = {'CMock' : bld})

with open('build_tools/envs.json', "r") as f:
    targets = json.load(f)

env_builders = {
    'armgcc': EnvBuilderArmgcc
}

for toolchain, env_builder in env_builders.iteritems():
    for name, target in targets.iteritems():
        env = env_builder.build(common_env, target)

        build_desc = {
            'target_name':  name,
            'toolchain':    toolchain,
            'build_type':   'release',
        }

        path = '_build/core/{target_name}/{toolchain}/{build_type}'.format(**build_desc)
        env.VariantDir(path, 'core', duplicate=0)
        env.SConscript(path + '/SConscript', exports=['env', 'build_desc'])
