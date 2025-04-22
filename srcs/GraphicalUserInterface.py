#!/bin/python3

import matplotlib.pyplot as pp
from LinearRegression import Point


class GraphicalUserInterface:

    def __init__(self):
        self.activeFigure()

    def activeFigure(self, index=1):
        pp.figure(index)

    def drawPoint(self, point):
        pp.plot(point.x, point.y, color='black', marker='+')
        pp.draw()

    def drawHighlightPoint(self, point):
        pp.plot(point.x, point.y, color='magenta', marker='o')
        pp.draw()

    def drawLine(self, x, y):
        pp.plot(x, y, color='green', linestyle='-')
        pp.draw()

    def show(self, blocking=False):
        pp.show(block=blocking)

    def pause(self, time):
        pp.pause(time)

    def close(self):
        pp.close()


if __name__ == "__main__":
    gui = GraphicalUserInterface()

    gui.activeFigure()
    gui.drawPoint(Point(1.5, 4.1))
    gui.drawPoint(Point(5.4, 1.3))
    gui.drawPoint(Point(2.3, 2.7))
    gui.drawPoint(Point(3.7, 3.9))
    gui.drawHighlightPoint(Point(3.0, 4.0))
    gui.drawLine([0.5, 6.5], [2, 4.5])

    gui.activeFigure(2)
    gui.drawHighlightPoint(Point(3.0, 4.0))
    gui.drawLine([0.5, 6.5], [4.5, 2])

    gui.show()
    gui.pause(5)
    gui.close()