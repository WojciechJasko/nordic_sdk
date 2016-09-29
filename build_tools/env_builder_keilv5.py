from env_builder import EnvBuilder

class EnvBuilderArmgcc(EnvBuilder):

    def default_update(self, env):
        super(EnvBuilderArmgcc, self).default_update(env)

        keil5_path = env["KEIL5"]

        env["CCFLAGS"].extend([
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

        env["LINKFLAGS"].extend([
                              "-mthumb",
                              "-mabi=aapcs",
                              "-Wl",
                              "--gc-sections",
                              "--specs=nano.specs",
                              "-lc",
                              "-lnosys"
                            ])

        env["CC"]           = keil5_path + "ARM\ARMCC\BIN\Armcc.Exe"
        env["CXX"]          = keil5_path + "ARM\ARMCC\BIN\Armcc.Exe"
        env["AS"]           = keil5_path + "ARM\ARMCC\BIN\Armasm.Exe"
        env["AR"]           = keil5_path + "ARM\ARMCC\BIN\ArmAr.Exe"
        env["LD"]           = keil5_path + "ARM\ARMCC\BIN\ArmLink.Exe"
        env["NM"]           = ""
        env["OBJDUMP"]      = keil5_path + "ARM\ARMCC\BIN\FromElf.Exe"
        env["OBJCOPY"]      = ""
        env["SIZE"]         = ""
        env["RANLIB"]       = ""
        env["PROGSUFFIX"]   = ".elf"

        env["ASFLAGS"]      = ""
        env["ASCOM"]        = " '$AS $ASFLAGS -o $TARGET $SOURCES'",


    def fpu_update(self, env, choice):
        super(EnvBuilderArmgcc, self).fpu_update(env, choice)

        if choice == 'hard':
            env["CCFLAGS"].extend([
                                  "--apcs=/hardfp",
                                  "--fpu=vfpv4_d16",
                                ])

        elif choice == 'soft':
            env["CCFLAGS"].extend([
                                  "--apcs=/softfp",
                                  "--fpu=softvfp"
                                ])

        else:
            raise Exception("Not supported fpu: {}".format(choice))


    def target_update(self, env, choice):
        super(EnvBuilderArmgcc, self).target_update(env, choice)

        if choice == 'cortex_m0':
            env["CCFLAGS"].extend([
                                  "--cpu=Cortex-M0"
                                ])

            env["ASFLAGS"].extend([
                                  "--cpu=Cortex-M0"
                                ])

            env["LINKFLAGS"].extend([
                                  "--cpu=Cortex-M0"
                                ])

        elif choice == 'cortex_m4':
            env["CCFLAGS"].extend([
                                  "--cpu=Cortex-M4"
                                ])

            env["ASFLAGS"].extend([
                                  "--cpu=Cortex-M4"
                                ])

            env["LINKFLAGS"].extend([
                                  "--cpu=Cortex-M4"
                                ])

        else:
            raise Exception("Not supported target: {}".format(choice))
