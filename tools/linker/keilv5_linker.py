import os

from SCons.Builder  import Builder
from SCons.Node     import Python
from SCons.Node.FS  import File
from SCons.Defaults import processDefines

from jinja2 import PackageLoader, Environment

jinjaEnv = None

def generate(env, **kwargs):
    setup_environment(env)
    add_builders(env)


def exists(env):
    return 1


def setup_environment(env):
    global jinjaEnv
    jinjaEnv = Environment(loader                   = PackageLoader('keilv5_linker', 'templates'),
                           trim_blocks              = True,
                           lstrip_blocks            = True,
                           keep_trailing_newline    = True)

def add_builders(env):
    def keil5_linker_emitter(target, source, env):
        data                = env['mcu_config']
        data['sections']    = list()

        return (target, [Python.Value(data)])

    def keil5_linker_action(target, source, env):
        global jinjaEnv
        with open(str(target[0]), 'w+') as f:
            template = jinjaEnv.get_template('linker_template.sct')
            f.write(template.render(source[0].read()))

    env.Append(BUILDERS={
                            'Linker': Builder(
                                action  = keil5_linker_action,
                                emitter = keil5_linker_emitter,
                                suffix  = '.sct')
                        })
