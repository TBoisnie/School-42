
package fr._42.avaj_launcher;


class Baloon
    extends Aircraft
    implements Flyable
{
    private WeatherTower weatherTower;

    Baloon(String name, Coordinates coordinates)
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
                this.coordinates.setHeight(this.coordinates.getHeight() + 4);
                this.coordinates.setLongitude(this.coordinates.getLongitude() + 2);
                this.log("Let's enjoy the good weather and take some pics.");
                break;
            case "RAIN":
                this.coordinates.setHeight(this.coordinates.getHeight() - 5);
                this.log("Damn you rain! You messed up my baloon.");
                break;
            case "FOG":
                this.coordinates.setHeight(this.coordinates.getHeight() - 3);
                this.log("Can't see anything. Beware the mountain!");
                break;
            case "SNOW":
                this.coordinates.setHeight(this.coordinates.getHeight() - 15);
                this.log("It's snowing. We're gonna crash.");
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
