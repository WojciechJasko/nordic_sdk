import os
from SCons.Builder import Builder

def generate(env, **kwargs):
    add_builders(env)


def exists(env):
    return 1


def add_builders(env):
    def unity_emitter(target, source, env): 
        assert(len(source) == 1)
        assert(len(target) == 1)
        file    = str(target[0])
        target  = list()
        target.append(file + '_Runner.c')
        return target, source

    def unity_generator(source, target, env, for_signature):
        assert(len(source) == 1)
        assert(len(target) == 1)
        result  = 'ruby '
        result += os.path.join(os.path.dirname(__file__), 'unity', 'auto', 'generate_test_runner.rb')
        result += ' {} {}'.format(str(source[0]), str(target[0]))
        return result

    env.Append(BUILDERS={
                        'Unity': Builder(
                            generator   = unity_generator,
                            emitter     = unity_emitter,
                            src_suffix  = '.c'),
                        })
