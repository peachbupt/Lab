import sys

class Callback(object):
    def __init__(self):
        self.func_map = {}
    def register(self, name):
        def func_wrapper(f):
            self.func_map[name] = f
            return f
        return func_wrapper

    def call_register(self, name = None):
        func = self.func_map.get(name, None)
        if func is None:
            raise Exception("No function registered againest - " + str(name))
        return func()

c = Callback()

@c.register('/')
def main_page_func():
    return "this is the main page"
@c.register('/next_page')
def next_page():
    return "this is the next page"
     
print c.call_register('/')
print c.call_register('/next_page')










