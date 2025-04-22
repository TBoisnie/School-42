#!/bin/python3

import sys
import argparse

from ResourceManager import ResourceManager
from LinearRegression import GradientDescent, LeastSquare

if __name__ == "__main__":
    #
    # Args
    #
    parser = argparse.ArgumentParser(
        prog="estimater",
        description="Linear Regression Estimater.",
        allow_abbrev=False
    )

    parser.add_argument('-i', '--input', action='store', type=str, help='Input file (informations must be a CSV file).')

    args = parser.parse_args()

    #
    # Config
    #
    config = {}
    config["file_input"] = args.input if args.input else ".infos.csv"

    #
    # Import
    #
    data = ResourceManager.readCSV(config["file_input"])

    #
    # Parse
    #
    if len(data) < 2:
        sys.exit(f"[Error][main] Estimate: Invalid informations file (Empty).")

    infos = {
        "alt_algorithm" : False,
        "x_min" : 0.0,
        "x_max" : 0.0,
        "y_min" : 0.0,
        "y_max" : 0.0,
        "theta_0" : 0.0,
        "theta_1" : 0.0,
        "accuracy" : 0.0
    }

    for field in infos.keys():
        try:
            index = data[0].index(field)
            if index >= len(data[1]):
                raise ValueError
        except ValueError:
            sys.exit(f"[Error][main] Estimate: Missing information ({field}).")

        try:
            value = float(data[1][index])
        except ValueError:
            sys.exit(f"[Error][main] Estimate: Invalid information ({field} = {data[1][index]}).")

        infos[field] = value if field not in ["alt_algorithm"] else bool(value)

    #
    # Estimate
    #
    lr = LeastSquare([]) if infos["alt_algorithm"] else GradientDescent([])
    lr.setPointsMin(infos['x_min'], infos['y_min'])
    lr.setPointsMax(infos['x_max'], infos['y_max'])
    lr.setAccuracy(infos['accuracy'])
    lr.setTheta(infos['theta_0'], infos['theta_1'])

    #
    # Prompt
    #
    mileage_unsafe = input("Mileage: ")

    try:
        mileage = float(mileage_unsafe)
    except ValueError:
        sys.exit("[Error][Main] Prompt: Invalid mileage (must be a number).")

    #
    # Print
    #
    print(f"Estimation: {lr.estimate(mileage)}")
    print(f"Accuracy: {lr.getAccuracy() * 100:.8}%")

