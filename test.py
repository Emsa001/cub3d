import os
import subprocess
import time

map_dir = '/maps/'
put_dir = ''

def usleep(mlsec):
    sec = mlsec / 1000000.0
    time.sleep(sec)

# cub3d tester

BLUE = '\033[1;94m'
GREEN = '\033[1;92m'
RED = '\033[1;91m'
RESET = '\033[0m'

def wrong_format():
    answer = True
    i = 1
    dir = put_dir
    usleep(100000)
    print(f"\n{BLUE}[ TESTING WRONG FORMAT ]{RESET}")
    valgrind_ok = "ERROR SUMMARY: 0 errors from 0 contexts"
    valgrind = 'valgrind --leak-check=full'

    run_cmd = './cub3d' + ' ' + dir

    maps = ['.cub', 'wrong1.cub', 'wrong2', 'wrong3.cub', 'wrong4.cub'
            , 'wrong5.cub', 'wrong6.cub', 'wrong7.cub', 'wrong8.cub', 'wrong9.cub'
            , 'wrong10.cub', 'wrong11.cub', 'wrong12.cub', 'wrong13.cub', 'wrong14.cub'
            , 'wrong15.cub', 'wrong16.cub']

    for m in maps:
        test = subprocess.Popen(f"{valgrind} {run_cmd + m}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = subprocess.run(run_cmd + m, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode
        if valgrind_ok not in test.stderr.read().decode():
            print(f"{RED}{i}. [KO LEAKS]{RESET}")
            print(f"{RED}Command: {run_cmd + m}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [MOK]{RESET}")
        i += 1
        if exit_code != 1:
            print(f"{RED}{i}. [KO]{RESET} {BLUE}EXIT [1] {RED}RETURN [{exit_code}]{RESET}")
            print(f"{RED}Command: {run_cmd + m}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] RETURN [{exit_code}]{RESET}")
        i += 1
    return answer

def wrong_args():
    answer = True
    i = 1
    usleep(100000)
    print(f"\n{BLUE}[ TESTING WRONG ARGS ]{RESET}")
    valgrind_ok = "ERROR SUMMARY: 0 errors from 0 contexts"

    cmd = ['./cub3d ' , './cub3d map.cub map.cub', './cub3d ""', './cub3d map.cub ""', './cub3d "" map.cub']

    valgrind = 'valgrind --leak-check=full'
    for c in cmd:
        test = subprocess.Popen(f"{valgrind} {c}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = subprocess.run(c, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode
        if valgrind_ok not in test.stderr.read().decode():
            print(f"{RED}{i}. [KO LEAKS]{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] [MOK]{RESET}")
        i += 1
        if exit_code != 1:
            print(f"{RED}{i}. [KO]{RESET} {BLUE}EXIT [1] {RED}RETURN [{exit_code}]{RESET}")
            print(f"{RED}Command: {c}{RESET}")
            answer = False
        else:
            print(f"{GREEN}{i}.[OK] RETURN [{exit_code}]{RESET}")
        i += 1
    return answer

if __name__ == "__main__":
    test = False
    failed_tests = []
    if not wrong_args():
        test = True
        failed_tests.append("wrong_args")
    if not wrong_format():
        test = True
        failed_tests.append("wrong_format")
    if test:
        print(f"\n{RED}[SOME TESTS FAILED]{RESET}")
        for i in failed_tests:
            print(f"{RED}[{i}]{RESET}")
    else:
        print(f"\n{GREEN}[ALL TESTS PASSED]{RESET}")
