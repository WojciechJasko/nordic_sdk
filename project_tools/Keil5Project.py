import os

from utils          import JinjaTemplateManager

from SCons.Node     import Python, FS
from SCons.Builder  import Builder


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
        data['regview_file']        = '$$Device:nRF52832_xxAA$\\SVD\\nrf52.xml'
        data['TargetDllArguments']  = '-MPU'

        data['ram']     = {
                            'size'  : '0x10000',
                            'start' : '0x20000000'
                            }
        data['rom']     = {
                            'size'  : '0x80000',
                            'start' : '0x00000'
                            }

        data['defines']     = env.get('CPPDEFINES', [])
        data['includes']    = env.get('CPPPATH', [])

        data['src'] = list()
        for path in env.get('src', []):
            if isinstance(path, FS.File):
                path = str(path)
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
