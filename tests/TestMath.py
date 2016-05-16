import unittest
from core.Membership import Triangle
from core.Membership import Sigmoid


class TestTriangleMF(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    # set of tests to check some data correctness
    def test_triangle_name(self):
        param = {'type': 'triangle', 'parameters': [-10, 0, 10]}
        name = 'Test Triangle'
        t = Triangle(name, param)
        self.assertEqual(t.name, name)

    def test_triangle_description(self):
        descr = 'Sample description'
        param = {'type': 'triangle', 'parameters': [-10, 0, 10], 'description': descr}
        t = Triangle('Test Triangle', param)
        self.assertEqual(t.description, descr)

    # set of tests to check parameters correctness
    def test_triangle_wrong_type(self):
        param = {'type': 'tria', 'parameters': [-10, 10, 20]}
        with self.assertRaises(TypeError):
            Triangle('Test Triangle', param)

    def test_triangle_too_few_param(self):
        param = {'type': 'triangle', 'parameters': [-10, 10]}
        with self.assertRaises(ValueError):
            Triangle('Test Triangle', param)

    def test_triangle_too_many_param(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20, 30]}
        with self.assertRaises(ValueError):
            Triangle('Test Triangle', param)

    def test_triangle_non_number_param(self):
        param = {'type': 'triangle', 'parameters': [10, 20, 'x']}
        with self.assertRaises(ValueError):
            Triangle('Test Triangle', param)

    def test_triangle_same_values_param(self):
        param = {'type': 'triangle', 'parameters': [10, 20, 20]}
        with self.assertRaises(ValueError):
            Triangle('Test Triangle', param)

    def test_triangle_unordered_param(self):
        param = {'type': 'triangle', 'parameters': [10, 30, 20]}
        with self.assertRaises(ValueError):
            Triangle('Test Triangle', param)

    # check correctness of calculated values
    def test_triangle_left_side(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(-11), 0)

    def test_triangle_left_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(-10), 0)

    def test_triangle_left_edge(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(0), 0.5)

    def test_triangle_just_left_of_left_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(-10.0001), 0)

    def test_triangle_just_right_of_left_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertGreater(tria.f(-9.9999), 0)

    def test_triangle_just_left_of_center(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertLess(tria.f(9.999), 1)

    def test_triangle_just_right_of_center(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertLess(tria.f(10.0001), 1)

    def test_triangle_right_edge(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(15), 0.5)

    def test_triangle_right_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(20), 0)

    def test_triangle_just_left_of_right_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertGreater(tria.f(19.9999), 0)

    def test_triangle_just_right_of_right_corner(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(20.0001), 0)

    def test_triangle_right_side(self):
        param = {'type': 'triangle', 'parameters': [-10, 10, 20]}
        tria = Triangle('Test Triangle', param)
        self.assertEqual(tria.f(21), 0)

class TestSigmoidMF(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    # set of tests to check some data correctness
    def test_sigmoid_name(self):
        param = {'type': 'sigmoid', 'parameters': [10, 5]}
        name = 'Test Simoid'
        t = Sigmoid(name, param)
        self.assertEqual(t.name, name)

    def test_sigmoid_description(self):
        descr = 'Sample description'
        param = {'type': 'sigmoid', 'parameters': [10, 5], 'description': descr}
        t = Sigmoid('Test Sigmoid', param)
        self.assertEqual(t.description, descr)

    # set of tests to check parameters correctness
    def test_sigmoid_wrong_type(self):
        param = {'type': 'sigmo', 'parameters': [10, 5]}
        with self.assertRaises(TypeError):
            Sigmoid('Test Sigmoid', param)

    def test_sigmoid_too_few_param(self):
        param = {'type': 'sigmoid', 'parameters': [10]}
        with self.assertRaises(ValueError):
            Sigmoid('Test Sigmoid', param)

    def test_sigmoid_too_many_param(self):
        param = {'type': 'sigmoid', 'parameters': [-10, 10, 20]}
        with self.assertRaises(ValueError):
            Sigmoid('Test Sigmoid', param)

    def test_sigmoid_non_number_param(self):
        param = {'type': 'sigmoid', 'parameters': [10, 'x']}
        with self.assertRaises(ValueError):
            Sigmoid('Test Sigmoid', param)

    # check correctness of calculated values
    def test_sigmoid_center(self):
        param = {'type': 'sigmoid', 'parameters': [10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertEqual(sigm.f(5), 0.5)

    def test_sigmoid_left_of_center(self):
        param = {'type': 'sigmoid', 'parameters': [10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertLess(sigm.f(4.9), 0.5)

    def test_sigmoid_right_of_center(self):
        param = {'type': 'sigmoid', 'parameters': [10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertGreater(sigm.f(5.1), 0.5)

    def test_sigmoid_center2(self):
        param = {'type': 'sigmoid', 'parameters': [-10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertEqual(sigm.f(5), 0.5)

    def test_sigmoid_left_of_center2(self):
        param = {'type': 'sigmoid', 'parameters': [-10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertGreater(sigm.f(4.9), 0.5)

    def test_sigmoid_right_of_center2(self):
        param = {'type': 'sigmoid', 'parameters': [-10, 5]}
        sigm = Sigmoid('Test Sigmoid', param)
        self.assertLess(sigm.f(5.1), 0.5)


if __name__ == "__main__":
    unittest.main()
