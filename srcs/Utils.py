#!/bin/python3


class Utils:

    @staticmethod
    def print_matrix(matrix_):
        size = len(matrix_)
        width = len(str(size*size))

        for row in matrix_:
            print((f"%{width}i " * len(row))[:-1] % tuple(row))

    @staticmethod
    def list_to_matrix(list_, n_):
        return [ list_[i:i+n_] for i in range(0, n_ * n_, n_) ]

    @staticmethod
    def matrix_to_list(matrix_):
        return [ component for row in matrix_ for component in row ]

    @staticmethod
    def matrix_to_list_snail(matrix_):
        return list(matrix_[0]) + Utils.matrix_to_list_snail(list(zip(*matrix_[1:]))[::-1]) if matrix_ else []

    @staticmethod
    def matrix_generate_snail(n_):
        numbers = [ *range(1, n_ * n_) ] + [0]
        matrix  = [ [0] * n_ for _ in range(n_) ]

        dir = (0, 1, 0, -1, 0)
        p = 0
        x = 0
        y = 0

        for number in numbers:
            matrix[y][x] = number

            new_y = y + dir[p]
            new_x = x + dir[p+1]

            if (not 0 <= new_y < n_) or (not 0 <= new_x < n_) or matrix[new_y][new_x] != 0:
                p = (p + 1) % 4
                new_y = y + dir[p]
                new_x = x + dir[p + 1]

            y = new_y
            x = new_x

        return matrix
