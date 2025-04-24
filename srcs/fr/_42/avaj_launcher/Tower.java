
package fr._42.avaj_launcher;

import java.util.ArrayList;


class Tower
{
    private ArrayList<Flyable> observers = new ArrayList<>();

    public void register(Flyable flyable)
    {
        this.observers.add(flyable);
    }

    public void unregister(Flyable flyable)
    {
        this.observers.remove(flyable);
    }

    protected void conditionsChanged()
    {
        ArrayList<Flyable> iterable = new ArrayList<>(this.observers);

        for (Flyable flyable: iterable)
        {
            flyable.updateConditions();
        }
    }
}
