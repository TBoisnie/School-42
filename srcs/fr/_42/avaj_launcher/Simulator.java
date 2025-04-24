
package fr._42.avaj_launcher;

import java.io.FileWriter;
import java.io.IOException;


public class Simulator
{
    public static void log(String message)
    {
        try (FileWriter writer = new FileWriter("simulation.txt", true))
        {
            writer.write(message + "\n");
            writer.close();
        }
        catch (IOException e)
        {
            System.out.println("[Error][Simulator] Can not log (file not found or unexpected exception).");
        }
    }

    public static void main(String[] args)
    {
        if (args.length < 1)
        {
            System.out.println("[Error][main] Missing argument (scenario: path to the scenario file).");
            return ;
        }

        try
        {
            Scenario scenario = new Scenario(args[0]);
            scenario.reset();
            scenario.run();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
}
