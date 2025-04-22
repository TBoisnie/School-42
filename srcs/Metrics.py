#!/bin/python3

from typing import List
from Node import Node


class Metrics:

    _time_complexity : int
    _space_complexity : int
    _path : List[Node]

    # Constructor
    def __init__(self):
        self._time_complexity = 1
        self._space_complexity = 1
        self._path = []

    # Getters & Setters
    @property
    def time_complexity(self):
        return self._time_complexity

    @time_complexity.setter
    def time_complexity(self, time_complexity_):
        self._time_complexity = time_complexity_

    @property
    def space_complexity(self):
        return self._space_complexity

    @space_complexity.setter
    def space_complexity(self, space_complexity_):
        self._space_complexity = space_complexity_

    @property
    def path(self):
        return self._path

    @path.setter
    def path(self, path_):
        self._path = path_
