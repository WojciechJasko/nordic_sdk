import os
import json
import pprint as pp

class EnvUpdater():

    def __init__(self, path):
        self.db = dict()

        for (dirpath, dirnames, filenames) in os.walk(path):
            for filename in filenames:
                path = os.path.join(dirpath, filename)

                with open(path, "r") as f:
                    config = json.load(f)

                for key, value in config.iteritems():
                    self._config_add(key, value)


    def _config_add(self, name, config):
        assert name not in self.db, '\'name\' already in db.'
        self.db[name] = config


    def update(self, env, desc):
        if isinstance(desc, list):
            for item in desc:
                self.update(env, item)

        elif isinstance(desc, dict):
            for key, value in desc.iteritems():
                if key in env: # key found
                    # update enviroment
                    if isinstance(env[key], list):
                        env[key].extend(value)
                    else:
                        env[key] = value

                elif key in self.db:
                    self.update(env, self.db[key][value])

                else:
                    raise Exception("Unknown key {}".format(key))

        else:
            raise Exception("Unexpected type {} {}".format(type(desc), desc))


    def dump(self):
        pp.pprint(self.db)

