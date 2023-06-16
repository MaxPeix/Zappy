import brain
import time
import sys

port: int = 0
name: str = ""
host: str = "localhost"

for i in range(len(sys.argv)):
    if sys.argv[i] == "--help":
        print("USAGE: ./zappy_ai -p port -n name -h machine")
        print("       port    is the port number")
        print("       name    is the name of the team")
        print("       machine is the name of the machine; localhost by default")
        exit(0)
if len(sys.argv) < 5:
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    exit(84)
for i in range(len(sys.argv)):
    if sys.argv[i] == "-p":
        if not sys.argv[i + 1].isdigit():
            print("Port must be a number")
            exit(84)
        port = int(sys.argv[i + 1])
    if sys.argv[i] == "-n":
        name = sys.argv[i + 1]
    if sys.argv[i] == "-h":
        host = sys.argv[i + 1]
if port == 0 or name == "":
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    exit(84)
if port < 0 or port > 65535:
    print("Port must be between 0 and 65535")
    exit(84)

# br = Brain(name, host, port)
br = Brain("team1", '127.0.0.1', 8000)
br.run()

time.sleep(3600)
