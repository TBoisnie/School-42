
package fr._42.avaj_launcher;


class WeatherTower
    extends Tower
{
    public String getWeather(Coordinates coordinates)
    {
        return WeatherProvider.getProvider().getCurrentWeather(coordinates);
    }

    void changeWeather()
    {
        this.conditionsChanged();
    }
}
