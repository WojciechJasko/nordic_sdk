import os
import subprocess
from SCons.Builder import Builder

COMMON_SRC = list()

def generate(env, **kwargs):
    setup_tools(env)
    add_methods(env)


def exists(env):
    return 1


def setup_tools(env):
    for tool in ['gcc', 'gnulink', 'unity', 'cmock']:
        env.Tool(tool)

    directory   = os.path.dirname(__file__)
    unity_path  = os.path.join(directory, 'unity', 'src')
    cmock_path  = os.path.join(directory, 'cmock', 'src')
    env.Append(CPPPATH=[unity_path, cmock_path, '#cmock'])

    global COMMON_SRC
    COMMON_SRC.append(os.path.join(unity_path, 'unity.c'))
    COMMON_SRC.append(os.path.join(cmock_path, 'cmock.c'))


def add_methods(env):
    def UnitTest(env, target, source):
        app = source[0].abspath
        with open(target[0].abspath, 'w+') as f:
            subprocess.call(app, stdout=f)

    def addUnitTest(env, target, source, *args, **kwargs):
        source_list = list()
        source_list.append(source)

        global COMMON_SRC
        source_list.append(COMMON_SRC)

        source_list.append(target)

        unity = env.Unity(target)
        source_list.append(unity)

        name    = os.path.splitext(target)[0]
        program = env.Program(target=name, source = source_list, *args, **kwargs)
        utest   = env.UnitTest(program)

        # add alias to run all unit tests.
        env.Alias('unittests', utest)
        # make an alias to run the test in isolation from the rest of the tests.
        env.Alias(str(program[0]), utest)
        return utest

    env.AddMethod(UnitTest,     "UnitTest")
    env.Append(BUILDERS={
                        'UnitTest': Builder(
                            action   = UnitTest,
                            suffix = '.result',
                            ),
                    })
    env.AddMethod(addUnitTest, "addUnitTest")