#!/bin/python3

from heapq import heappop, heappush, _siftup, _siftdown

from Node import Node


class PathNotFound(Exception):
    """
    Custom Exception raised when A* does not found path.
    """
    pass


class AStar:

    @staticmethod
    def run(src_, dst_, heuristic_, metrics_, greedy_):
        closed_set = set()
        open_set = dict()
        priority_queue = []

        current = Node(src_)
        current.cost_h = heuristic_(src_, dst_)

        heappush(priority_queue, current)
        open_set[current.value.hash] = current

        open_set_size = 1
        while priority_queue:
            current = heappop(priority_queue)
            del open_set[current.value.hash]
            open_set_size -= 1

            if current.value == dst_:
                metrics_.time_complexity = len(closed_set)
                metrics_.path = AStar.__build_path(current)
                return

            closed_set.add(current)

            for node in AStar.__get_neighbors(current):
                if node in closed_set:
                    continue

                new_cost_g = current.cost_g + 1 if not greedy_ else 0 # Cost = 1 (required by subject)

                if node.value.hash not in open_set:
                    node.cost_g = new_cost_g
                    node.cost_h = heuristic_(node.value, dst_)
                    node.parent = current

                    heappush(priority_queue, node)
                    open_set[node.value.hash] = node
                    open_set_size += 1
                    metrics_.space_complexity = max(metrics_.space_complexity, open_set_size)

                else:
                    node = open_set[node.value.hash]
                    if node.cost_g > new_cost_g:
                        idx = priority_queue.index(node)

                        # Remove node (costs changed)
                        priority_queue[idx] = priority_queue[-1]
                        priority_queue.pop()
                        if idx < open_set_size-1:
                            _siftup(priority_queue, idx)
                            _siftdown(priority_queue, 0, idx)

                        # Add node (with updated values)
                        node.cost_g = new_cost_g
                        node.parent = current

                        heappush(priority_queue, node)

        metrics_.time_complexity = len(closed_set)
        raise PathNotFound

    @staticmethod
    def __get_neighbors(node_):
        coords = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        neighbors = []
        for dx, dy in coords:
            neighbor = node_.clone()

            if neighbor.value.move_to(dx, dy):
                neighbors.append(neighbor)

        return neighbors

    @staticmethod
    def __build_path(node):
        path = []

        while node is not None:
            path.insert(0, node)
            node = node.parent

        return path
