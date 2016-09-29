import os
import logging

from copy import deepcopy

class EnvBuilder(object):
    SCONS_DEFAULTS = {
        'CC':           str(),
        'CXX':          str(),
        'AS':           str(),
        'AR':           str(),
        'LD':           str(),
        'NM':           str(),
        'OBJDUMP':      str(),
        'OBJCOPY':      str(),
        'SIZE':         str(),
        'RANLIB':       str(),
        'PROGSUFFIX':   str(),
        'CCFLAGS':      list(),
        'CFLAGS':       list(),
        'CPPDEFINES':   list(),
        'LINKFLAGS':    list(),
    }

    @classmethod
    def build(cls, env, desc):
        # Create a copy
        new_env     = env.Clone()
        local_desc  = deepcopy(desc)

        # Complite the missing keys in enviroment
        for key, value in EnvBuilder.SCONS_DEFAULTS.iteritems():
            if key not in new_env:
                new_env[key] = value

        # Builder specific
        cls.default_update(new_env)

        # FPU support
        fpu = local_desc.pop('fpu', None)
        if fpu:
            cls.fpu_update(new_env, fpu)

        # Core support
        target = local_desc.pop('target', None)
        if target:
            cls.target_update(new_env, target)

        # Build type support
        build_type = local_desc.pop('build_type', None)
        if build_type:
            cls.build_type_update(new_env, build_type)

        # Miscellaneous
        for i in xrange(len(local_desc)):
            key, value = local_desc.popitem()

            if key in EnvBuilder.SCONS_DEFAULTS:
                if isinstance(value, list):
                    new_env[key].extend(value)

                else:
                    new_env[key] = value
            else:
                raise Exception("Not supported key {}".format(key))

        return new_env


    @classmethod
    def default_update(cls, env):
        pass


    @classmethod
    def build_type_update(cls, env, choice):
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


    @classmethod
    def fpu_update(cls, env, choice):
        pass


    @classmethod
    def target_update(cls, env, choice):
        pass
