
package fr._42.avaj_launcher;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


class Scenario
{
    private ArrayList<Flyable> flyables;
    private String filepath;
    private int iteration;

    public Scenario(String filepath)
    {
        this.flyables = new ArrayList<>();
        this.filepath = filepath;
        this.iteration = 0;
    }

    public void run()
    {
        WeatherTower weatherTower = new WeatherTower();

        for (Flyable flyable: this.flyables)
        {
            flyable.registerTower(weatherTower);
        }

        for (int i = 0; i < iteration; ++i)
        {
            weatherTower.changeWeather();
        }
    }

    public void reset()
        throws Exception
    {
        this.flyables.clear();
        this.iteration = 0;

        try (BufferedReader reader = new BufferedReader(new FileReader(this.filepath)))
        {
            String line = reader.readLine();

            while (line != null)
            {
                String[] fields = line.split(" ");

                if (fields.length == 0)
                {
                    // Do nothing
                }
                // Iteration
                else if (this.iteration == 0)
                {

                    if (fields.length != 1)
                        throw new ScenarioInvalidIterationException();

                    try
                    {
                        this.iteration = Integer.parseInt(fields[0]);
                    }
                    catch (NumberFormatException e)
                    {
                        throw new ScenarioInvalidIterationException();
                    }

                    if (this.iteration <= 0)
                        throw new ScenarioInvalidIterationException();
                }
                // Aircraft
                else
                {
                    if (fields.length != 5)
                        throw new ScenarioAircraftFormatException();

                    String type = fields[0];
                    if (!AircraftFactory.TYPES.contains(type))
                        throw new ScenarioAircraftTypeException();

                    String name = fields[1];

                    int longitude = 0;
                    int latitude = 0;
                    int height = 0;
                    try
                    {
                        longitude = Integer.parseInt(fields[2]);
                        latitude = Integer.parseInt(fields[3]);
                        height = Integer.parseInt(fields[4]);
                    }
                    catch (NumberFormatException e)
                    {
                        throw new ScenarioAircraftCoordinatesException();
                    }

                    if (longitude < 0 || latitude < 0 || height < 0)
                        throw new ScenarioAircraftCoordinatesException();

                    this.flyables.add(AircraftFactory.newAircraft(type, name, longitude, latitude, height));
                }

                line = reader.readLine();
            }

            reader.close();
        }
        catch (IOException e)
        {
            throw new Exception("[Error][Scenario] File not found or invalid format.");
        }

        if (this.flyables.isEmpty())
        {
            throw new ScenarioEmptyException();
        }
    }
}
