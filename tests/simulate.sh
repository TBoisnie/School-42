#!/usr/bin/env sh

SCENARIO=$1

mkdir -p ../bins

cd ../srcs
echo "--Listing: *.java > source.txt"
find * -name "*.java" > ../bins/sources.txt

echo "--Compiling: @sources.txt"
javac -d ../bins @../bins/sources.txt

cd ../bins
echo "--Cleaning: simulation.txt"
rm simulation.txt > /dev/null 2>&1
echo "--Starting: simulator"
java fr._42.avaj_launcher.Simulator ../tests/$SCENARIO

echo "--Output:"
cat ../bins/simulation.txt
