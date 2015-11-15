import unittest
from ..MembershipFunction import Triangle


class TestTriangleMF(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    def test_triangle_left_side(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(-11), 0)

    def test_triangle_left_corner(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(-10), 0)

    def test_triangle_left_edge(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(0), 0.5)

    def test_triangle_center(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(10), 1)

    def test_triangle_right_edge(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(15), 0.5)

    def test_triangle_right_corner(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(20), 0)

    def test_triangle_right_side(self):
        param = {'type': 'triangle', 'param': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(21), 0)

if __name__ == "__main__":
    unittest.main()
