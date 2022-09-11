import ray

# initialize ray
ray.init()
# define functions to execute in parallel using ray.remote
@ray.remote
def func1():
    # do this

@ray.remote
def func2():
    # do this


if __name__ == '__main__':



