
package fr._42.avaj_launcher;


class Helicopter
    extends Aircraft
    implements Flyable
{
    private WeatherTower weatherTower;

    Helicopter(String name, Coordinates coordinates)
    {
        super(name, coordinates);
    }

    public void registerTower(WeatherTower weatherTower)
    {
        if (this.weatherTower != null)
        {
            this.weatherTower.unregister(this);
            Simulator.log("Tower says: " + this.getLogIdentifier() + " unregistered to weather tower.");
        }

        this.weatherTower = weatherTower;

        if (this.weatherTower != null)
        {
            this.weatherTower.register(this);
            Simulator.log("Tower says: " + this.getLogIdentifier() + " registered to weather tower.");
        }
    }

    public void updateConditions()
    {
        String weather = this.weatherTower.getWeather(coordinates);

        switch (weather)
        {
            case "SUN":
                this.coordinates.setHeight(this.coordinates.getHeight() + 2);
                this.coordinates.setLongitude(this.coordinates.getLongitude() + 10);
                this.log("A helicopter is just like a flying ceiling fan.");
                break;
            case "RAIN":
                this.coordinates.setLongitude(this.coordinates.getLongitude() + 5);
                this.log("The most important is to focus on something else.");
                break;
            case "FOG":
                this.coordinates.setLongitude(this.coordinates.getLongitude() + 1);
                this.log("Oh Sh*t. Here we go again.");
                break;
            case "SNOW":
                this.coordinates.setHeight(this.coordinates.getHeight() - 12);
                this.log("My rotor is going to freeze!");
                break;
            default:
                break;
        }

        if (this.coordinates.getHeight() <= 0)
        {
            Simulator.log(
                this.getLogIdentifier() + " landing (" +
                Integer.toString(this.coordinates.getLatitude()) + ", " +
                Integer.toString(this.coordinates.getLongitude()) + ", " +
                Integer.toString(this.coordinates.getHeight()) + ")."
            );
            this.registerTower(null);
        }
    }
}
