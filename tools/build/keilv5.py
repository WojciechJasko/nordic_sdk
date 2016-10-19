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
    env['ENV']['KEIL5'] = 'C:\Keil_v5'
    assert env['ENV'].has_key('KEIL5'), "You need to specify Keil compiler path (KEIL5=<path>)"
    assert env.has_key('MCU'), "You need to specify processor (MCU=<cpu>)"
    assert env.has_key('BUILD_TYPE'), "You need to specify build type (BUILD_TYPE=<build_type>)"

    path = env.get('NORDIC_CONFIG', os.path.join(os.path.dirname(__file__), 'default_config.json'))
    with open(path, 'r') as f:
        global TARGETS
        TARGETS = json.load(f)


def setup_tools(env):
    for tool in ['gcc','g++','ar', 'gnulink', 'nasm']:
        env.Tool(tool)

    env.Replace(CC          = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\Armcc.Exe")
    env.Replace(CXX         = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\Armcc.Exe")
    env.Replace(AS          = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\Armasm.Exe")
    env.Replace(AR          = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\ArmAr.Exe")
    env.Replace(LD          = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\ArmLink.Exe")
    env.Replace(LINK        = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\ArmLink.Exe")
    env.Replace(NM          = "")
    env.Replace(OBJDUMP     = "")
    env.Replace(OBJCOPY     = env['ENV']['KEIL5'] + "\\ARM\\ARMCC\\BIN\\FromElf.Exe")
    env.Replace(RANLIB      = "")
    env.Replace(RANLIBCOM   = "")
    env.Replace(SIZE        = "")

    env.Replace(CCFLAGS     = "")
    env.Replace(LINKFLAGS   = "")
    env.Replace(ASFLAGS     = "")
    env.Replace(ARFLAGS     = "-r")
    env['PROGSUFFIX']   = '.axf'

    env['CCCOM']   = r'$CC $CFLAGS $CCFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -c -o $TARGET $SOURCES'
    env['LINKCOM'] = r'$LINK --libpath '+env['ENV']['KEIL5']+'\ARM\ARMCC\LIB $LINKFLAGS -o $TARGET $SOURCES $LIBS'
    env['ASCOM']   = r'$AS $ASFLAGS -o $TARGET $SOURCES'

    env['ASSUFFIXES'] = ['.s', '.asm', '.ASM']


def add_flags(env):
    # Common
    env.Append(CCFLAGS = [
                            "-O2",
                            "-g",
                            "--c99"
                        ])

    global TARGETS
    # Target
    if TARGETS[env['MCU']]['target'] == 'cortex_m0':
        env.Append(CCFLAGS = [
                                "--cpu=Cortex-M0"
                            ])

        env.Append(LINKFLAGS = [
                                "--cpu=Cortex-M0"
                            ])

        env.Append(ASFLAGS = [
                            "--cpu=Cortex-M0"
                        ])

    elif TARGETS[env['MCU']]['target'] == 'cortex_m4':
        env.Append(CCFLAGS = [
                                "--cpu=Cortex-M4"
                            ])

        env.Append(LINKFLAGS = [
                                "--cpu=Cortex-M4"
                            ])

        env.Append(ASFLAGS = [
                            "--cpu=Cortex-M4"
                        ])

    else:
        raise Exception("Not supported target: {}".format(TARGETS[env['MCU']]['target']))

    # FPU
    if TARGETS[env['MCU']]['fpu'] == 'hard':
        env.Append(CCFLAGS = [
                                "--fpu=vfpv4_d16"
                            ])

    elif TARGETS[env['MCU']]['fpu'] == 'soft':
        env.Append(CCFLAGS = [
                                "--fpu=softvfp"
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
                              "-O2",
                            ])

    else:
        raise Exception("Not supported build type: {}".format(env['BUILD_TYPE']))

def add_methods(env):
    def Hex(env, target, source, lib):
        #TODO: add asm and depends elffile from asmobjfile: Depends(elffile, asmobjfile)
        source.append(env['startup'])
        env['HEXSUFFIX'] = '.hex'
        elffile = env.Program(
            target = target,
            source = source,
            LIBS=lib
        )
        hexfile = env.Command(target, source, "$OBJCOPY --i32 $TARGET$PROGSUFFIX -o $TARGET$HEXSUFFIX")
        env.Depends( hexfile, elffile )
        return elffile

    env.AddMethod(Hex, "Hex")

