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
	explicit Engine( int power = 100 );
	int getPower() const noexcept;
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

	float m_weight;		// tonnes
	float m_width = 2;	// meters
	int m_doorCount = 4;
	int m_tireCount = 4;
	enum class Type
	{
		Family,
		Sports,
		Truck
	} m_type;
	std::unique_ptr<Engine> m_pEngine;
	Tires m_tires;
	std::string m_color;
	std::string m_name;
	unsigned m_mileage = 0;	// km - metric	// always is the same initial value

public:
	Car( float weight, float width, int doorCount, int tireCount, Type type,
		std::unique_ptr<Engine> peng, const Tires& tires, const std::string& color,
		const std::string& name );
	~Car();
	Car( const Car& rhs) = delete;
	Car& operator=( const Car& rhs) = delete;

	Car( Car&& rhs ) noexcept
		:
		m_weight{rhs.m_weight},
		m_width{rhs.m_width},
		m_doorCount{rhs.m_doorCount},
		m_tireCount{rhs.m_tireCount},
		m_type{rhs.m_type},
		m_pEngine{std::move( rhs.m_pEngine )},
		m_tires{std::move( rhs.m_tires )},
		m_color{std::move( rhs.m_color )},
		m_name{std::move( rhs.m_name )},
		m_mileage{rhs.m_mileage}
	{

	}
	
	Car& operator=( Car&& rhs ) noexcept
	{
		m_weight = rhs.m_weight;
		m_width = rhs.m_width;
		m_doorCount = rhs.m_doorCount;
		m_tireCount = rhs.m_tireCount;
		m_type = rhs.m_type;
		std::swap( m_pEngine, rhs.m_pEngine );
		std::swap( m_tires, rhs.m_tires );
		std::swap( m_color, rhs.m_color );
		std::swap( m_name, rhs.m_name );
		m_mileage = rhs.m_mileage;
		return *this;
	}

	class Builder final
	{
		float m_weight;
		float m_width = 2;
		int m_doorCount = 4;
		int m_tireCount = 4;
		int m_power;
		Tires m_tires;
		Material m_material;
		std::string m_name;
		std::string m_color;

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

		std::unique_ptr<Car> create() const;

		// SETTERS
		Builder& setWeight( float value ) noexcept;
		Builder& setWidth( float value ) noexcept;
		Builder& setDoorCount( int value ) noexcept;
		Builder& setTireCount( int value ) noexcept;
		Builder& setPower( int value ) noexcept;
		Builder& setColor( const std::string& value ) noexcept;
		Builder& setName( const std::string& value ) noexcept;
		Builder& setMaterial( const Material& value ) noexcept;
	};
	//////////////////////////////////////////////////////////////////////

	void present();
	void cruise() noexcept;

	// Car Setters/Getters
};