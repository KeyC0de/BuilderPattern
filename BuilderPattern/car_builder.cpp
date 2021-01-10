#include <iostream>
#include "car_builder.h"


Engine::Engine( int power )
	:
	m_power(power)
{}

int Engine::getPower() const noexcept
{
	return m_power;
}


Car::Car( float weight,
	float width,
	int doorCount,
	int tireCount,
	Type type,
	std::unique_ptr<Engine> peng,
	const Tires& tires,
	const std::string& color,
	const std::string& name )
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
	std::cout << name << " created!" << '\n';
}

std::unique_ptr<Car> Car::Builder::create() const
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

Car::Builder& Car::Builder::setWeight( float value ) noexcept
{
	m_weight = value;
	return *this;
}

Car::Builder& Car::Builder::setWidth( float value ) noexcept
{
	m_width = value;
	return *this;
}

Car::Builder& Car::Builder::setDoorCount( int value ) noexcept
{
	m_doorCount = value;
	return *this;
}

Car::Builder& Car::Builder::setTireCount( int value ) noexcept
{
	m_tireCount = value;
	return *this;
}

Car::Builder& Car::Builder::setPower( int value ) noexcept
{
	m_power = value;
	return *this;
}

Car::Builder& Car::Builder::setColor( const std::string& value ) noexcept
{
	m_color = value;
	return *this;
}

Car::Builder& Car::Builder::setName( const std::string& value ) noexcept
{
	m_name = value;
	return *this;
}

Car::Builder& Car::Builder::setMaterial( const Material& value ) noexcept
{
	m_material = value;
	return *this;
}

//////////////////////////////////////////////////////////////////////

Car::~Car()
{
	std::cout << m_name
		<< " destroyed!"
		<< '\n';
}

void Car::present()
{
	std::cout << "This is " << m_name
		<< " ready to cruise the vast landscapes and the infinite roads of the world\n"
		<< "weight:" << m_weight << '\n'
		<< "width:" << m_width << '\n'
		<< "door count:" << m_doorCount << '\n'
		<< "tire count:" << m_tireCount << '\n'
		<< "engine power = " << m_pEngine->getPower() << '\n'
		<< "color:" << m_color << '\n'
		<< "mileage:" << m_mileage << '\n'
		<< '\n';
}

void Car::cruise() noexcept
{
	m_mileage += 40;
	std::cout << '\n'
		<< "\nCruising ..\n"
		<< '\n';
}