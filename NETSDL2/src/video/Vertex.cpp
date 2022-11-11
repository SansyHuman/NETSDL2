#include "../../include/video/Vertex.h"

using namespace NETSDL2::Video;

NETSDL2::Video::Vertex::Vertex(NETSDL2::Video::FPoint% position, NETSDL2::Video::Color% color, NETSDL2::Video::FPoint% texCoord)
	: Position(position), Color(color), TexCoord(texCoord)
{
	
}

System::String^ NETSDL2::Video::Vertex::ToString()
{
	return System::String::Format("[Pos: {0}, Color: {1}, TexC: {2}]", Position, Color, TexCoord);
}
