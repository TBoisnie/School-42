#!/bin/python3

import sys
import csv

class ResourceManager:

    @classmethod
    def readCSV(cls, filepath):
        data = []

        try:
            f = open(filepath, 'r')
        except EnvironmentError:
            sys.exit(f"[Error][ResourceManager.readCSV] Could not open `{filepath}`.")
        else:
            with f:
                content = csv.reader(f, delimiter=',')
                for row in content:
                    data.append(row)

        return data

    @classmethod
    def writeCSV(cls, filepath, content):
        try:
            f = open(filepath, 'w')
        except EnvironmentError:
            sys.exit(f"[Error][ResourceManager.writeCSV] Could not open `{filepath}`.")
        else:
            with f:
                writer = csv.writer(f, delimiter=',')
                for row in content:
                    writer.writerow(row)


if __name__ == "__main__":
    filepath = ".test.csv"
    ResourceManager.writeCSV(filepath, [["theta_0", "theta_1"], [-1.0, -1.0]])
    print(ResourceManager.readCSV(filepath))
