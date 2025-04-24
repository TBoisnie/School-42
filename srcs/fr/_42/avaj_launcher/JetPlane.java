
package fr._42.avaj_launcher;


class JetPlane
    extends Aircraft
    implements Flyable
{
    private WeatherTower weatherTower;

    JetPlane(String name, Coordinates coordinates)
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
                this.coordinates.setLatitude(this.coordinates.getLatitude() + 10);
                this.log("Watch more sunsets than Netflix.");
                break;
            case "RAIN":
                this.coordinates.setLatitude(this.coordinates.getLatitude() + 5);
                this.log("It's raining. Better watch out for lightings.");
                break;
            case "FOG":
                this.coordinates.setLatitude(this.coordinates.getLatitude() + 1);
                this.log("Head (literally) in the clouds.");
                break;
            case "SNOW":
                this.coordinates.setHeight(this.coordinates.getHeight() - 7);
                this.log("OMG! Winter is coming!");
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
