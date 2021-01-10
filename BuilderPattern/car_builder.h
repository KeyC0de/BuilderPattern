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
	float m_width = 2;	// meteres
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

	class Builder final
	{
		float m_weight;	// tonnes
		float m_width = 2;
		int m_doorCount = 4;
		int m_tireCount = 4;
		int m_power;
		Tires m_tires;
		Material m_material;
		std::string m_name;		///!///
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
		// It would be best to get rid of setters and getters & pack everything into
		// a struct and/or make the struct public instead
		Builder& setWeight( float value ) noexcept;
		Builder& setWidth( float value ) noexcept;
		Builder& setDoorCount( int value ) noexcept;
		Builder& setTireCount( int value ) noexcept;
		Builder& setPower( int value ) noexcept;;
		Builder& setColor( const std::string& value ) noexcept;
		Builder& setName( const std::string& value ) noexcept;
		Builder& setMaterial( const Material& value ) noexcept;
	};
	//////////////////////////////////////////////////////////////////////
	~Car();
	Car( const Car& rhs) = delete;
	Car& operator=( const Car& rhs) = delete;

	void present();
	void cruise() noexcept;

	// TODO: implement the mctor & maop as well
};
