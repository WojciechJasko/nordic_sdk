import os

from SCons.Builder  import Builder
from SCons.Node     import Python
from SCons.Node.FS  import File
from SCons.Defaults import processDefines

from jinja2 import PackageLoader, Environment

jinjaEnv = None

def generate(env, **kwargs):
    setup_environment(env)
    add_builders(env)


def exists(env):
    return 1


def setup_environment(env):
    global jinjaEnv
    jinjaEnv = Environment(loader                   = PackageLoader('keilv5_project', 'templates'),
                           trim_blocks              = True,
                           lstrip_blocks            = True,
                           keep_trailing_newline    = True)


def add_builders(env):
    def keilv5_project_emitter(target, source, env):
        assert(len(target) == 1)
        data        = dict()
        root_dir    = env.Dir("#").abspath
        target_dir  = os.path.dirname(target[0].abspath)

        file    = str(target[0])
        target  = list()
        target.append(file + '.uvprojx')
        target.append(file + '.uvoptx')

        # Add SVD-File.
        if env['mcu'].startswith('nrf51'):
            path                = os.path.join(os.path.dirname(__file__), 'keil', 'svd', 'nrf51.svd')
            data['svd_file']    = os.path.relpath(path, target_dir)

        elif env['mcu'].startswith('nrf52'):
            path                = os.path.join(os.path.dirname(__file__), 'keil', 'svd', 'nrf52.svd')
            data['svd_file']    = os.path.relpath(path, target_dir)

        # Add defines.
        data['defines'] = processDefines(env.get('CPPDEFINES', []))

        # Add includes.
        data['includes'] = list()
        for path in env.get('CPPPATH', []):
            path = root_dir + '/' + path[1:]
            data['includes'].append(os.path.relpath(path, target_dir))

        # Add files.
        data['files'] = list()
        source.append(env['startup'])
        for s in source:
            path = os.path.relpath(s.srcnode().abspath, target_dir)

            new         = dict()
            new['name'] = os.path.basename(path)
            new['path'] = path

            ext = os.path.splitext(path)[1]
            if ext in ['.c']:
                new['type'] = '1'

            elif ext in ['.S', '.s']:
                new['type'] = '2'

            elif ext == '.lib':
                new['type'] = '4'

            else:
                new['type'] = '5'

            data['files'].append(new)

        return (target, [Python.Value(data)])

    def keilv5_project_action(target, source, env): 
        global jinjaEnv
        with open(str(target[0]), 'w+') as f:
            template = jinjaEnv.get_template(env['mcu'] + '.uvprojx')
            f.write(template.render(source[0].read()))

        with open(str(target[1]), 'w+') as f:
            template = jinjaEnv.get_template(env['mcu'] + '.uvoptx')
            f.write(template.render(source[0].read()))

    env.Append(BUILDERS={
                            'Project': Builder(
                                action  = keilv5_project_action,
                                emitter = keilv5_project_emitter)
                        })
