import subprocess

build_folder = 'build-vs'

def main():
    print('[setup.py] Installing dependencies via Conan')
    subprocess.run(f'conan install --build=missing --install-folder {build_folder} --output-folder {build_folder} -pr:b=default -s build_type=Debug .'.split(' '))
    subprocess.run(f'cmake --preset default -B {build_folder}')

main()
