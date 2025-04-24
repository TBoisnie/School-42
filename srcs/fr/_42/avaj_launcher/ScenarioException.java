
package fr._42.avaj_launcher;


class ScenarioException
    extends Exception
{
    ScenarioException(String message)
    {
        super("[Error][Scenario]" + message);
    }
}

class ScenarioInvalidIterationException
    extends ScenarioException
{
    ScenarioInvalidIterationException()
    {
        super(" Iteration must be an integer greater than 0 (> 0).");
    }
}

class ScenarioAircraftFormatException
    extends ScenarioException
{
    ScenarioAircraftFormatException()
    {
        super(" Aircraft format must be like : \"type name longitude latitude height\".");
    }
}

class ScenarioAircraftTypeException
    extends ScenarioException
{
    ScenarioAircraftTypeException()
    {
        super(" Aircraft type does not exist.");
    }
}

class ScenarioAircraftCoordinatesException
    extends ScenarioException
{
    ScenarioAircraftCoordinatesException()
    {
        super(" Aircraft coordinates must be integer greater than or equals to 0 (>= 0).");
    }
}

class ScenarioEmptyException
    extends ScenarioException
{
    ScenarioEmptyException()
    {
        super(" Nothing to simulate (at least 1 aircraft is required).");
    }
}
