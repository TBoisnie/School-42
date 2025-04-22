#!/bin/python3

from abc import ABC, abstractmethod
from typing import NamedTuple


class Point(NamedTuple):
    x: float = 0.0
    y: float = 0.0


class LinearRegression(ABC):

    _points : list[Point] = []
    _points_size : int = 0
    _points_min : Point = Point(0.0, 0.0)
    _points_max : Point = Point(0.0, 0.0)

    _theta : list[float] = [0.0, 0.0]
    _accuracy : float = 0.0

    #
    # Constructor
    #
    def __init__(self, points):
        self._points = points
        self._points_size = len(points)

        if self._points_size > 0:
            x_list = [p.x for p in self._points]
            y_list = [p.y for p in self._points]

            self._points_min = Point(min(x_list), min(y_list))
            self._points_max = Point(max(x_list), max(y_list))

            self._updateAccuracy()

    #
    # Public Methods
    #
    @abstractmethod
    def run(self):
        pass

    def estimate(self, x):
        return self._theta[0] + self._theta[1] * x

    #
    # Getters & Setters
    #
    def getPointsMin(self):
        return self._points_min

    def getPointsMax(self):
        return self._points_max

    def getAccuracy(self):
        return self._accuracy

    def getTheta(self):
        return self._theta

    def setPointsMin(self, x_min, y_min):
        self._points_min = Point(x_min, y_min)

    def setPointsMax(self, x_max, y_max):
        self._points_max = Point(x_max, y_max)

    def setAccuracy(self, accuracy):
        self._accuracy = accuracy

    def setTheta(self, theta_0, theta_1):
        self._theta = [theta_0, theta_1]

    #
    # Private Methods
    #
    def _updateAccuracy(self):
        avg_y = sum([ p.y for p in self._points ]) / float(self._points_size)

        sum_square_explained = sum([ (p.y - self.estimate(p.x)) ** 2 for p in self._points ])
        sum_square_total     = sum([ (p.y - avg_y)              ** 2 for p in self._points ])

        if sum_square_total == 0.0:
            self._accuracy = 1.0 if sum_square_explained == 0.0 else -1.0
        else:
            self._accuracy = 1.0 - sum_square_explained / sum_square_total


class GradientDescent(LinearRegression):

    _points_normalized: list[Point]
    _error : float = 0.0

    #
    # Constructor
    #
    def __init__(self, points):
        super().__init__(points)

        self._points_normalized = [ Point(self.__normalizeX(p.x), self.__normalizeY(p.y)) for p in self._points ]

        if self._points_size > 0:
            self.__updateError()

    #
    # Overloading
    #
    def run(self, max_iteration=1e6, learning_rate=1e0, precision=1e-6):
        for _ in range(int(max_iteration)):
            t0 = learning_rate / float(self._points_size) * sum([ (self.__estimate(p.x) - p.y)       for p in self._points_normalized ])
            t1 = learning_rate / float(self._points_size) * sum([ (self.__estimate(p.x) - p.y) * p.x for p in self._points_normalized ])

            self._theta[0] -= t0
            self._theta[1] -= t1

            prev_err = self._error
            self.__updateError()

            if self.__isPrecisionReached(precision, prev_err, self._error):
                break

            learning_rate = self.__adjustLearningRate(learning_rate, prev_err, self._error)

        self._updateAccuracy()

    def estimate(self, x):
        return self.__denormalizeY(super().estimate(self.__normalizeX(x)))

    #
    # Getters & Setters
    #
    def getError(self):
        return self._error

    #
    # Private Methods
    #
    def __estimate(self, normalized_x):
        return super().estimate(normalized_x)

    def __updateError(self):
        sum_squared_errors = sum([ (self.__estimate(p.x) - p.y) ** 2 for p in self._points_normalized ])

        self._error = sum_squared_errors / float(self._points_size)

    def __isPrecisionReached(self, precision, prev_err, curr_err):
        return (abs(prev_err - curr_err) < precision)

    def __adjustLearningRate(self, learning_rate, prev_err, curr_err):
        return learning_rate / (1.0 + float(curr_err >= prev_err))

    #
    # Normalization
    #
    def __normalizeX(self, x):
        if self._points_max.x == self._points_min.x:
            return 1.0 / self._points_size
        return (x - self._points_min.x) / (self._points_max.x - self._points_min.x)

    def __normalizeY(self, y):
        if self._points_max.y == self._points_min.y:
            return 1.0 / self._points_size
        return (y - self._points_min.y) / (self._points_max.y - self._points_min.y)

    def __denormalizeX(self, x):
        return x * (self._points_max.x - self._points_min.x) + self._points_min.x

    def __denormalizeY(self, y):
        return y * (self._points_max.y - self._points_min.y) + self._points_min.y


class LeastSquare(LinearRegression):

    #
    # Constructor
    #
    def __init__(self, points):
        super().__init__(points)

    #
    # Overrides
    #
    def run(self):
        sum_x = sum([ p.x for p in self._points ])
        sum_y = sum([ p.y for p in self._points ])

        avg_x = sum_x / float(self._points_size)
        avg_y = sum_y / float(self._points_size)

        covariance = sum([ (p.x - avg_x) * (p.y - avg_y) for p in self._points ])
        variance   = sum([ (p.x - avg_x) ** 2            for p in self._points ])

        self._theta[1] = covariance / variance
        self._theta[0] = avg_y - self._theta[1] * avg_x

        self._updateAccuracy()


if __name__ == "__main__":
    points = [
        Point(1.0, 8.0),
        Point(3.0, 5.0),
        Point(5.0, 3.0),
        Point(7.0, 3.0),
    ]
    to_estimate = 6

    lr = GradientDescent(points)
    lr.run()
    t0 = lr.estimate(0)
    t1 = lr.estimate(1) - t0
    print(f"Gradient Descent: {t0}, {t1}")
    print(f"Error: {lr.getError()}")
    print(f"Accuracy: {lr.getAccuracy() * 100:.8}%")
    print(f"Estimate ({to_estimate}): {lr.estimate(to_estimate)}")

    print()

    lr = LeastSquare(points)
    lr.run()
    t0 = lr.estimate(0)
    t1 = lr.estimate(1) - t0
    print(f"Least Square: {t0}, {t1}")
    print(f"Error: None")
    print(f"Accuracy: {lr.getAccuracy() * 100:.8}%")
    print(f"Estimate ({to_estimate}): {lr.estimate(to_estimate)}")

