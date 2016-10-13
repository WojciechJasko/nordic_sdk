import os
from SCons.Builder import Builder

def generate(env, **kwargs):
    setup_tools(env)
    add_builders(env)
    add_methods(env)


def exists(env):
    return env.Detect('ruby')

def setup_tools(env):
    env['cmock'] = dict()

def add_builders(env):
    def cmock_emitter(target, source, env): 
        target  = list()
        for s in source:
            file            = os.path.basename(str(s))
            file_name, ext  = os.path.splitext(file)
            target.append('cmock_' + file_name + '.c')
            target.append('cmock_' + file_name + '.h')
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

def add_methods(env):
    def addCMock(env, header):
        build_cmock = env.CMock(header)
        cmock       = env.Install('cmock/', build_cmock)
        file_name   = os.path.splitext(str(build_cmock[0]))[0]

        env['cmock'][file_name] = cmock[0]
        return cmock

    env.AddMethod(addCMock,   "addCMock")
