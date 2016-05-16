import logging
import pprint
from core.Model import ModelFIND

logging.FileHandler('debug.log')
logging.basicConfig(level=logging.DEBUG)

m = ModelFIND()
obj = m.load('simple_find.toml')
pprint.pprint(obj)

m.setInputValuesList([-10.0, -10.0])
index = m.calcIndex()
print(index)

