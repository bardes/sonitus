#!/usr/bin/env python
from sys import argv, stderr

usage = \
"""
Usage: {program} <sample rate> <A4 freq.> [octaves=8]
e.g.: {program} 64000 442.0 5
""".format(program=argv[0])

if len(argv) < 3 or len(argv) > 4 :
    print(usage, file = stderr)
    exit(1)

A4 = 0
sample_rate = 0
octaves = 8

try:
    A4 = float(argv[2])
except:
    print("Error, invalid argument: Freq. must be a number!", file = stderr)
    print(usage, file = stderr)
    exit(1)

try:
    sample_rate = int(argv[1])
except:
    print("Error, invalid argument: Sample rate must be an integer!", \
            file = stderr)
    print(usage, file = stderr)
    exit(1)

if len(argv) == 4 :
    try:
         octaves = int(argv[3])
    except:
        print("Error, invalid argument: Octaves must be an integer!", \
                file = stderr)
        print(usage, file = stderr)
        exit(1)

freq_ratio = 2**(1/12)
base_freq = A4/(freq_ratio**57)
periods = [round(sample_rate/(2*base_freq*freq_ratio**t)) \
        for t in range(0, 12*octaves)]

print("uint16_t tone_periods[{ntones}] = {{".format(ntones=12*octaves))
for o in range(0, octaves):
    print('\t', end='')
    for i in range(0, 12):
        print("{period}, ".format(period=periods[12*o+i]), end='')
    print('')
print("};")
