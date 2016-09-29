import os
import logging

from copy import deepcopy

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
        new         = self.env.Clone()
        local_desc  = deepcopy(desc)

        self.default_update(new)

        fpu = local_desc.pop('fpu', None)
        if fpu:
            self.fpu_update(new, fpu)

        target = local_desc.pop('target', None)
        if target:
            self.target_update(new, target)

        build_type = local_desc.pop('build_type', None)
        if build_type:
            self.build_type_update(new, build_type)

        for i in xrange(len(local_desc)):
            key, value = local_desc.popitem()

            if key in EnvBuilder.SCONS_DEFAULTS:
                if isinstance(value, list):
                    new[key].extend(value)

                else:
                    new[key] = value
            else:
                raise Exception("Not supported key {}".format(key))

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

        elif choice == "unit_test":
            pass

        else:
            raise Exception("Not supported build type: {}".format(choice))


    def default_update(self, env):
        pass


    def fpu_update(self, env, choice):
        pass


    def target_update(self, env, choice):
        pass

