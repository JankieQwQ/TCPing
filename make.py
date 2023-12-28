import os
if __name__ == '__main__':
    output_name = 'tcping{}'.format(os.name.replace('nt','.exe').replace('posix',''))
    code = os.system('g++ -o {} main.cpp'.format(output_name))
    failed = '[Failed] An error was thrown while compiling with g++, please check the command line output.'
    print('\033[0;31;40m{}\033[0m'.format(failed))
    raise SystemExit(0)