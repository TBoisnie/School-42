# 42 - Misc - Avaj Launcher

Implementation in `Java` of a given `UML` diagram, simulating a Control Tower managing various Aircraft positions.

## Requirements

- [Java](https://www.java.com/en/)

## Getting Started

1. Compile

	```sh
	# Create bins directory
	mkdir -p ./bins

	# List source files
	find ./srcs/* -name "*.java" > ./bins/sources.txt

	# Compile
	javac -d ./bins '@./bins/sources.txt'
	```

1. Execute

	```sh
	# Run
	java -classpath ./bins fr._42.avaj_launcher.Simulator ./tests/scenario_0.txt
	```

1. Output

	```sh
	# Show
	cat ./simulation.txt
	```

1. All-In-One

	```sh
	# Change directory
	cd ./tests

	# Run
	./simulate.sh scenario_0.txt
	```

## Example

```sh
> ./simulate.sh scenario_1.txt

--Listing: *.java > source.txt
--Compiling: @sources.txt
--Cleaning: simulation.txt
--Starting: simulator
--Output:
Tower says: Baloon#B1(1) registered to weather tower.
Tower says: Baloon#B2(2) registered to weather tower.
Tower says: JetPlane#J1(3) registered to weather tower.
Tower says: Helicopter#H1(4) registered to weather tower.
Baloon#B1(1): It's snowing. We're gonna crash.
Baloon#B1(1) landing (3, 2, 0).
Tower says: Baloon#B1(1) unregistered to weather tower.
Baloon#B2(2): Let's enjoy the good weather and take some pics.
JetPlane#J1(3): OMG! Winter is coming!
Helicopter#H1(4): My rotor is going to freeze!
Baloon#B2(2): Let's enjoy the good weather and take some pics.
JetPlane#J1(3): OMG! Winter is coming!
Helicopter#H1(4): A helicopter is just like a flying ceiling fan.
Baloon#B2(2): Let's enjoy the good weather and take some pics.
JetPlane#J1(3): It's raining. Better watch out for lightings.
Helicopter#H1(4): The most important is to focus on something else.
Baloon#B2(2): Let's enjoy the good weather and take some pics.
JetPlane#J1(3): Head (literally) in the clouds.
Helicopter#H1(4): Oh Sh*t. Here we go again.
Baloon#B2(2): Let's enjoy the good weather and take some pics.
JetPlane#J1(3): Head (literally) in the clouds.
Helicopter#H1(4): A helicopter is just like a flying ceiling fan.

```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
