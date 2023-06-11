import zappyAI as zp

from brain import Brain
import json

br = Brain("team1", '127.0.0.1', 8000)

lala = br._ai.to_json()

print(lala)

# br.cartography(zp.Pos(1, 6), zp.Pos(6, 1))

