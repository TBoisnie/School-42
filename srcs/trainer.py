#!/bin/python3

import sys
import argparse

from ResourceManager import ResourceManager
from LinearRegression import GradientDescent, LeastSquare, Point
from GraphicalUserInterface import GraphicalUserInterface

if __name__ == "__main__":
    #
    # Args
    #
    parser = argparse.ArgumentParser(
        prog="trainer",
        description="Linear Regression Trainer using Gradient Descent or Least Square Algorithm.",
        allow_abbrev=False
    )

    parser.add_argument('-v',   '--visual',        action='store_true',           help='Enable Graphical User Interface (GUI).')
    parser.add_argument('-d',   '--duration',      action='store',      type=int, help='Graphical User Interface (GUI) display time (in seconds) (activate --visual flag).')
    parser.add_argument('-i',   '--input',         action='store',      type=str, help='Input file (dataset must be a CSV file).')
    parser.add_argument('-o',   '--output',        action='store',      type=str, help='Output file (informations that will be used for the estimater).')
    parser.add_argument('-alt', '--alt-algorithm', action='store_true',           help='Switch to alternative algorithm (Least Square, instead of Gradient Descent).')

    args = parser.parse_args()

    #
    # Config
    #
    config = {}
    config["visual_duration"] = abs(args.duration) if args.duration else 0
    config["visual_enabled"]  = args.visual or config["visual_duration"]
    config["file_input"]      = args.input    if args.input        else "../tests/data_0.csv"
    config["file_output"]     = args.output   if args.output       else ".infos.csv"
    config["alt_algorithm"]   = args.alt_algorithm

    #
    # Import
    #
    data = ResourceManager.readCSV(config["file_input"])

    #
    # Parse
    #
    points = []
    for i, d in enumerate(data, start=1):
        try:
            x = float(d[0])
            y = float(d[1])
        except ValueError:
            print(f"[Warning][main] Training: Ignoring row {i}: X ({d[0]}) and Y ({d[1]}) must be float.")
        else:
            points.append(Point(x, y))

    if len(points) < 2:
        sys.exit(f"[Error][main] Training: Invalid points (at least 2 are required).")

    if len(set([p.x for p in points])) < 2:
        sys.exit(f"[Error][main] Training: Invalid points (must not all be vertically aligned).")

    #
    # Training
    #
    if config["alt_algorithm"]:
        lr = LeastSquare(points)
        lr.run()
    else:
        lr = GradientDescent(points)
        lr.run()
        # lr.run(max_iteration=1e6, learning_rate=1e0, precision=1e-6)

    #
    # Export
    #
    infos = [
        ["alt_algorithm", "x_min", "x_max", "y_min", "y_max", "theta_0", "theta_1", "accuracy"],
        [int(config["alt_algorithm"]), lr.getPointsMin().x, lr.getPointsMax().x, lr.getPointsMin().y, lr.getPointsMax().y, lr.getTheta()[0], lr.getTheta()[1], lr.getAccuracy()]
    ]

    ResourceManager.writeCSV(config["file_output"], infos)

    #
    # Print
    #
    algo = "Gradient Descent" if not config['alt_algorithm'] else "Least Square"
    print(f"Algorithm: {algo}")
    print(f"Theta: {lr.getTheta()}")
    print(f"Accuracy: {lr.getAccuracy() * 100:.8}%")

    #
    # Graphical User Interface
    #
    if config["visual_enabled"]:
        gui = GraphicalUserInterface()

        for p in points:
            gui.drawPoint(p)

        xs = [ lr._points_min.x, lr._points_max.x ]
        ys = [ lr.estimate(x) for x in xs]
        gui.drawLine(xs, ys)


        if config["visual_duration"] != 0:
            gui.show()
            gui.pause(config["visual_duration"] )
            gui.close()
        else:
            gui.show(True)
            gui.close()
