import os

from utils          import JinjaTemplateManager

from SCons.Node     import Python
from SCons.Builder  import Builder
from SCons.Defaults import processDefines


def generate(env, **kwargs):
    add_builders(env)


def exists(env):
    return 1

def add_builders(env):
    def keil5_emitter(target, source, env): 
        data                = dict()
        data['nrf_dfp_pack_vendor']     = 'NordicSemiconductor'
        data['nrf_dfp_name']            = 'nRF_DeviceFamilyPack'
        data['nrf_dfp_pack_version']    = '8.7.1'
        data['nrf_dfp_pack_url']        = 'http://developer.nordicsemi.com/nRF51_SDK/pieces/nRF_DeviceFamilyPack/'

        data['device']              = 'nRF52832_xxAA'
        data['AdsDevice4']          = 'Cortex-M4'
        data['RvdsVP']              = '2'
        data['Cpu']                 = 'IROM(0x00000000,0x80000) IRAM(0x20000000,0x10000) CPUTYPE("Cortex-M4") FPU2 CLOCK(64000000) ELITTLE'
        data['regview_file']        = 'SVD\\nrf52.xml' #TODO
        data['TargetDllArguments']  = '-MPU'

        data['ram']     = {
                            'dev_size': '0x10000',
                            'dev_start': '0x0',
                            'end': '0x7ffff',
                            'end_next_byte': '0x20010000',
                            'size': '0xec38',
                            'start': '0x200013c8'
                            }
        data['rom']     = {
                            'dev_size': '0x80000',
                            'dev_start': '0x20000000',
                            'end': '0x2000ffff',
                            'end_next_byte': '0x80000',
                            'size': '0x61000',
                            'start': '0x1f000'
                            }

        data['defines']     = processDefines(env.get('CPPDEFINES', []))
        data['includes']    = env.get('CPPPATH', [])

        data['src'] = list()
        for path in env.get('src', []):
            data['src'].append({'name': os.path.basename(path), 'type': '1', 'path': path})

        return (target, [Python.Value(data)])

    def keil5_action(source, target, env):
        assert len(source)
        assert len(target)

        with open(str(target[0]), 'w+') as f:
            template = JinjaTemplateManager.instance().get_template('uvprojx.xml')
            f.write(template.render(source[0].read()))


    env.Append(BUILDERS={
                            'Keil5Project': Builder(
                                action      = keil5_action,
                                emitter     = keil5_emitter,
                                suffix      = '.uvprojx'),
                        })
