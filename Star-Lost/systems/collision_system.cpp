
#include "../game_context.h"

using namespace ecs;

using collideable = mpl::type_list<
	components::position,
	components::collision
>;

struct segment
{
	float x;
	float y;
	float w;
	float h;
};

sf::FloatRect operator+(const sf::FloatRect &rect, const sf::Vector2f &vec)
{
	return sf::FloatRect{ rect.left + vec.x, rect.top + vec.y, rect.width, rect.height };
}


inline double perpDot(const sf::Vector2f &a, const sf::Vector2f &b) 
{ 
	return (a.y*b.x) - (a.x*b.y); 
}

float lineline(segment a, segment b) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	float	x1 = std::min(a.x, a.x + a.w),
			x2 = std::max(a.x, a.x + a.w),
			x3 = std::min(b.x, b.x + b.w),
			x4 = std::max(b.x, b.x + b.w);

	float	y1 = std::min(a.y, a.y + a.h),
			y2 = std::max(a.y, a.y + a.h),
			y3 = std::min(b.y, b.y + b.h),
			y4 = std::max(b.y, b.y + b.h);

	// Float uncertainty
	float epsilon = std::numeric_limits<float>::epsilon() * 10000.0f;
	float inf = std::numeric_limits<float>::infinity();
	float fail = std::numeric_limits<float>::max();

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d < epsilon) return fail;

	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;
		
	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) - epsilon || x > std::max(x1, x2) + epsilon 
	 || x < std::min(x3, x4) - epsilon || x > std::max(x3, x4) + epsilon) return fail;
	if (y < std::min(y1, y2) - epsilon || y > std::max(y1, y2) + epsilon 
	 || y < std::min(y3, y4) - epsilon || y > std::max(y3, y4) + epsilon) return fail;

	float xf = (x - x1) / (x2 - x1);
	float yf = (y - y1) / (y2 - y1);

	return std::min(
		xf < 0.0f || xf > 1.0f ? fail : xf,
		yf < 0.0f || yf > 1.0f ? fail : yf
	);
}

void systems::collision::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::velocity &vel,
	components::collision &bbx
) const
{

	auto delta = ctx.get_delta();
	auto newpos = pos + vel * delta;
	// Where our bounding box is gonna be, 
	// should we continue along our current trajectory
	auto newbox = bbx.bbox + newpos;

	// Check if our boxes will intersect
	ctx.for_entities<collideable>([&pos, &vel, &bbx, &ctx, eid, newbox, delta](entity_index otherid)
	{
		if (otherid == eid)
			return;

		auto obox =
			ctx.get_component<components::collision>(otherid).bbox
			+ ctx.get_component<components::position>(otherid);

		auto ivel = vel * ctx.get_delta();

		auto abox = bbx.bbox + pos;

		// Define the line segments making up the transfer
		segment moving[4] = {
			{ abox.left,  abox.top, ivel.x, ivel.y }, // NW
			{ abox.left + abox.width, abox.top, ivel.x, ivel.y }, // NE
			{ abox.left, abox.top + abox.height, ivel.x, ivel.y }, // SW
			{ abox.left + abox.width, abox.top + abox.height, ivel.x, ivel.y }, // SE
		};

		segment target[4] = {
			{ obox.left,				obox.top,				obox.width, 0			},	// Top
			{ obox.left,				obox.top,				0,			obox.height },	// Left
			{ obox.left,				obox.top + obox.height, obox.width, 0			},	// Bottom
			{ obox.left + obox.width,	obox.top,				0,			obox.height }	// Right
		};
		
		//if (!obox.intersects(newbox))
		//	return;

		using array_iter = std::array<float, 4>::iterator;
		using array_iter2 = std::array<array_iter, 4>::iterator;

		// Construct a collision matrix
		std::array<std::array<float, 4>, 4> matrix{ {
			//		   top							   left							   bottom						   right
			/* NW */ { lineline(moving[0], target[0]), lineline(moving[0], target[1]), lineline(moving[0], target[2]), lineline(moving[0], target[3]) },
			/* NE */ { lineline(moving[1], target[0]), lineline(moving[1], target[1]), lineline(moving[1], target[2]), lineline(moving[1], target[3]) },
			/* SW */ { lineline(moving[2], target[0]), lineline(moving[2], target[1]), lineline(moving[2], target[2]), lineline(moving[2], target[3]) },
			/* SE */ { lineline(moving[3], target[0]), lineline(moving[3], target[1]), lineline(moving[3], target[2]), lineline(moving[3], target[3]) }
		} };

		// Find out which of our corners intersected with the obstacle first
		std::array<array_iter, 4> lowest{
			/* NW */ std::min_element(matrix[0].begin(), matrix[0].end()),
			/* NE */ std::min_element(matrix[1].begin(), matrix[1].end()),
			/* SW */ std::min_element(matrix[2].begin(), matrix[2].end()),
			/* SE */ std::min_element(matrix[3].begin(), matrix[3].end())
		};

		auto line = std::min_element(lowest.begin(), lowest.end(), [](auto a, auto b) { return *a < *b; });

		float fraction = **line;
		if (fraction == std::numeric_limits<float>::max())
			return;

		// Move to our point of intersection
		pos += ivel * fraction;

		// Get the remaining velocity
		auto restvel = ivel * (1.0f - fraction);

		auto nullify = sf::Vector2f{ 0.0f, 0.0f };
		auto reverse_x = sf::Vector2f{ -1.0f, 1.0f };
		auto reverse_y = sf::Vector2f{ 1.0f, -1.0f};

		auto new_velocity = sf::Vector2f{};
		// Figure out what to do with it
		switch (std::distance(lowest.begin(), line))
		{
		case 0: // NW
			switch (std::distance(matrix[0].begin(), *line))
			{
			case 0: new_velocity = nullify; break; // top
			case 1: new_velocity = nullify; break; // left
			case 2: new_velocity = reverse_y; break; // bottom
			case 3: new_velocity = reverse_x; break; // right
			default: break;
			}
			break;
		case 1: // NE
			switch (std::distance(matrix[1].begin(), *line))
			{
			case 0: new_velocity = nullify; break; // top
			case 1: new_velocity = reverse_x; break; // left
			case 2: new_velocity = reverse_y; break; // bottom
			case 3: new_velocity = nullify; break; // right
			default: break;
			}
			break;
		case 2: // SW
			switch (std::distance(matrix[2].begin(), *line))
			{
			case 0: new_velocity = reverse_y; break; // top
			case 1: new_velocity = nullify; break; // left
			case 2: new_velocity = nullify; break; // bottom
			case 3: new_velocity = reverse_x; break; // right
			default: break;
			}
			break;
		case 3: // SE
			switch (std::distance(matrix[3].begin(), *line))
			{
			case 0: new_velocity = reverse_y; break; // top
			case 1: new_velocity = reverse_x; break; // left
			case 2: new_velocity = nullify; break; // bottom
			case 3: new_velocity = nullify; break; // right
			default: break;
			}
			break;
		default: break;
		}
		vel.x = new_velocity.x * restvel.x / delta;
		vel.y = new_velocity.y * restvel.y / delta;
	});	

}