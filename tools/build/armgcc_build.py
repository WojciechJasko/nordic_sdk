import os

from SCons.Builder import Builder


def generate(env, **kwargs):
    setup_tools(env)
    add_flags(env)
    add_builders(env)
    add_methods(env)


def exists(env):
    return 1


def setup_tools(env):
    for tool in ['gcc','g++','ar', 'gnulink']:
        env.Tool(tool)

    env.Replace(CC      = "arm-none-eabi-gcc")
    env.Replace(CXX     = "arm-none-eabi-g++")
    env.Replace(AS      = "arm-none-eabi-as")
    env.Replace(AR      = "arm-none-eabi-ar")
    env.Replace(LD      = "arm-none-eabi-ld")
    env.Replace(NM      = "arm-none-eabi-nm")
    env.Replace(OBJDUMP = "arm-none-eabi-objdump")
    env.Replace(OBJCOPY = "arm-none-eabi-objcopy")
    env.Replace(RANLIB  = "arm-none-eabi-ranlib")
    env.Replace(SIZE    = "arm-none-eabi-size")
    env['PROGSUFFIX']   = '.elf'
    env['HEXSUFFIX']    = '.hex'


def add_flags(env):
    # Common
    env.Append(CCFLAGS = [
                            "-mthumb",
                            "-mabi=aapcs",
                            "-Wall",
                            "-Werror",
                            "-g3",
                            "-ffunction-sections",
                            "-fdata-sections",
                            "-fno-strict-aliasing",
                            "-fno-builtin",
                            "--short-enums",
                            "-MP",
                            "-MD"
                        ])

    env.Append(LINKFLAGS = [
                            "-mthumb",
                            "-mabi=aapcs",
                            #"-Wl",
                            #"--gc-sections",
                            "--specs=nano.specs",
                            "-lc",
                            "-lnosys"
                        ])

    # Target
    if env['mcu_config']['cortex'] == 'M0':
        env.Append(CCFLAGS = [
                                "-mcpu=cortex-m0"
                            ])

        env.Append(LINKFLAGS = [
                                "-mcpu=cortex-m0"
                            ])

    elif env['mcu_config']['cortex'] == 'M4':
        env.Append(CCFLAGS = [
                                "-mcpu=cortex-m4"
                            ])

        env.Append(LINKFLAGS = [
                                "-mcpu=cortex-m4"
                            ])

    else:
        raise Exception("Not supported target: {}".format(env['mcu_config']['cortex']))

    # FPU
    if env['mcu_config']['fpu'] == 'hard':
        env.Append(CCFLAGS = [
                                "-mfloat-abi=hard",
                                "-mfpu=fpv4-sp-d16",
                            ])

    elif env['mcu_config']['fpu'] == 'soft':
        env.Append(CCFLAGS = [
                                "-mfloat-abi=soft"
                            ])

    else:
        raise Exception("Not supported fpu: {}".format(env['mcu_config']['fpu']))

    # Build Type
    if env['build_type'] == "debug":
        env.Append(CCFLAGS = [
                              "-O0",
                            ])

    elif env['build_type'] == "release":
        env.Append(CCFLAGS = [
                              "-O3",
                            ])

    else:
        raise Exception("Not supported build type: {}".format(env['build_type']))


def add_builders(env):
    env.Append(BUILDERS={
                            'Elf2Hex': Builder(
                                action      = "$OBJCOPY -O ihex $SOURCE $TARGET",
                                suffix      = env['HEXSUFFIX'],
                                src_suffix  = env['PROGSUFFIX'])
                        })

def add_methods(env):
    def addLinkerScript(env, source):
        env.Append(LINKFLAGS = '-T'+source[0].abspath)
        return source

    env.AddMethod(addLinkerScript,   "addLinkerScript")
