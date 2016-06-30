from core.fuzzyCreator import fuzzyCreator

if __name__ == '__main__':
	fuzzyCreator('./tests/simpleFeq.toml', './templates/', 'tests/output').render(False)

