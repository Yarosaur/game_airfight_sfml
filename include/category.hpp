#ifndef __AIRPLANE_CATEGORY_HPP__
#define __AIRPLANE_CATEGORY_HPP__


// Entity/scene node category, used to dispatch commands
namespace Category
{
    enum Type
    {
	None		= 0,
	Scene		= 1 << 0,
	PlayerAircraft	= 1 << 1,
	AlliedAircraft	= 1 << 2,
	EnemyAircraft	= 1 << 3,
    };
}

#endif // __AIPLANE_CATEGORY_HPP__
