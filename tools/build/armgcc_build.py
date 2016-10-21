import os
import json

from SCons.Builder import Builder

TARGETS     = None

def generate(env, **kwargs):
    setup_environment(env)
    setup_tools(env)
    add_flags(env)
    add_builders(env)
    add_methods(env)


def exists(env):
    return 1


def setup_environment(env):
    path = env.get('NORDIC_CONFIG', os.path.join(os.path.dirname(__file__), 'default_config.json'))
    with open(path, 'r') as f:
        global TARGETS
        TARGETS = json.load(f)


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

    global TARGETS
    # Target
    if TARGETS[env['MCU']]['target'] == 'cortex_m0':
        env.Append(CCFLAGS = [
                                "-mcpu=cortex-m0"
                            ])

        env.Append(LINKFLAGS = [
                                "-mcpu=cortex-m0"
                            ])

    elif TARGETS[env['MCU']]['target'] == 'cortex_m4':
        env.Append(CCFLAGS = [
                                "-mcpu=cortex-m4"
                            ])

        env.Append(LINKFLAGS = [
                                "-mcpu=cortex-m4"
                            ])

    else:
        raise Exception("Not supported target: {}".format(TARGETS[env['MCU']]['target']))

    # FPU
    if TARGETS[env['MCU']]['fpu'] == 'hard':
        env.Append(CCFLAGS = [
                                "-mfloat-abi=hard",
                                "-mfpu=fpv4-sp-d16",
                            ])

    elif TARGETS[env['MCU']]['fpu'] == 'soft':
        env.Append(CCFLAGS = [
                                "-mfloat-abi=soft"
                            ])

    else:
        raise Exception("Not supported fpu: {}".format(TARGETS[env['MCU']]['fpu']))

    # Build Type
    if env['BUILD_TYPE'] == "debug":
        env.Append(CCFLAGS = [
                              "-O0",
                            ])

    elif env['BUILD_TYPE'] == "release":
        env.Append(CCFLAGS = [
                              "-O3",
                            ])

    else:
        raise Exception("Not supported build type: {}".format(env['BUILD_TYPE']))

    # MCU description
    env['MCU_FLASHADDR'] = TARGETS[env['MCU']]['flash_addr']
    env['MCU_FLASHSIZE'] = TARGETS[env['MCU']]['flash_size']
    env['MCU_RAMADDR'] = TARGETS[env['MCU']]['ram_addr']
    env['MCU_RAMSIZE'] = TARGETS[env['MCU']]['ram_size']


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
