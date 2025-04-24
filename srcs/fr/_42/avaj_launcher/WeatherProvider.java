
package fr._42.avaj_launcher;


class WeatherProvider
{
    private static String[] weather = {"RAIN", "FOG", "SUN", "SNOW"};
    private static WeatherProvider weatherProvider;

    private WeatherProvider()
    {
        // Private constructor (Singleton)
    }

    public static WeatherProvider getProvider()
    {
        if (weatherProvider == null)
            weatherProvider = new WeatherProvider();

        return weatherProvider;
    }

    public String getCurrentWeather(Coordinates coordinates)
    {
        int x = coordinates.getLongitude();
        int y = coordinates.getLatitude();
        int z = coordinates.getHeight();

        int distance = (int) Math.sqrt(x * x + y * y + z * z);

        return weather[distance % weather.length];
    }
}
