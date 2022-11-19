import os, json, argparse, shutil, sys

p = argparse.ArgumentParser()
p.add_argument('--clean', action = 'store_true')
p.add_argument('--cmake', action = 'store_true')
p.add_argument('--verbose', action = 'store_true')
p.add_argument('--upload', action = 'store_true')
p.add_argument('--config', required = False)
args = p.parse_args()

contents = json.load(open('config.json', 'r'))

configs = contents["configs"] if not args.config else [c for c in contents["configs"] if c["name"] == args.config]

for config in configs:
    print('BUILDING FOR TARGET -> %s' % config['name'])
    output = 'build_' + config['name']
    if not os.path.isdir(output):
        os.mkdir(output)
    elif args.clean:
        shutil.rmtree(output)
        os.mkdir(output)

    cmake_params = ' '.join(['-D%s:%s="%s"' % (p["name"], p["type"], p["value"]) for p in config["parameters"]])

    if args.upload:
        if 'upload_enabled' in config.keys():
            cmake_params += ' -DUPLOAD:BOOL=ON'
    else:
        cmake_params += ' -DUPLOAD:BOOL=OFF'


    if args.verbose:
        cmake_params += ' -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON --verbose=1'
    else:
        # Just in case it's cached.
        cmake_params += ' -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF'

    os.chdir(output)
    os.system(f'cmake {cmake_params} ..')
    print(f'cmake {cmake_params} ..')

    if not args.cmake:
        os.system('make -j4')
