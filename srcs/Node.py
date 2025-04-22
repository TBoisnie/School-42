#!/bin/python3

from __future__ import annotations

from Puzzle import Puzzle


class Node:

    _value : Puzzle
    _parent : Node

    _cost_g : float
    _cost_h : float
    _cost_f : float

    # Constructor
    def __init__(self, value_):
        self._value = value_
        self._parent = None

        self._cost_g = 0.0
        self._cost_h = 0.0
        self._cost_f = 0.0

    # Public methods
    def clone(self):
        clone = Node(self._value.clone())
        clone.parent = self._parent
        clone.cost_h = self._cost_h
        clone.cost_g = self._cost_g

        return clone

    # Getters & Setters
    @property
    def value(self):
        return self._value

    @property
    def parent(self):
        return self._parent

    @parent.setter
    def parent(self, parent_):
        self._parent = parent_

    @property
    def cost_g(self):
        return self._cost_g

    @cost_g.setter
    def cost_g(self, cost_g_):
        self._cost_g = cost_g_
        self.__update_cost_f()

    @property
    def cost_h(self):
        return self._cost_h

    @cost_h.setter
    def cost_h(self, cost_h_):
        self._cost_h = cost_h_
        self.__update_cost_f()

    @property
    def cost_f(self):
        return self._cost_f

    # Private methods
    def __update_cost_f(self):
        self._cost_f = self._cost_g + self._cost_h

    # Comparison: Equality ("in")
    def __eq__(self, other_):
        return self._value == other_.value

    def __hash__(self):
        return self._value.hash

    # Comparison: Order (HeapQ)
    def __lt__(self, other_):
        return self._cost_f < other_.cost_f
