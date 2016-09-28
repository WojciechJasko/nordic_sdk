import os
import logging

class EnvBuilder(object):
    SCONS_DEFAULTS = {
        'CC':          str(),
        'CXX':         str(),
        'AS':          str(),
        'AR':          str(),
        'LD':          str(),
        'NM':          str(),
        'OBJDUMP':     str(),
        'OBJCOPY':     str(),
        'SIZE':        str(),
        'RANLIB':      str(),
        'PROGSUFFIX':  str(),
        'CCFLAGS':     list(),
        'CFLAGS':      list(),
        'LINKFLAGS':   list(),
    }

    def __init__(self, env):
        self.env = env

        # Complite the missing keys in enviroment
        for key, value in EnvBuilder.SCONS_DEFAULTS.iteritems():
            if key not in self.env:
                env[key] = value


    def create(self, desc):
        # Create a copy
        new = self.env.Clone()

        self.default_update(new)

        if 'fpu' in desc:
            self.fpu_update(new, desc['fpu'])

        if 'target' in desc:
            self.target_update(new, desc['target'])

        if 'build_type' in desc:
            self.build_type_update(new, desc['build_type'])

        return new


    def build_type_update(self, env, choice):
        if choice == "debug":
            env["CCFLAGS"].extend([
                                  "-O0",
                                ])

            env["CPPDEFINES"].extend([
                           "NRF_DEBUG",
                        ])

        elif choice == "release":
            env["CCFLAGS"].extend([
                                  "-O3",
                                ])

        else:
            raise Exception("Not supported build type: {}".format(choice))


    def default_update(self, env):
        pass


    def fpu_update(self, env, choice):
        pass


    def target_update(self, env, choice):
        pass

