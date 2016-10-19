import os

def generate(env, **kwargs):
    setup_tools(env)
    add_methods(env)


def exists(env):
    return 1


def setup_tools(env):
    env['lib']      = dict()
    env['source']   = dict()
    env['cmock']    = dict()


def add_methods(env):
    def addLibrary(env, target, source):
        build_library = env.Library(
            target = target,
            source = source
        )
        library = env.Install('#libs/' + env['name'], build_library)
        env['lib'][target] = library
        return library

    def addSource(env, target, source):
        env['source'][target] = source
        return source

    def addCMock(env, headers):
        cmocks = list()
        for header in headers:
            build_cmock = env.CMock(header)
            cmock       = env.Install('#cmock/', build_cmock)
            file_name   = os.path.splitext(str(build_cmock[0]))[0]

            env['cmock'][file_name] = cmock[0]
            cmocks.append(cmock)

        return cmocks

    def addUnitTest(env, target, source):
        utest_result = env.UnitTest(target, source)

        utest = env.Install('#unit_test/', utest_result)
        # add alias to run all unit tests.
        env.Alias('unittests', utest)
        # make an alias to run the test in isolation from the rest of the tests.
        env.Alias(os.path.splitext(target)[0], utest)
        return utest

    env.AddMethod(addLibrary,   "addLibrary")
    env.AddMethod(addSource,    "addSource")
    env.AddMethod(addCMock,     "addCMock")
    env.AddMethod(addUnitTest,  "addUnitTest")