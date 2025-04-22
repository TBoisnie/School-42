#!/bin/python3

from math import sqrt


class Heuristic:

    @staticmethod
    def manhattan(src_, dst_):
        dist = 0.0

        for i in src_.tiles:
            src_pos = src_.tiles_position[i]
            dst_pos = dst_.tiles_position[i]

            dx = abs(dst_pos[0] - src_pos[0])
            dy = abs(dst_pos[1] - src_pos[1])

            dist += dx + dy

        return dist

    @staticmethod
    def euclidean(src_, dst_):
        dist = 0.0

        for i in src_.tiles:
            src_pos = src_.tiles_position[i]
            dst_pos = dst_.tiles_position[i]

            dx = dst_pos[0] - src_pos[0]
            dy = dst_pos[1] - src_pos[1]

            dist += dx * dx + dy * dy

        return sqrt(dist)

    @staticmethod
    def hamming(src_, dst_):
        dist = 0.0

        for i in range(src_.n * src_.n):
            dist += (src_.tiles[i] != dst_.tiles[i])

        return dist

    @staticmethod
    def linear_conflict(src_, dst_):
        # https://cse.sc.edu/~mgv/csce580sp15/gradPres/HanssonMayerYung1992.pdf
        def __conflict(src_, dst_):
            conflict = 0

            for i, src_tile_i in enumerate(src_):
                if src_tile_i != 0 and src_tile_i in dst_:
                    for j, src_tile_j in enumerate(src_):
                        if src_tile_j != 0 and src_tile_j in dst_:
                            conflict += (i > j and dst_.index(src_tile_i) < dst_.index(src_tile_j))

            return conflict

        dist = Heuristic.manhattan(src_, dst_)

        for i in range(src_.n):
            row_start = i * src_.n
            row_end = row_start + src_.n

            col_start = i
            col_step = src_.n

            dist += __conflict(src_.tiles[row_start:row_end], dst_.tiles[row_start:row_end])
            dist += __conflict(src_.tiles[col_start::col_step], dst_.tiles[col_start::col_step])

        return dist

    @staticmethod
    def uniform_cost(src_, dst_):
        return 0
