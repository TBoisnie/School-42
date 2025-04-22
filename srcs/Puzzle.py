#!/bin/python3

from random import choice
from Utils import Utils
from typing import List, Tuple


class Puzzle:

    _n : int
    _tiles : List[int]
    _tiles_position : List[Tuple[int]]
    _hash : int

    # Constructor
    def __init__(self, n_, tiles_, update_ = True):
        self._n = n_
        self._tiles = tiles_

        if update_:
            self.__update_tiles_position()
            self.__update_hash()

    # Public methods
    def move_to(self, dx_, dy_):
        src_x, src_y = self._tiles_position[0]
        dst_x, dst_y = src_x + dx_, src_y + dy_

        if 0 <= dst_x < self._n and 0 <= dst_y < self._n:
            src_idx = src_y * self._n + src_x
            dst_idx = dst_y * self._n + dst_x

            src_val = self._tiles[src_idx]
            dst_val = self._tiles[dst_idx]

            src_pos = self._tiles_position[src_val]
            dst_pos = self._tiles_position[dst_val]

            self._tiles_position[src_val] = dst_pos
            self._tiles_position[dst_val] = src_pos

            self._tiles[src_idx] = dst_val
            self._tiles[dst_idx] = src_val

            self.__update_hash()

            return True

        return False

    def randomize(self, max_iteration_):
        for _ in range(max_iteration_):
            delta = [0, 0]
            delta[choice([0, 1])] = choice([-1, 1])
            self.move_to(*delta)

    def orderize(self):
        self._tiles = Utils.matrix_to_list(
            Utils.matrix_generate_snail(self._n)
        )
        self.__update_tiles_position()
        self.__update_hash()

    def is_solvable(self, dst_):
        swap = self.count_swap(dst_)

        src_zero_pos = self.__get_position(0)
        dst_zero_pos = dst_.__get_position(0)

        zero_dist = abs(src_zero_pos[0] - dst_zero_pos[0]) + abs(src_zero_pos[1] - dst_zero_pos[1])

        return (zero_dist % 2 == 0 and swap % 2 == 0) or (zero_dist % 2 == 1 and swap % 2 == 1)

    def count_swap(self, dst_):
        swap = 0
        for i in range(self._n * self._n):
            for j in range(i + 1, self._n * self._n):
                if dst_.tiles.index(self._tiles[i]) > dst_.tiles.index(self._tiles[j]):
                    swap += 1
        return swap

    def clone(self):
        c = Puzzle(self._n, self._tiles[:], False)
        c._tiles_position = self._tiles_position[:]
        c._hash = self._hash
        return c

    # Getters & Setters
    @property
    def n(self):
        return self._n

    @property
    def tiles(self):
        return self._tiles

    @property
    def tiles_position(self):
        return self._tiles_position

    @property
    def hash(self):
        return self._hash

    # Private methods
    def __update_hash(self):
        self._hash = hash(tuple(self._tiles))

    def __update_tiles_position(self):
        self._tiles_position = [ self.__get_position(i) for i in range(0, self._n * self._n)]

    def __get_position(self, i_):
        index = self._tiles.index(i_)
        return (index % self._n, index // self._n)

    # Comparison: Equality
    def __eq__(self, other_):
        return self._hash == other_.hash
