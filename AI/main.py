from brain import Brain
import logging
from utils import Comm
import argparse
import sys
from dataclasses import dataclass


@dataclass
class Arguments:
    host: str
    port: int
    name: str
    log_level: int


HELP = """USAGE: {executable} -p port -n name -h machine
               port    is the port number
               name    is the name of the team
               machine is the name of the machine; localhost by default
"""


def print_usage() -> None:
    print(HELP.format(executable=sys.argv[0]))


def main() -> None:
    if "--help" in sys.argv:
        print_usage()
        exit(0)

    parser = argparse.ArgumentParser(
        prog=sys.argv[0],
        add_help=False
    )
    parser.add_argument("-p", "--port", required=True, type=int, help='The port number')
    parser.add_argument("-n", "--name", required=True, type=str, help="The name of the team to join")
    parser.add_argument("-h", "--host", default="localhost", type=str, help="The ip or hostname of the server")
    parser.add_argument("-l", "--log-level", default=20, type=str,
                        help="Enable verbose logging (lower is more verbose)")
    parser.add_argument("-a", "--auto-spawn", default=False, type=bool, help="Automatically spawn new players")
    parser.add_argument("-e", "--encrypt", default=False, type=bool,
                        help="Encrypt the communication (required if multiple teams)")

    try:
        args = parser.parse_args()
    except SystemExit:
        exit(84)

    try:
        communication: Comm = Comm(args.host, args.port, log_level=args.log_level)
    except ConnectionRefusedError:
        print(f"Unable to connect to the server at {args.host}:{args.port}")
        exit(84)
    br = Brain(args.name, communication, args.encrypt, args.auto_spawn)
    br.run()


if __name__ == "__main__":
    main()
