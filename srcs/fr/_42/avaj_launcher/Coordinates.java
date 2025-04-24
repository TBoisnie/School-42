
package fr._42.avaj_launcher;


class Coordinates
{
    private int longitude;
    private int latitude;
    private int height;

    Coordinates(int longitude, int latitude, int height)
    {
        this.setLongitude(longitude);
        this.setLatitude(latitude);
        this.setHeight(height);
    }

    public int getLongitude()
    {
        return this.longitude;
    }

    public void setLongitude(int longitude)
    {
        this.longitude = longitude;
    }

    public int getLatitude()
    {
        return this.latitude;
    }

    public void setLatitude(int latitude)
    {
        this.latitude = latitude;
    }

    public int getHeight()
    {
        return this.height;
    }

    public void setHeight(int height)
    {
        this.height = Math.max(0, Math.min(height, 100));
    }
}
