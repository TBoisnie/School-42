
package fr._42.avaj_launcher;


class Aircraft
{
    protected long id;
    protected String name;
    protected Coordinates coordinates;
    private static long idCounter;

    protected Aircraft(String name, Coordinates coordinates)
    {
        this.id = this.nextId();
        this.name = name;
        this.coordinates = coordinates;
    }

    protected void log(String message)
    {
        Simulator.log(this.getLogIdentifier() + ": " + message);
    }

    protected String getLogIdentifier()
    {
        return this.getClass().getSimpleName() + "#" + this.name + "(" + this.id + ")";
    }

    private long nextId()
    {
        return ++idCounter;
    }
}
