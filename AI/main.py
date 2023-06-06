import logging

import utils
from ai import AI

# rs = zappyAI.Resources(1, 2, 3, 4, 5, 6, 7, 8)
#
# for k in rs:
#     print(k, rs[k])
#
# if 'linemate' in rs:
#     print("linemate is in rs")

ai = AI(utils.Comm('127.0.0.1', 8000, log_level=logging.INFO), "team1")
print("inventory is correct:", ai.check_inventory())
ai.look()
print(ai.inventory)
for item in ai.world[ai.pos]:
    ai.take(item)
    print("took item:", item)
print("inventory is correct:", ai.check_inventory())
print(ai.inventory)


# command.draw_map()
# command.forward()
# command.look()
# command.draw_map()
# command.forward()
# command.look()
# command.draw_map()
# command.forward()
# command.look()
# command.draw_map()
# command.forward()
# command.look()
# command.draw_map()
# sleep(2)
# command.draw_map()
# command.right()
# sleep(2)
# command.draw_map()
# command.right()
# sleep(2)
# command.draw_map()
# command.forward()
# sleep(2)
# command.draw_map()
# command.left()
# sleep(2)
# command.draw_map()
# command.forward()
# sleep(2)
# command.draw_map()
# print("size: ", len(lala))
# print(lala)
