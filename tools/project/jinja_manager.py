import os
from jinja2 import PackageLoader, Environment

TEMPLATES = 'templates'

class JinjaManager:
    __the_instance = None

    def __init__(self):
        self.env = Environment(loader                   = PackageLoader('jinja_manager', TEMPLATES),
                               trim_blocks              = True,
                               lstrip_blocks            = True,
                               keep_trailing_newline    = True)
        self.used_templates = dict()


    def get_template(self, name):
        assert isinstance(name, str), "'\'name\' is not str."
        if name not in self.used_templates:
            self.used_templates[name] = self.env.get_template(name)

        return self.used_templates[name]

    @staticmethod
    def instance():
        if JinjaManager.__the_instance is None:
            JinjaManager.__the_instance = JinjaManager()
        return JinjaManager.__the_instance