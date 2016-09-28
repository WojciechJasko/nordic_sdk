from env_builder import EnvBuilder

class EnvBuilderArmgcc(EnvBuilder):

    def default_update(self, env):
        super(ArmGccEnvBuilder, self).method(env)

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

        env["CC"]           = "arm-none-eabi-gcc"
        env["CXX"]          = "arm-none-eabi-g++"
        env["AS"]           = "arm-none-eabi-as"
        env["AR"]           = "arm-none-eabi-ar"
        env["LD"]           = "arm-none-eabi-ld"
        env["NM"]           = "arm-none-eabi-nm"
        env["OBJDUMP"]      = "arm-none-eabi-objdump"
        env["OBJCOPY"]      = "arm-none-eabi-objcopy"
        env["SIZE"]         = "arm-none-eabi-size"
        env["RANLIB"]       = "arm-none-eabi-ranlib"
        env["PROGSUFFIX"]   = ".elf"


    def fpu_update(self, env, choice):
        super(ArmGccEnvBuilder, self).method(env, choice)

        if choice == 'hard':
            env["CCFLAGS"].extend([
                                  "-mfloat-abi=hard",
                                  "-mfpu=fpv4-sp-d16",
                                ])

        elif choice == 'soft':
            env["CCFLAGS"].extend([
                                  "-mfloat-abi=soft"
                                ])

        else:
            raise Exception("Not supported fpu: {}".format(choice))


    def target_update(self, env, choice):
        super(ArmGccEnvBuilder, self).method(env, choice)

        if choice == 'cortex_m0':
            env["CCFLAGS"].extend([
                                  "-mcpu=cortex-m0"
                                ])

            env["LINKFLAGS"].extend([
                                  "-mcpu=cortex-m0"
                                ])

        elif choice == 'cortex_m4':
            env["CCFLAGS"].extend([
                                  "-mcpu=cortex-m4"
                                ])

            env["LINKFLAGS"].extend([
                                  "-mcpu=cortex-m4"
                                ])

        else:
            raise Exception("Not supported target: {}".format(choice))
