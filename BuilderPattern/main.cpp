#include <iostream>
#include "car_builder.h"


int main()
{
	std::cout << "sizeof(Car)="
		<< sizeof( Car )
		<< '\n';
	std::cout << "sizeof(Car::Builder)="
		<< sizeof( Car::Builder )
		<< "\n\n";

	auto truckMaster = Car::Builder{}
		.setWeight( 20 )
		.setName( "Truck Master 18-Wheeler" )
		.setColor( "yellow" )
		.setDoorCount( 5 )
		.setTireCount( 8 )
		.setMaterial( Material::SyntheticRubber )
		.setPower( 6000 )
		.create();
	
	truckMaster->present();
	truckMaster->cruise();
	truckMaster->present();

#if defined _DEBUG && !defined NDEBUG
	while ( !getchar() );
#endif
	return EXIT_SUCCESS;
}