import logging
from core.Model import ModelFIND

logging.FileHandler('debug.log')
logging.basicConfig(level=logging.DEBUG)

m = ModelFIND()
obj = m.load('fuzzy_system.toml')
print(obj)
