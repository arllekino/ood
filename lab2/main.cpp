//
// Created by Miroslav Aktuganov on 15.09.2025.
//

#include "./Observer/WeatherData.h"

int main()
{
    CWeatherData wd;

    CDisplay display;
    wd.RegisterObserver(display, 0);

    CStatsDisplay statsDisplay;
    wd.RegisterObserver(statsDisplay, 0);

    wd.SetMeasurements(3, 0.7, 760, 20, -361);
    wd.SetMeasurements(4, 0.8, 761, 20, -361);

    wd.RemoveObserver(statsDisplay);

    wd.SetMeasurements(10, 0.8, 761, 20, -361);
    wd.SetMeasurements(-10, 0.8, 761, 20, -361);
    return 0;
}