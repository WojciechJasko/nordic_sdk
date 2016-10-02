import os
from SCons.Builder import Builder

def generate(env, **kwargs):
    add_builders(env)


def exists(env):
    return env.Detect('ruby')


def add_builders(env):
    def cmock_emitter(target, source, env): 
        target  = list()
        for s in source:
            file            = os.path.basename(str(s))
            file_name, ext  = os.path.splitext(file)
            target.append('cmock\cmock_' + file_name + '.h')
            target.append('cmock\cmock_' + file_name + '.c')
        return target, source

    def cmock_generator(source, target, env, for_signature):
        result  = 'ruby '
        result += os.path.join(os.path.dirname(__file__), 'cmock', 'lib', 'cmock.rb')
        result += ' '
        result += ' '.join([str(s) for s in source])
        result += ' --mock_path={}'.format(os.path.dirname(str(target[0])))
        result += ' --plugins=return_thru_ptr;ignore_arg;ignore;callback;array'
        result += ' --mock_prefix="cmock_"'
        return result

    env.Append(BUILDERS={
                            'CMock': Builder(
                                generator   = cmock_generator,
                                emitter     = cmock_emitter,
                                src_suffix  = '.h'),
                        })
