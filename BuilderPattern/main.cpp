#include <iostream>
#include "car_builder.h"

int main()
{
	std::wcout << "sizeof(Car)=" << sizeof( Car ) << '\n';
	std::wcout << "sizeof(Car::Builder)=" << sizeof( Car::Builder ) << L'\n' << L'\n';

	auto truckMaster = Car::Builder{}
			.setWeight( 20 )
			.setName( L"Truck Master 18-Wheeler" )
			.setColor( L"yellow" )
			.setDoorCount( 5 )
			.setTireCount( 8 )
			.setMaterial( Material::SyntheticRubber )
			.setPower( 6000 )
			.create();
	
	truckMaster->present();
	truckMaster->cruise();
	truckMaster->present();

	std::system( "pause" );
	return 0;
}