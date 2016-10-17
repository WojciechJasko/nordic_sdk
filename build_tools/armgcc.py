import os
import json

from SCons.Builder import Builder

TARGETS     = None
compilers   = ["arm-none-eabi-gcc", "arm-none-eabi-g++"]

def generate(env, **kwargs):
    setup_environment(env)
    setup_tools(env)
    add_flags(env)
    add_methods(env)


def exists(env):
    return env.Detect(env.get('CC', compilers))


def setup_environment(env):
    assert env.has_key('MCU'), "You need to specify processor (MCU=<cpu>)"
    assert env.has_key('BUILD_TYPE'), "You need to specify build type (BUILD_TYPE=<build_type>)"

    path = env.get('NORDIC_CONFIG', os.path.join(os.path.dirname(__file__), 'default_config.json'))
    with open(path, 'r') as f:
        global TARGETS
        TARGETS = json.load(f)


def setup_tools(env):
    for tool in ['gcc','g++','ar', 'gnulink']:
        env.Tool(tool)

    env['lib'] = list()

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


def add_methods(env):
    def Hex(env, target, source, lib):
        env['HEXSUFFIX'] = '.hex'
        source.append(TARGETS[env['MCU']]['startup']['armgcc'])
        elffile = env.Program(
            target=target,
            source = source,
            LIBS=lib
        )
        hexfile = env.Command(target, source, "$OBJCOPY -O ihex $TARGET$PROGSUFFIX $TARGET$HEXSUFFIX")
        env.Depends( hexfile, elffile )
        return elffile

    def addLibrary(env, target, source):
        build_library = env.Library(
            target = target,
            source = source
        )
        library = env.Install('#libs/' + env['name'], build_library)
        env['lib'].append(library)
        return library

    env.AddMethod(Hex,          "Hex")
    env.AddMethod(addLibrary,   "addLibrary")

