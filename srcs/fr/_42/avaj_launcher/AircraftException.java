
package fr._42.avaj_launcher;


class AircraftException
    extends Exception
{
    AircraftException(String message)
    {
        super("[Error][Aircraft]" + message);
    }
}

class AircraftInvalidTypeException
    extends AircraftException
{
    AircraftInvalidTypeException(String type)
    {
        super(" Type `" + type + "` does not exit.");
    }
}

class AircraftNotImplementedException
    extends AircraftException
{
    AircraftNotImplementedException(String type)
    {
        super(" Class `" + type + "` does not exit.");
    }
}
