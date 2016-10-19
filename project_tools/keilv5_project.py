import os

from SCons.Builder  import Builder
from SCons.Node     import Python
from SCons.Node.FS  import File
from SCons.Defaults import processDefines

from jinja_manager  import JinjaManager

def generate(env, **kwargs):
    add_builders(env)


def exists(env):
    return 1


def add_builders(env):
    def keil5_emitter(target, source, env):
        data                = dict()
        data['defines']     = processDefines(env.get('CPPDEFINES', []))
        data['includes']    = list()

        root_dir    = env.Dir("#").abspath
        target_dir  = os.path.dirname(target[0].abspath)
        print(target_dir)
        for path in env.get('CPPPATH', []):
            path = root_dir + '/' + path[1:]
            data['includes'].append(os.path.relpath(path, target_dir))

        source.append(env['startup'])
        data['files'] = list()
        for s in source:
            path = os.path.relpath(s.srcnode().abspath, target_dir)

            new  = dict()
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

    def keil5_action(target, source, env): 
        with open(str(target[0]), 'w+') as f:
            template = JinjaManager.instance().get_template('nrf51422.uvprojx')
            f.write(template.render(source[0].read()))

    env.Append(BUILDERS={
                            'Project': Builder(
                                action  = keil5_action,
                                emitter = keil5_emitter,
                                suffix  = '.uvprojx')
                        })
