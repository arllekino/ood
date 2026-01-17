#pragma once
#include <iostream>
#include <unordered_set>

#include "IObserver.h"
#include "WeatherDataCharacteristicStat.h"

enum class WeatherEventType
{
	TEMPERATURE,
	HUMIDITY,
	PRESSURE,
	WIND_SPEED,
	WIND_DIRECTION
};

struct SWeatherInfo
{
	std::unordered_map<WeatherEventType, double> availableEvents;
};

class CDisplay final : public IObserver<SWeatherInfo>
{
public:
	void Update(const IObservable<SWeatherInfo>& observable, const SWeatherInfo& data) override
	{
		if (data.availableEvents.contains(WeatherEventType::TEMPERATURE))
			std::cout << "Current Temp " << data.availableEvents.at(WeatherEventType::TEMPERATURE) << std::endl;
		if (data.availableEvents.contains(WeatherEventType::HUMIDITY))
			std::cout << "Current Hum " << data.availableEvents.at(WeatherEventType::HUMIDITY) << std::endl;
		if (data.availableEvents.contains(WeatherEventType::PRESSURE))
			std::cout << "Current Pressure " << data.availableEvents.at(WeatherEventType::PRESSURE) << std::endl;
		if (data.availableEvents.contains(WeatherEventType::WIND_SPEED))
			std::cout << "Current Wind Speed " << data.availableEvents.at(WeatherEventType::WIND_SPEED) << std::endl;
		if (data.availableEvents.contains(WeatherEventType::WIND_DIRECTION))
			std::cout << "Current Wind Direction " << data.availableEvents.at(WeatherEventType::WIND_DIRECTION) << std::endl;
		if (!data.availableEvents.empty())
			std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay final : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStat(WeatherDataCharacteristicStat("Temperature")),
		m_humidityStat(WeatherDataCharacteristicStat("Humidity")),
		m_pressureStat(WeatherDataCharacteristicStat("Pressure")),
		m_windSpeedStat(WeatherDataCharacteristicStat("Wind Speed")),
		m_windDirectionStat(WeatherDataCharacteristicStat("Wind Direction"))
	{
	}

	void Update(const IObservable<SWeatherInfo>& observable, const SWeatherInfo& data) override
	{
		if (data.availableEvents.contains(WeatherEventType::TEMPERATURE))
			UpdateTemperature(data.availableEvents.at(WeatherEventType::TEMPERATURE));
		if (data.availableEvents.contains(WeatherEventType::HUMIDITY))
			UpdateHumidity(data.availableEvents.at(WeatherEventType::HUMIDITY));
		if (data.availableEvents.contains(WeatherEventType::PRESSURE))
			UpdatePressure(data.availableEvents.at(WeatherEventType::PRESSURE));
		if (data.availableEvents.contains(WeatherEventType::WIND_SPEED))
			UpdateWindSpeed(data.availableEvents.at(WeatherEventType::WIND_SPEED));
		if (data.availableEvents.contains(WeatherEventType::WIND_DIRECTION))
			UpdateWindDirection(data.availableEvents.at(WeatherEventType::WIND_DIRECTION));
	}

	void AddObservable(IObservable<SWeatherInfo>* observable)
	{
		m_observables.insert(observable);
	}

private:
	WeatherDataCharacteristicStat m_temperatureStat;
	WeatherDataCharacteristicStat m_humidityStat;
	WeatherDataCharacteristicStat m_pressureStat;
	WeatherDataCharacteristicStat m_windSpeedStat;
	WeatherDataCharacteristicStat m_windDirectionStat;

	std::set<IObservable<SWeatherInfo>*> m_observables{};

	void UpdateTemperature(const double temperature)
	{
		m_temperatureStat.UpdateStat(temperature);
		m_temperatureStat.PrintStat();
	}

	void UpdateHumidity(const double humidity)
	{
		m_humidityStat.UpdateStat(humidity);
		m_humidityStat.PrintStat();
	}

	void UpdatePressure(const double pressure)
	{
		m_pressureStat.UpdateStat(pressure);
		m_pressureStat.PrintStat();
	}

	void UpdateWindSpeed(const double windSpeed)
	{
		m_windSpeedStat.UpdateStat(windSpeed);
		m_windSpeedStat.PrintStat();
	}

	void UpdateWindDirection(const double windDirection)
	{
		m_windDirectionStat.UpdateStat(windDirection);
		m_windDirectionStat.PrintStat();
	}
};

class CWeatherData final : public CObservable<SWeatherInfo>
{
public:
	CWeatherData() : m_availableEvents({
		{WeatherEventType::HUMIDITY, 0},
		{WeatherEventType::PRESSURE, 0},
		{WeatherEventType::WIND_SPEED, 0},
		{WeatherEventType::TEMPERATURE, 0},
		{WeatherEventType::WIND_DIRECTION, 0} })
	{
	}

	explicit CWeatherData(const std::unordered_set<WeatherEventType>& availableEvents)
	{
		for (const auto& event : availableEvents) {
			m_availableEvents.emplace(event, 0.0);
		}
	}

	[[nodiscard]] std::unordered_map<WeatherEventType, double> GetAvailableEvents() const
	{
		return m_availableEvents;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	// правильно считать direction
	void SetMeasurements(
		const double temp,
		const double humidity,
		const double pressure,
		const double windSpeed,
		const int windDirection)
	{
		constexpr int maxWindDirection = 360;
		auto validWindDirection = windDirection % maxWindDirection;
		validWindDirection = windDirection < 0
			? validWindDirection + maxWindDirection
			: validWindDirection;
		if (m_availableEvents.contains(WeatherEventType::TEMPERATURE))
			m_availableEvents.insert({WeatherEventType::TEMPERATURE, temp});
		if (m_availableEvents.contains(WeatherEventType::HUMIDITY))
			m_availableEvents.insert({WeatherEventType::HUMIDITY, humidity});
		if (m_availableEvents.contains(WeatherEventType::PRESSURE))
			m_availableEvents.insert({WeatherEventType::PRESSURE, pressure});
		if (m_availableEvents.contains(WeatherEventType::WIND_SPEED))
			m_availableEvents.insert({WeatherEventType::WIND_SPEED, windSpeed});
		if (m_availableEvents.contains(WeatherEventType::WIND_DIRECTION))
			m_availableEvents.insert({WeatherEventType::WIND_DIRECTION, validWindDirection});

		MeasurementsChanged();
	}

	void AddAvailableEvent(const WeatherEventType event, const double value)
	{
		m_availableEvents.insert({event, value});
	}

	void RemoveAvailableEvent(const WeatherEventType event)
	{
		m_availableEvents.erase(event);
	}
protected:
	[[nodiscard]] SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.availableEvents = GetAvailableEvents();
		return info;
	}
private:
	std::unordered_map<WeatherEventType, double> m_availableEvents;
};