#pragma once

#include <string>
#include <memory>
#include <vector>
#include <type_traits>


enum class Material
{
	SyntheticRubber,
	Naturalrubber,
	CarbonBlack
};

class Engine
{
	int m_power;
public:
	explicit Engine( int power = 100 )
		:
		m_power{power}
	{}

	int getPower() const noexcept
	{
		return m_power;
	}
};

class Tire
{
public:
	Material m_material;
};

class StandardTire
	: public Tire
{

};

class HeavyDutyTire
	: public Tire
{

};


class Car
{
	using Tires = std::vector<Tire>;

	enum class Type
	{
		Family,
		Sports,
		Truck
	};

	float m_weight;		// tonnes
	float m_width = 2;	// meteres
	int m_doorCount = 4;
	int m_tireCount = 4;
	Type m_type;
	std::unique_ptr<Engine> m_pEngine;
	Tires m_tires;
	std::wstring m_color;
	std::wstring m_name;

	unsigned m_mileage = 0;	// km - metric	// always is the same initial value

public:
	Car( float weight,
		float width,
		int doorCount,
		int tireCount,
		Type type,
		std::unique_ptr<Engine> peng,
		const Tires& tires,
		const std::wstring& color,
		const std::wstring& name )
		:
		m_weight{weight},
		m_width{width},
		m_doorCount{doorCount},
		m_tireCount{tireCount},
		m_type{type},
		m_pEngine{std::move( peng )},
		m_tires{tires},
		m_color{color},
		m_name{name}
	{
		std::wcout << name << L" created!" << L'\n';
	}

	////////////////////////////
	class Builder final
	{
		float m_weight;	// tonnes
		float m_width = 2;
		int m_doorCount = 4;
		int m_tireCount = 4;
		int m_power;
		Tires m_tires;
		Material m_material;
		std::wstring m_name;		///!///
		std::wstring m_color;

		template<typename T>
		Tires createWheels() const
		{
			static_assert( std::is_base_of_v<Tire, T>,
				"T must be a subclass of Tire" );

			Tires tires;
			for ( auto i = 0; i < m_tireCount; ++i )
			{
				tires.emplace_back( T{m_material} );
			}
			return tires;
		}
	public:
		Builder() = default;

		std::unique_ptr<Car> create() const
		{
			Type type;
			if ( m_power > 2000 )
			{
				type = ( m_tireCount > 4 ) ?
					Type::Truck
					: Type::Sports;
			}
			else
			{
				type = Type::Family;
			}
			
			Tires tires;
			if ( m_tireCount > 4 )
			{
				tires = createWheels<HeavyDutyTire>();
			}
			else
			{
				tires = createWheels<StandardTire>();
			}

			return std::make_unique<Car>( m_weight,
				m_width,
				m_doorCount,
				m_tireCount,
				type,
				std::make_unique<Engine>( m_power ),
				std::move( tires ),
				m_color,
				m_name );
		}

		// SETTERS
		Builder& setWeight( float value ) noexcept
		{
			m_weight = value;
			return *this;
		}
		Builder& setWidth( float value ) noexcept
		{
			m_width = value;
			return *this;
		}
		Builder& setDoorCount( int value ) noexcept
		{
			m_doorCount = value;
			return *this;
		}
		Builder& setTireCount( int value ) noexcept
		{
			m_tireCount = value;
			return *this;
		}
		Builder& setPower( int value ) noexcept
		{
			m_power = value;
			return *this;
		}
		Builder& setColor( const std::wstring& value ) noexcept
		{
			m_color = value;
			return *this;
		}
		Builder& setName( const std::wstring& value ) noexcept
		{
			m_name = value;
			return *this;
		}
		Builder& setMaterial( const Material& value ) noexcept
		{
			m_material = value;
			return *this;
		}
	};
	//////////////////////////////////////////////////////////////////////
	~Car()
	{
		std::wcout << m_name
			<< L" destroyed!"
			<< L'\n';
	}

	void present()
	{
		std::wcout	<< L"This is " << m_name
			<< " ready to cruise the vast landscapes and the infinite roads of the world\n"
			<< L"weight:" << m_weight << L'\n'
			<< L"width:" << m_width << L'\n'
			<< L"door count:" << m_doorCount << L'\n'
			<< L"tire count:" << m_tireCount << L'\n'
			<< L"engine power = " << m_pEngine->getPower() << L'\n'
			<< L"color:" << m_color << L'\n'
			<< L"mileage:" << m_mileage << L'\n'
			<< L'\n';
	}

	void cruise() noexcept
	{
		m_mileage += 40;
		std::wcout << L'\n'
			<< L"\nCruising ..\n"
			<< L'\n';
	}

	Car( const Car& rhs) = delete;
	Car& operator=( const Car& rhs) = delete;

	// TODO: implement the mctor & maop as well
};
