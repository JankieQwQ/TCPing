import os

coloramaFlag = True
try:
    import colorama
except ModuleNotFoundError:
    coloramaFlag = False

if __name__ == '__main__':
    output_name = 'tcping{}'.format(os.name.replace('nt','.exe').replace('posix',''))
    code = os.system('g++ -o {} main.cpp'.format(output_name))
    failed = '[Failed] An error was thrown while compiling with g++, please check the command line output'
    if code:
        if coloramaFlag:
            print(colorama.Fore.RED + failed)
        else:
            print(failed)
    raise SystemExit(0)