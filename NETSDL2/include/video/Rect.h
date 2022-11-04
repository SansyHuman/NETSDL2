#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// Point structure like Point, but uses float instead of int for
		/// coordinates.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct FPoint
		{
			/// <summary>
			/// The x coordinate of the point.
			/// </summary>
			float X;

			/// <summary>
			/// The y coordinate of the point.
			/// </summary>
			float Y;

			FPoint(float x, float y);

			virtual System::String^ ToString() override;
		};

		/// <summary>
		/// A structure that contains the definition of a rectangle, with the
		/// origin at the upper left.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct FRect : System::IEquatable<FRect>
		{
			/// <summary>
			/// The x location of the rectangle's upper left corner.
			/// </summary>
			float X;

			/// <summary>
			/// The y location of the rectangle's upper left corner.
			/// </summary>
			float Y;

			/// <summary>
			/// The width of the rectangle.
			/// </summary>
			float W;

			/// <summary>
			/// The height of the rectangle.
			/// </summary>
			float H;

			FRect(float x, float y, float w, float h);

			virtual System::String^ ToString() override;

			/// <summary>
			/// Check whether a rectangle has no area.
			/// </summary>
			property bool Empty
			{
				bool get();
			}

			virtual bool Equals(NETSDL2::Video::FRect other);
		};

		/// <summary>
		/// A structure that defines a two dimensional point.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Point
		{
			/// <summary>
			/// The x coordinate of the point.
			/// </summary>
			int X;

			/// <summary>
			/// The y coordinate of the point.
			/// </summary>
			int Y;

			Point(int x, int y);

			virtual System::String^ ToString() override;
		};

		/// <summary>
		/// A structure that contains the definition of a rectangle, with the
		/// origin at the upper left.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Rect : System::IEquatable<Rect>
		{
			/// <summary>
			/// The x location of the rectangle's upper left corner.
			/// </summary>
			int X;

			/// <summary>
			/// The y location of the rectangle's upper left corner.
			/// </summary>
			int Y;

			/// <summary>
			/// The width of the rectangle.
			/// </summary>
			int W;

			/// <summary>
			/// The height of the rectangle.
			/// </summary>
			int H;

			Rect(int x, int y, int w, int h);

			virtual System::String^ ToString() override;

			/// <summary>
			/// Check whether a rectangle has no area.
			/// </summary>
			property bool Empty
			{
				bool get();
			}

			virtual bool Equals(NETSDL2::Video::Rect other);
		};

		/// <summary>
		/// Functions for handling simple rectangles including overlaps and
		/// merges.
		/// </summary>
		public ref struct RectOps abstract sealed
		{
			/// <summary>
			/// Calculate a minimal rectangle enclosing a set of points with
			/// float precision.
			/// </summary>
			/// <param name="points">An array of <see cref="FPoint"/> structures
			/// representing points to be enclosed.</param>
			/// <param name="clip">An <see cref="FRect"/> used for clipping or
			/// null to enclose all points.</param>
			/// <param name="result">An <see cref="FRect"/> structure filled
			/// in with the minimal enclosing rectangle</param>
			/// <returns>true if any points were enclosed or false if all the
			/// points were outside of the clipping rectangle.</returns>
			static bool EncloseFPoints(array<FPoint>^ points, System::Nullable<FRect> clip, [Out]FRect% result);

			/// <summary>
			/// Calculate a minimal rectangle enclosing a set of points.
			/// </summary>
			/// <param name="points">An array of <see cref="Point"/> structures
			/// representing points to be enclosed.</param>
			/// <param name="clip">An <see cref="Rect"/> used for clipping or
			/// null to enclose all points.</param>
			/// <param name="result">An <see cref="Rect"/> structure filled
			/// in with the minimal enclosing rectangle</param>
			/// <returns>true if any points were enclosed or false if all the
			/// points were outside of the clipping rectangle.</returns>
			static bool EnclosePoints(array<Point>^ points, System::Nullable<Rect> clip, [Out]Rect% result);

			/// <summary>
			/// Determine whether two rectangles intersect.
			/// </summary>
			/// <param name="a">An <see cref="Rect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="Rect"/> structure representing
			/// the second rectangle.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool HasIntersection(Rect a, Rect b);

			/// <summary>
			/// Determine whether two rectangles intersect with float precision.
			/// </summary>
			/// <param name="a">An <see cref="FRect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="FRect"/> structure representing
			/// the second rectangle.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool HasIntersectionF(FRect a, FRect b);

			/// <summary>
			/// Calculate the intersection of two rectangles with float
			/// precision.
			/// </summary>
			/// <param name="a">An <see cref="FRect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="FRect"/> structure representing
			/// the second rectangle.</param>
			/// <param name="result">An <see cref="FRect"/> structure filled in
			/// with the intersection of rectangles a and b.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool IntersectFRect(FRect a, FRect b, [Out]FRect% result);

			/// <summary>
			/// Calculate the intersection of a rectangle and line segment with
			/// float precision.
			/// </summary>
			/// <param name="rect">An <see cref="FRect"/> structure representing
			/// the rectangle to intersect.</param>
			/// <param name="x1">The starting X-coordinate of the line.</param>
			/// <param name="y1">The starting Y-coordinate of the line.</param>
			/// <param name="x2">The ending X-coordinate of the line.</param>
			/// <param name="y2">The ending Y-coordinate of the line.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool IntersectFRectAndLine(FRect rect, float x1, float y1, float x2, float y2);

			/// <summary>
			/// Calculate the intersection of two rectangles.
			/// </summary>
			/// <param name="a">An <see cref="Rect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="Rect"/> structure representing
			/// the second rectangle.</param>
			/// <param name="result">An <see cref="Rect"/> structure filled in
			/// with the intersection of rectangles a and b.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool IntersectRect(Rect a, Rect b, [Out]Rect% result);

			/// <summary>
			/// Calculate the intersection of a rectangle and line segment.
			/// </summary>
			/// <param name="rect">An <see cref="Rect"/> structure representing
			/// the rectangle to intersect.</param>
			/// <param name="x1">The starting X-coordinate of the line.</param>
			/// <param name="y1">The starting Y-coordinate of the line.</param>
			/// <param name="x2">The ending X-coordinate of the line.</param>
			/// <param name="y2">The ending Y-coordinate of the line.</param>
			/// <returns>true if there is an intersection, false otherwise.
			/// </returns>
			static bool IntersectRectAndLine(Rect rect, int x1, int y1, int x2, int y2);

			/// <summary>
			/// Use this function to check if a point resides inside a rectangle.
			/// </summary>
			/// <param name="p">An <see cref="FPoint"/> which is the point.
			/// </param>
			/// <param name="r">An <see cref="FRect"/> which is the rectangle.
			/// </param>
			/// <returns>true if point resides inside rectangle or false if
			/// not.</returns>
			static bool PointInFRect(FPoint p, FRect r);

			/// <summary>
			/// Use this function to check if a point resides inside a rectangle.
			/// </summary>
			/// <param name="p">An <see cref="Point"/> which is the point.
			/// </param>
			/// <param name="r">An <see cref="Rect"/> which is the rectangle.
			/// </param>
			/// <returns>true if point resides inside rectangle or false if
			/// not.</returns>
			static bool PointInRect(Point p, Rect r);

			/// <summary>
			/// Calculate the union of two rectangles with float precision.
			/// </summary>
			/// <param name="a">An <see cref="FRect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="FRect"/> structure representing
			/// the second rectangle.</param>
			/// <param name="result">An <see cref="FRect"/> structure filled in
			/// with the union of rectangles a and b.</param>
			static void UnionFRect(FRect a, FRect b, [Out]FRect% result);

			/// <summary>
			/// Calculate the union of two rectangles.
			/// </summary>
			/// <param name="a">An <see cref="FRect"/> structure representing
			/// the first rectangle.</param>
			/// <param name="b">An <see cref="FRect"/> structure representing
			/// the second rectangle.</param>
			/// <param name="result">An <see cref="FRect"/> structure filled in
			/// with the union of rectangles a and b.</param>
			static void UnionRect(Rect a, Rect b, [Out]Rect% result);
		};

	}
}