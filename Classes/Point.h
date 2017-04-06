#ifndef POINT_H_
#define POINT_H_

namespace eun {
#define MATH_TOLERANCE              2e-37f

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

	// class Point
	class Point {
	public:
		Point() : x(0.0f), y(0.0f) {}
		Point(float _x, float _y) : x(_x), y(_y) {}
		Point(const Point& _other) : x(_other.x), y(_other.y) {}
		~Point() {}


		//subtract
		/*inline void Vec2::subtract(const Vec2& v)
		{
		x -= v.x;
		y -= v.y;
		}*/
		//add
		/*inline void Vec2::add(const Vec2& v)
		{
		x += v.x;
		y += v.y;
		}*/

		inline Point operator+(const Point& _other) {
			Point tmp(*this);
			tmp.x += _other.x;
			tmp.y += _other.y;
			return tmp;
		}

		//inline Point& operator+=(const Point& _other) {
		//	x += _other.x;
		//	y += _other.y;
		//	return *this;
		//}

		inline Point operator-(const Point& _other) {
			Point tmp(*this);
			tmp.x -= _other.x;
			tmp.y -= _other.y;
			return tmp;
		}

		/*inline Vec2 Vec2::operator*(float s) const
		{
		Vec2 result(*this);
		result.scale(s);
		return result;
		}*/

		/*inline void Vec2::scale(float scalar)
		{
		x *= scalar;
		y *= scalar;
		}*/

		inline Point operator*(float f) const {
			Point tmp(*this);
			tmp.x *= f;
			tmp.y *= f;
			return tmp;
		}

		/*inline Point& operator-=(const Point& _other) {
		x -= _other.x;
		y -= _other.y;
		return *this;
		}*/

		/*inline Point operator-(const cocos2d::Vec2& _other) {
		Point tmp(*this);
		tmp.x -= _other.x;
		tmp.y -= _other.y;
		return tmp;
		}*/

		/*inline Point& operator-=(const cocos2d::Vec2& _other) {
		x -= _other.x;
		y -= _other.y;
		return *this;
		}*/

		void normalize()
		{
			float n = x * x + y * y;
			// Already normalized.
			if (n == 1.0f)
				return;

			n = std::sqrt(n);
			// Too close to zero.
			if (n < MATH_TOLERANCE)
				return;

			n = 1.0f / n;
			x *= n;
			y *= n;
		}

		float distance(const Point& _other) const
		{
			float dx = _other.x - x;
			float dy = _other.y - y;
			return std::sqrt(dx * dx + dy * dy);
		}

		Point min_point(const eun::Point& _other) const
		{
			Point min_point;
			min_point.x = ((x > _other.x) ? _other.x : x);
			min_point.y = ((y > _other.y) ? _other.y : y);
			return min_point;
		}

		float x;
		float y;
	};

	// class Point

}

#endif