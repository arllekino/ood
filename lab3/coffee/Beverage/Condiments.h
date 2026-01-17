#pragma once

#include "IBeverage.h"

class CCondimentDecorator : public IBeverage
{
public:
    [[nodiscard]] std::string GetDescription() const override
    {
        return m_beverage->GetDescription() + ", " + GetCondimentDescription();
    }

    [[nodiscard]] double GetCost() const override
    {
        return m_beverage->GetCost() + GetCondimentCost();
    }

    [[nodiscard]] virtual std::string GetCondimentDescription() const = 0;
    [[nodiscard]] virtual double GetCondimentCost() const = 0;
protected:
    explicit CCondimentDecorator(IBeveragePtr&& beverage) : m_beverage(move(beverage))
    {
    }
private:
    IBeveragePtr m_beverage;
};

class CCinnamon : public CCondimentDecorator
{
public:
	explicit CCinnamon(IBeveragePtr&& beverage)
		: CCondimentDecorator(move(beverage))
	{}
protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 20;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Cinnamon";
	}
};

class CLemon : public CCondimentDecorator
{
public:
	explicit CLemon(IBeveragePtr&& beverage, const unsigned quantity = 1)
		: CCondimentDecorator(move(beverage))
	, m_quantity(quantity)
	{}
protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 10.0 * m_quantity;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}
private:
	unsigned m_quantity;
};


enum class IceCubeType
{
	Dry,
	Water
};

class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(
		IBeveragePtr&& beverage,
		const unsigned quantity,
		const IceCubeType type = IceCubeType::Water)
			: CCondimentDecorator(move(beverage))
			, m_quantity(quantity)
			, m_type(type)
	{}
protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
	}
	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
			+ " ice cubes x " + std::to_string(m_quantity);
	}
private:
	unsigned m_quantity;
	IceCubeType m_type;
};

enum class SyrupType
{
	Chocolate,
	Maple,
};

class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, const SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{}
protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 15;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
			+ " syrup";
	}
private:
	SyrupType m_syrupType;
};

class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr&& beverage, const unsigned mass)
		:CCondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

	[[nodiscard]] double GetCondimentCost() const override
	{
		return 2.0 * m_mass;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}
private:
	unsigned m_mass;
};

class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr&& beverage, const unsigned mass)
		: CCondimentDecorator(move(beverage)),
		m_mass(mass)
	{}

protected:
	[[nodiscard]] double GetCondimentCost() const override
	{
		return 1.0 * m_mass;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}
private:
	unsigned m_mass;
};

class Cream : public CCondimentDecorator
{
public:
	explicit Cream(IBeveragePtr&& beverage) : CCondimentDecorator(move(beverage))
	{
	}

	[[nodiscard]] double GetCondimentCost() const override
	{
		return 25;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "With Cream";
	}
};

class Chocolate : public CCondimentDecorator
{
public:
	explicit Chocolate(IBeveragePtr&& beverage, const unsigned sliceCount)
		: CCondimentDecorator(move(beverage)),
		m_sliceCount(sliceCount)
	{
		if (m_sliceCount > 5)
		{
			throw std::invalid_argument("Max chocolate slice count is 5");
		}
	}

	[[nodiscard]] double GetCondimentCost() const override
	{
		return 10 * m_sliceCount;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return "Count of chocolate slices " + std::to_string(m_sliceCount);
	}
private:
	unsigned m_sliceCount;
};

enum class LiquorType
{
	NUTTY, CHOCOLATE
};

class Liquor : public CCondimentDecorator
{
public:
	explicit Liquor(IBeveragePtr&& beverage, const LiquorType liquorType)
		: CCondimentDecorator(move(beverage)),
		m_liquorType(liquorType)
	{
	}

	[[nodiscard]] double GetCondimentCost() const override
	{
		return 50;
	}

	[[nodiscard]] std::string GetCondimentDescription() const override
	{
		return GetLiquorDescriptionAsString() + " liquor";
	}
private:
	LiquorType m_liquorType;

	[[nodiscard]] std::string GetLiquorDescriptionAsString() const
	{
		switch (m_liquorType)
		{
			case LiquorType::NUTTY:
				return "Nutty";
			case LiquorType::CHOCOLATE:
				return "Chocolate";
			default:
				return "Unknown";
		}
	}
};