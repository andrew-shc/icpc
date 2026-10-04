#!/usr/bin/env python3

"""
Local testing tool for My System.

Note: This tool is intended to help with debugging interaction.
It is *not* the same code used to test your solution when it
is submitted. For example, the tool *does not* apply the time
and memory limits that are applied to submitted solutions,
and there may be other differences, especially if your solution
exhibits incorrect behavior.

To run the testing tool, run::

    pypy3 testing_tool.py <program> <arguments>

where `arguments` are optional arguments to the program to run. The following
show examples for different languages:

    pypy3 testing_tool.py ./myprogram
    pypy3 testing_tool.py java -cp . MyProgram
    pypy3 testing_tool.py pypy3 myprogram.py

The testing tool will run your program on exactly one test case.
"""

import argparse
import random
import subprocess
import sys
from typing import TextIO


class WrongAnswer(RuntimeError):
    """Raised whenever an incorrect answer is received."""

    pass


def vprint(*args, verbose: bool, file: TextIO, **kwargs) -> None:
    """Print to `file`, and also to stdout if `verbose is true."""
    if verbose:
        print("< ", end="")
        print(*args, **kwargs)
        sys.stdout.flush()
    print(*args, file=file, **kwargs)


def vreadline(data: TextIO, verbose: bool) -> str:
    """Read a line from `data`, and also log it to stdout if `verbose` is true."""
    line = data.readline()
    if verbose and line:
        print(">", line.rstrip("\n"))
    return line


def check_done(process: subprocess.Popen) -> None:
    """Check for extra output from program."""
    line = vreadline(process.stdout, True)
    if line != "":
        raise WrongAnswer("Program gave extra output")


def main() -> int:
    parser = argparse.ArgumentParser(usage="%(prog)s [-h] filename program [args...]")
    parser.add_argument("program", nargs=argparse.REMAINDER)

    args = parser.parse_args()
    if not args.program:
        parser.error("Must specify program to run")

    l = []
    for i in range(100):
        if random.randint(0, 1):
            l.append("F")
            l.append("T")
        else:
            l.append("T")
            l.append("F")

    s = "".join(l)

    process = subprocess.Popen(
        args.program,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        encoding="utf-8",
        errors="surrogateescape",
    )

    try:
        vprint("1", file=process.stdin, flush=True, verbose=True)
        numMatches = 0
        for i in range(len(s)):
            ch = vreadline(process.stdout, True).strip()
            if not (ch == "F" or ch == "T"):
                raise WrongAnswer("got illegal output {}".format(ch))
            numMatches += s[i] == ch
            vprint(s[i], file=process.stdin, flush=True, verbose=True)
        print(
            "Your program correctly answered {} of the 200 questions".format(numMatches)
        )
        check_done(process)
    except WrongAnswer as e:
        print("ERROR: %s" % e)
        vprint("-1", file=process.stdin, flush=True, verbose=True)
        return 1
    except BrokenPipeError:
        print("ERROR: error when communicating with program - exited prematurely?")
        return 2

    return 0


if __name__ == "__main__":
    sys.exit(main())
