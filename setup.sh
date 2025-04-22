#!/usr/bin/env bash

# Create a virtual environment
echo "Setting up the virtual environment..."
python -m venv .venv

# Install dependencies
echo "Installing the dependencies..."
.venv/bin/python -m pip install --upgrade pip
.venv/bin/python -m pip install numpy matplotlib
