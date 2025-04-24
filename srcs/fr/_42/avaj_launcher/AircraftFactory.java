
package fr._42.avaj_launcher;

import java.lang.reflect.Constructor;
import java.util.Set;


class AircraftFactory
{
    public final static Set<String> TYPES = Set.of("Baloon", "Helicopter", "JetPlane");

    public static Flyable newAircraft(String type, String name, int longitude, int latitude, int height)
        throws AircraftInvalidTypeException, AircraftNotImplementedException
    {
        if (type == null)
            throw new AircraftInvalidTypeException("NULL");

        if (!TYPES.contains(type))
            throw new AircraftInvalidTypeException(type);

        Object obj;

        try
        {
            Class<?> cls = Class.forName(Aircraft.class.getPackageName() + "." + type);
            Constructor<?> ctor = cls.getDeclaredConstructor(String.class, Coordinates.class);
            obj = ctor.newInstance(name, new Coordinates(longitude, latitude, height));
        }
        catch (Exception e)
        {
            throw new AircraftNotImplementedException(type);
        }

        return (Flyable) obj;
    }
}
