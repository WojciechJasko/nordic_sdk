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
        if 'Library' not in env['BUILDERS']: 
            env['lib'][target] = None
            return

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
            file            = os.path.basename(str(header))
            file_name, ext  = os.path.splitext(file)

            if 'CMock' not in env['BUILDERS']:
                env['cmock'][file_name] = None

            else:
                build_cmock = env.CMock(header)
                cmock       = env.Install('#cmock/', build_cmock)

                env['cmock'][file_name] = cmock[0]
                cmocks.append(cmock)

        return cmocks

    def addUnitTest(env, target, source):
        if 'UnitTest' not in env['BUILDERS']:
            return

        utest_result = env.UnitTest(target, source)

        utest = env.Install('#unit_test/', utest_result)
        # add alias to run all unit tests.
        env.Alias('unittests', utest)
        # make an alias to run the test in isolation from the rest of the tests.
        env.Alias(os.path.splitext(target)[0], utest)
        return utest

    def addHex(env, target, source, linker_file, lib = None):
        if 'Elf2Hex' not in env['BUILDERS']:
            return

        if not lib:
            lib = list()

        local_env = env.Clone()
        local_env.addLinkerScript(linker_file)

        source.append(env['startup'])
        elffile = local_env.Program(
            target  = target,
            source  = source,
            LIBS    = lib
        )
        hexfile = local_env.Elf2Hex(elffile)
        local_env.Depends(elffile, linker_file)
        return hexfile

    env.AddMethod(addLibrary,   "addLibrary")
    env.AddMethod(addSource,    "addSource")
    env.AddMethod(addCMock,     "addCMock")
    env.AddMethod(addUnitTest,  "addUnitTest")
    env.AddMethod(addHex,       "addHex")
