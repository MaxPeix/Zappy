import socket
import logging


class Comm:
    _socket: socket.socket = None
    __logger: logging.Logger = logging.getLogger("Comm")

    def __init__(self, ip: str, port: int, connect: bool = True, log_level: int = logging.WARN) -> None:
        self.__logger.setLevel(log_level)
        self.__logger.addHandler(logging.StreamHandler())
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__logger.info("Communication created")
        self.__logger.info("log level: %s", logging.getLevelName(log_level))
        if connect:
            self.connect(ip, port)

    def __del__(self) -> None:
        self.close()
        self.__logger.info("Communication deleted")

    def is_connected(self) -> bool:
        try:
            self._socket.getpeername()
            return True
        except OSError:
            return False

    def connect(self, ip: str, port: int) -> None:
        if self.is_connected():
            self.__logger.warning("Already connected")
            return
        self.__logger.info("Connecting to %s:%d", ip, port)
        try:
            self._socket.connect((ip, port))
        except ConnectionRefusedError:
            self.__logger.error("Connection refused")
            raise ConnectionRefusedError("Connection refused")
        self.__logger.info("Connected to %s:%d", ip, port)

    def send(self, data: str) -> None:
        if not self.is_connected():
            self.__logger.error("Not connected")
            raise ConnectionError("Not connected")
        self.__logger.info("--> %s", data[:-1] if data.endswith("\n") else data)
        self._socket.send(data.encode())

    def _recv(self) -> str | None:
        if not self.is_connected():
            self.__logger.error("Not connected")
            raise ConnectionError("Not connected")
        res: bytes = b""
        while True:
            data: bytes = self._socket.recv(1024)
            res += data
            if not data or len(data) != 1024 or data[1024] == b"":
                break
        if res == b"":
            return None
        return res.decode()

    def recv(self) -> list[str]:
        if not self.is_connected():
            self.__logger.error("Not connected")
            raise ConnectionError("Not connected")
        res: list[str] = []
        data: str = self._recv()
        if data is None:
            return res
        self.__logger.debug("Received data:")
        while len(data) > 0:
            current: str
            index: int = data.index('\n')
            if index == -1:
                break
            current = data[:index]
            if current == "dead":
                self.__logger.info("You died")
                raise ConnectionError("You died")
            data = data[index + 1:]
            self.__logger.info("<-- %s", current)
            res.append(current)
            self.__logger.debug("\t%s", current)
        return res

    def close(self) -> None:
        self._socket.close()
        self.__logger.info("Connection closed")
