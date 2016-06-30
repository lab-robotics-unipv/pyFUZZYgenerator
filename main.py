from core.fuzzyCreator import fuzzyCreator

if __name__ == '__main__':
	fuzzyCreator('./tests/quadFeq.toml', './templates/', 'tests/output').render(False)

