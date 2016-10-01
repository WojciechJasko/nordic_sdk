from env_builder import EnvBuilder

class EnvBuilderArmgcc(EnvBuilder):

    def default_update(self, env):
        super(EnvBuilderArmgcc, self).default_update(env)

        keil5_path = env["KEIL5"]

        env["CCFLAGS"].extend([
                              "-O2"
                              "-g",
                            ])

        env['CC']           = keil5_path + "ARMCC\\BIN\\Armcc.Exe"
        env['CXX']          = keil5_path + "ARMCC\\BIN\\Armcc.Exe"
        env['AS']           = keil5_path + "ARMCC\\BIN\\Armasm.Exe"
        env['AR']           = keil5_path + "ARMCC\\BIN\\ArmAr.Exe"
        env['LD']           = keil5_path + "ARMCC\\BIN\\ArmLink.Exe"
        env['LINK']         = keil5_path + "ARMCC\\BIN\\ArmLink.Exe"
        env['NM']           = ''
        env['OBJDUMP']      = keil5_path + "ARMCC\\BIN\\FromElf.Exe"
        env['OBJCOPY']      = ''
        env['SIZE']         = ''
        env['RANLIB']       = ''
        env["PROGSUFFIX"]   = ".axf"

        env["ASFLAGS"]      = ""
        env["ASCOM"]        = " '$AS $ASFLAGS -o $TARGET $SOURCES'",

        env['CCCOM']     = r'$CC $CFLAGS $CCFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -c -o $TARGET $SOURCES'

        env['ASFLAGS']   = SCons.Util.CLVar('')
        env['ASPPFLAGS'] = '$ASFLAGS'

        bld = Builder(action = '$AS $ASFLAGS $CFLAGS $CCFLAGS -o $TARGET $SOURCES')
        env['BUILDERS']['ASMCOMM'] = bld

        def generate_hex(source, target, env, for_signature):
            return '$OBJDUMP --i32 %s -o %s '%(source[0], target[0])

        env.Append(BUILDERS={
            'Objdump': Builder(
                       generator=generate_hex,
                       suffix='.hex',
                       src_suffix='.afx')})

        env['LINKFLAGS']   = SCons.Util.CLVar('')
        env['LINKCOM']     = r'$LINK --libpath $keil5_path+ARMCC\LIB $LINKFLAGS -o $TARGET $SOURCES $LIBS'



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
