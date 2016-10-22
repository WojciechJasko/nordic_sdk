import os

from SCons.Builder import Builder

def generate(env, **kwargs):
    setup_environment(env)
    setup_tools(env)
    add_flags(env)
    add_builders(env)
    add_methods(env)


def exists(env):
    return 1


def setup_environment(env):
    env['ENV']['KEIL5'] = 'C:\Keil_v5'


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

    env['CCCOM']   = r'$CC $CFLAGS $CCFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -c -o $TARGET $SOURCES'
    env['LINKCOM'] = r'$LINK --libpath '+env['ENV']['KEIL5']+'\ARM\ARMCC\LIB $LINKFLAGS -o $TARGET $SOURCES $LIBS'
    env['ASCOM']   = r'$AS $ASFLAGS -o $TARGET $SOURCES'

    env['ASSUFFIXES']   = ['.s', '.asm', '.ASM']
    env['LIBSUFFIX']    = '.lib'
    env['PROGSUFFIX']   = '.axf'
    env['HEXSUFFIX']    = '.hex'


def add_flags(env):
    # Common
    env.Append(CCFLAGS = [
                            "-g",
                            "--c99"
                        ])

    # Target
    if env['mcu_config']['cortex'] == 'M0':
        env.Append(CCFLAGS = [
                                "--cpu=Cortex-M0"
                            ])

        env.Append(LINKFLAGS = [
                                "--cpu=Cortex-M0"
                            ])

        env.Append(ASFLAGS = [
                            "--cpu=Cortex-M0"
                        ])

    elif env['mcu_config']['cortex'] == 'M4':
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
        raise Exception("Not supported target: {}".format(env['mcu_config']['cortex']))

    # FPU
    if env['mcu_config']['fpu'] == 'hard':
        env.Append(CCFLAGS = [
                                "--fpu=vfpv4_d16"
                            ])

    elif env['mcu_config']['fpu'] == 'soft':
        env.Append(CCFLAGS = [
                                "--fpu=softvfp"
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
                                action      = "$OBJCOPY --i32 $SOURCE -o $TARGET",
                                suffix      = env['HEXSUFFIX'],
                                src_suffix  = env['PROGSUFFIX'])
                        })

def add_methods(env):
    def addLinkerScript(env, source):
        env.Append(LINKFLAGS = '--scatter='+source[0].abspath)
        return source

    env.AddMethod(addLinkerScript,   "addLinkerScript")
